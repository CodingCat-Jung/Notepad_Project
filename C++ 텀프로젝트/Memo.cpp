#include <iostream>
#include <cstring>
#include <cstdio>

#include "Memo.h"

using namespace std;

#define FILE_SIZE 5

// 기본 생성자
NoteBook::NoteBook() {

	// count를 저장하는 파일 읽기 시도
	ifstream countFile("count.txt");
	if (countFile.is_open()) {
		countFile >> count; // 파일에서 count 값을 읽어옴
		countFile.close();
	}
	else {
		cerr << "에러: count를 읽어오는 데 실패했습니다." << endl;
		count = 0; // 파일을 읽어오지 못할 경우 기본값으로 초기화
	}

}

// 파일명을 입력받는 생성자
NoteBook::NoteBook(string noteName) : NoteBook() {

	this->noteName = noteName;

	// open() 함수 호출 - 파일 로드
	open(noteName); // 노트 열 때 사용자가 지정한 이름으로 초기화

}

// 소멸자 함수
NoteBook::~NoteBook() {
	// 파일에 count 값을 저장
	ofstream countFile("count.txt");
	if (countFile.is_open()) {
		countFile.clear();
		countFile << count << endl;
		countFile.flush();
	}

	// close() 함수 호출 - 파일 저장
	close();

}

// 파일 오픈 함수
// 파일 로드를 위한 함수 - 생성자에서 호출
void NoteBook::open(string noteName) {

	// 텍스트 파일에서 내용 읽어와 contents[NUM] 배열에 저장
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream 인스턴스 contentsFile를 이용하여 파일 오픈 - 읽기 및 쓰기 용도
		contentsFile.open(fileName, ios::in | ios::out);

		// 파일 열렸는지 확인 후 불린 값 isOpen 변수에 저장
		isOpen = contentsFile.is_open();

		if (!isOpen) { // 파일 오픈 실패
			cout << "FILE = " << generateFileName(i) << " 은 존재하지 않은 파일입니다." << endl;
			continue;
		}

		getline(contentsFile, contents[i]); // 라인으로 내용을 읽어서 contents 배열에 저장
		//cout << contents[i] << endl;
		contentsFile.close();
	}
}

// 파일 닫기 함수
// 파일 저장을 위한 함수 - 소멸자에서 호출
void NoteBook::close() {

	// 파일의 개수 크기(5)만큼 반복 - contents 배열에서 내용 파일에 저장 후 파일 닫기
	// 존재하는 파일만 저장, 존재하지 않는 파일은 패스
	for (int i = 0; i < FILE_SIZE; i++) {

		if (contents[i]=="") { // 존재하지 않는 파일
			continue;
		}

		else if (isOpen) {
			// contents 배열에 내용이 존재하면 - 존재하는 파일인 경우
			string fileName = generateFileName(i);

			// fstream 인스턴스 contentsFile를 이용하여 파일 오픈 - 쓰기 용도
			contentsFile.open(fileName, ios::out);

			// 파일 열렸는지 확인 후 불린 값 isOpen 변수에 저장
			isOpen = contentsFile.is_open();

			contentsFile << contents[i]; // 텍스트 파일에 배열에 저장되어 있던 내용 저장
		}
		
		contentsFile.close();
	}
}

// 저장할 파일명 생성 ex) memo01.txt ...
string NoteBook::generateFileName(int i) {
	// 기본 파일명 생성
	char defaultName[BUFSIZ] = "\0";

	strcpy(defaultName, noteName.c_str());
	// c_str() : C-string 처럼 string의 내용을 반환
	strcat(defaultName, "00.txt");

	// 새 파일명 생성
	static char page[100];
	strcpy(page, defaultName); // 기본 파일명 복사
	int location = strlen(noteName.c_str());

	char number[3];
	sprintf(number, "%02d", i); // 페이지 번호를 두 자리 정수로 변환하여 저장
	// sprintf returns the number of bytes stored in buffer
	strncpy(page + location, number, 2); // 페이지 번호를 파일명에 추가
	// not counting the terminating null character

	return page; // 생성된 파일명 반환
}

// 메모 수 반환 함수
int NoteBook::Count() const {
	return count;
}

