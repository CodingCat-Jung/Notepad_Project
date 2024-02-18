#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Memo.h"
using namespace std;

const int SIZE = 80;

int menu()
{
	int num;
	cout << "\n";
	cout << "====================\n";
	cout << "1.\t작성\t\n";
	cout << "2.\t보기\t\n";
	cout << "3.\t수정\t\n";
	cout << "4.\t삭제\t\n";
	cout << "5.\tEnd\t\n";
	cout << "====================\n";

	cin >> num;
	cin.get(); // 개행 문자를 읽음
	return num;
}

int main() {
	NoteBook note("memo");

	// cnt : 메모수 카운트
	int cnt;

	// num : page 인자값 전달 변수
	// sel : 메뉴 단계에서 사용자 선택 기능 전달 변수
	int num, sel, j, k;

	char buff[SIZE]; // 문자열을 입력받는 임시 버퍼

	// cnt 지정
	cnt = note.Count() + 1; // 멤버함수의 카운터는 0부터 카운트되기 때문에 +1

	do {
		sel = menu();
		switch (sel)
		{
			// 1. 작성
		case 1:
			// 카운트가 5보다 크면 더이상 작성 x
			// 메모 페이지와 내용 입력 받음
			note.file_Open();
			cout << "작성할 메모 페이지 번호를 입력하세요 : "; cin >> num;

			// 문자열이 입력될 경우 예외처리
			if (cin.fail()) {
				cerr << "올바르지 않은 입력입니다." << endl;
				cin.clear(); // 입력 버퍼 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
				continue;
			}

			// 범위 체크
			if (num > 5 || num <= 0) { // 메모장의 범위 1 ~ 5
				cout << "범위를 벗어났습니다." << endl;
				continue;
			}
			
			cout << "메모 내용을 입력하세요: "; cin >> buff;

			if (cin.fail()) {
				cerr << "입력이 너무 깁니다. 버퍼 크기 초과." << endl;
				cin.clear(); // 입력 스트림 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
				continue;
			}

			note.write(num - 1, buff); // contents[NUM] 배열에 해당 인덱스에 내용 임시 저장
			
			break;

			// 2. 보기
		case 2:
			// 카운트된 위치까지 보여주기
			// c_str() : 스트링 클래스의 문자열을 C 스트링 형식으로 변환
			// 문자열의 앞 8글자만 표기(영문일 경우) : 핸폰 메모장 효과

			// 존재하는 파일 내용 출력
			note.display();

			cout << "\n메모 페이지 번호를 입력하세요 ( Back is 0 ) : ";
			cin >> num;
			cin.get();

			// 문자열이 입력될 경우 예외처리
			if (cin.fail()) {
				cerr << "올바르지 않은 입력입니다." << endl;
				cin.clear(); // 입력 버퍼 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
				continue;
			}

			if (num == 0) // 0번 입력시 뒤로 (메뉴창으로)
			{
				break;
			}
			else if (num > note.Count() && num < 0)// 범위 벗어난 경우
			{
				cout << "범위를 벗어났습니다." << endl;
			}
			else // 메모의 전체 보기
			{
				string memoContent = note.look(num - 1);
			}

			break;

			// 3. 수정
		case 3:
			// 수정 할 메모 페이지 입력 받음
			note.file_Open();
			cout << "수정할 메모 페이지 번호를 입력하세요 : ";
			cin >> num;
			cin.get();

			// 문자열이 입력될 경우 예외처리
			if (cin.fail()) {
				cerr << "올바르지 않은 입력입니다." << endl;
				cin.clear(); // 입력 버퍼 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
				continue;
			}

			// 범위 체크
			if (num > note.Count() && num <= 0) {
				cout << "범위를 벗어났습니다." << endl;
				continue;
			}

			// 새 문자열 내용 입력 받음
			cout << "새 내용을 입력하세요: "; cin >> buff;

			// 기존 메모를 새 문자열로 교체
			note.edit(num - 1, buff);

			break;

			// 4. 삭제
		case 4:
			// 삭제할 메모 페이지 입력 받음
			note.file_Open();
			cout << "삭제할 메모 페이지 번호를 입력하세요 : ";
			cin >> num;
			cin.get();

			// 문자열이 입력될 경우 예외처리
			if (cin.fail()) {
				cerr << "올바르지 않은 입력입니다." << endl;
				cin.clear(); // 입력 버퍼 초기화
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
				continue;
			}

			// 범위 체크
			if (num > note.Count() && num <= 0) {
				cout << "범위를 벗어났습니다." << endl;
				continue;
			}

			// 메모 삭제
			note.remove(num - 1);

			break;

			// 5. End
		case 5:
			cout << "Program end. \n";
			break;

		default:
			// 메뉴 입력 범위를 벗어난 경우
			cout << "Input Error. Try again. \n";
			break;
		}
	} while (sel != 5);

	return 0;
}