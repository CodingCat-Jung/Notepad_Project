#pragma once
#pragma warning (disable: 4996)
#ifndef MEMO_H
#define MEMO_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define NUM 5

class NoteBook {
	// Constructors and Destructors
public:
	NoteBook();
	NoteBook(string noteName);
	~NoteBook();

	// Methods
	void write(int page, string content); // page에 해당하는 인덱스 번호에 content 내용 작성
	void edit(int page, string content); // page에 해당하는 인덱스 번호의 내용을 매개변수 content 내용으로 바꿈
	string& look(int page); // page에 해당하는 인덱스 번호의 내용을 출력
	void remove(int page); // page에 해당하는 인덱스 번호의 메모를 모두 삭제

	void open(string noteName); 
	void close();
	int Count() const;

	void display();
	void file_Open();

	// instance variable
private:
	// 저장할 파일명 생성 ex) noteName01.txt ...
	string generateFileName(int i);

	string contents[NUM]; // 5개의 메모를 관리할 문자열
	fstream contentsFile; // fstream 인스턴스 contentsFile
	string noteName; // 메모 파일 이름
	bool isOpen; // 메모의 여닫힘 여부
	int count; // 메모수 카운트
};

#endif // !MEMO_H