// 메모 작성 함수
// page에 해당하는 인덱스 번호에 content 내용 작성
void NoteBook::write(int page, string content) {

	// 페이지는 0 ~ 4
	if (page < 0 && page > NUM) {
		cout << "페이지 번호가 잘못 입력되었습니다." << endl;
		return;
	}

	// 파일이 존재하지 않는 경우에만 파일 생성 후 contents 배열에 내용 작성, count 증가
	// 파일이 존재하는 경우에는 패스
	string filename = generateFileName(page); // 파일명 생성

	ifstream testFile(filename.c_str());

	if (!testFile) { // 파일이 존재하지 않으면
		testFile.close();
		ofstream newFile(filename.c_str()); // 새 파일 생성

		newFile.close();

		contents[page] = content; // 해당 배열의 인덱스에 내용 저장
		count++; // 새 파일이 생성되었으므로 count 증가

		cout << "정상적으로 새로운 파일을 생성하고 작성되었습니다." << endl;
	}
	else { // 파일이 존재하는 경우
		cout << "이미 존재하는 파일입니다." << endl;
	}
}

// 메모 조회 함수
// page에 해당하는 인덱스 번호의 내용을 출력
string& NoteBook::look(int page) {

	// 유효한 page 범위인 경우
	if (page >= 0 && page < NUM) {
		cout << "선택하신 " << page << "페이지 내용입니다." << endl;
		cout << contents[page] << endl; // 선택한 페이지 내용 contents 배열에서 읽어와 출력
		return contents[page];
	}

	else cout << "범위를 벗어났습니다." << endl;

	return contents[0];
}

// 메모 수정 함수
// page에 해당하는 인덱스 번호의 내용을 매개변수 content 내용으로 바꿈
void NoteBook::edit(int page, string content)
{
	// 유효한 페이지 범위인 경우
	if (page >= 0 && page < NUM) {
		// 해당 페이지의 내용을 매개변수로 받은 content로 수정
		contents[page] = content;
		cout << "정상적으로 내용이 수정되었습니다." << endl;
	}
	else {
		cerr << "잘못된 페이지 번호입니다." << endl;
	}
}

// 메모 삭제 함수
// page에 해당하는 인덱스 번호의 메모를 모두 삭제
void NoteBook::remove(int page) {
	// 유효한 page 범위인 경우
	if (page >= 0 && page < NUM) {

		// 해당 페이지의 내용을 삭제
		contents[page] = ""; 
		cout << "정상적으로 해당 페이지 내용을 삭제하였습니다." << endl;
		
		// 해당 페이지 텍스트 파일 삭제
		contentsFile.close(); // 파일을 삭제하기 전에 닫기

		// 파일 삭제
		string filename = generateFileName(page);

		//system("icacls filename /grant 사용자:권한");

		if (std::remove(filename.c_str()) == 0) {
			cout << "정상적으로 파일을 삭제했습니다." << endl;
			count--;
		}
		else {
			cerr << "파일을 삭제하는 중에 문제가 발생했습니다." << endl;
		}

	}
	else {
		cerr << "잘못된 페이지 번호입니다." << endl;
	}
}

// main()에서 2번 보기 선택 한 경우
// 존재하는 파일 내용 출력 함수
void NoteBook::display() {
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream 인스턴스 contentsFile를 이용하여 파일 오픈 - 읽기 
		contentsFile.open(fileName, ios::in);

		// 파일 열렸는지 확인 후 불린 값 isOpen 변수에 저장
		isOpen = contentsFile.is_open();

		if (!isOpen) { // 파일 오픈 실패
			cout << "num " << i + 1 << ". ";
			cout << "FILE = " << generateFileName(i) << " 은 존재하지 않은 파일입니다." << endl;
			continue;
		}

		else if (isOpen) {
			cout << "num " << i + 1 << ". ";
			cout << "메모 페이지 " << i + 1 << " 내용 : ";
			cout << contents[i] << endl;
		}
		contentsFile.close();
	}
}

void NoteBook::file_Open() {

	// 존재하는 파일 출력
	for (int i = 0; i < FILE_SIZE; i++) {

		string fileName = generateFileName(i);

		// fstream 인스턴스 contentsFile를 이용하여 파일 오픈 - 읽기 
		contentsFile.open(fileName, ios::in);

		// 파일 열렸는지 확인 후 불린 값 isOpen 변수에 저장
		isOpen = contentsFile.is_open();

		if (!isOpen) { // 파일 오픈 실패
			cout << "num " << i + 1 << ". ";
			cout << "FILE = " << generateFileName(i) << " 은 존재하지 않은 파일입니다." << endl;
			continue;
		}

		cout << "num " << i + 1 << ". ";
		cout<< "memo0" << i << ".txt 파일 존재함" << endl;

		contentsFile.close();
	}
}