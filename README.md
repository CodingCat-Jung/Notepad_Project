# 📘 메모장 관리 프로그램 (C++ Term Project)

> **20204026 정명훈**  
> C++ 프로그래밍 텀 프로젝트 결과물입니다. 간단한 CLI 기반 메모장 관리 프로그램을 구현하였습니다.

---

## 🛠️ 프로젝트 소개

이 프로그램은 5개의 텍스트 메모 파일을 관리할 수 있는 **메모장 관리 프로그램**입니다.  
파일의 **작성, 보기, 수정, 삭제** 기능을 제공하며, 다양한 예외 상황을 처리할 수 있도록 구현되어 있습니다.

---

## 📂 기본 구성

- `Memo.h`: 메모장 관련 기능을 담은 헤더 파일
- `main.cpp`: 사용자 인터페이스 및 프로그램 흐름 제어
- 최대 5개의 텍스트 파일(`memo1.txt` ~ `memo5.txt`)을 생성 및 관리

---

## ▶️ 프로그램 실행 흐름

### 초기 화면

- 실행 시 현재 존재하지 않는 메모 파일 리스트를 먼저 출력합니다.
- 이후, 사용자에게 아래 메뉴 중 하나를 선택하도록 합니다:

---

## 📝 기능 설명

### 1. 작성

- 사용자가 작성할 메모 번호(1~5)를 선택합니다.
- 이미 존재하는 파일 선택 시 에러 메시지를 출력하고 메뉴로 되돌아갑니다.
- 존재하지 않는 번호 선택 시 새로운 텍스트 파일을 생성하고, 내용을 임시 저장합니다.

### 2. 보기

- 저장된 메모 파일 목록을 보여줍니다.
- 사용자는 보고 싶은 메모 번호를 입력합니다.
- `0` 입력 시 이전 메뉴로 돌아갑니다.

### 3. 수정

- 메모 번호를 선택 후 내용을 입력하면 해당 메모가 수정됩니다.
- 수정 후 `보기` 메뉴를 통해 변경 내용을 확인할 수 있습니다.

### 4. 삭제

- 존재하지 않는 파일 선택 시 오류 메시지를 출력합니다.
- 존재하는 파일 선택 시 정상적으로 삭제됩니다.

---

## ⚠️ 예외 처리

- **범위 초과 입력**: 메모 번호 1~5 외의 숫자 입력 시 오류 메시지 출력
- **문자 입력**: 숫자를 입력해야 하는 곳에 문자를 입력할 경우 예외 처리
- 그 외 각 기능 내에서의 적절한 예외 처리 구현

---

## ✅ 실행 환경

- **Language**: C++
- **IDE**: Visual Studio 

---

## 📎 참고

- 본 프로젝트는 2024년 2학기 C++ 프로그래밍 수업의 텀 프로젝트 과제로 수행되었습니다.
