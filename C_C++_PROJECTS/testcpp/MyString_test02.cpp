#include <iostream>
#include <cstring>

using namespace std;

class MyString{
  char *string_content;
  int string_length;

  int memory_capacity;

public:
  MyString();
  // 문자열로 부터 생성
  MyString(const char *str);
  // 복사 생성자
  MyString(const MyString &str);
  // 이동 생성자
  MyString(MyString &&str);
  
  void reserve(int size);
  MyString operator+(const MyString &s);
  ~MyString();

  int length() const;
  void print();
  void println();
};

MyString::MyString() {
  cout << "기본 생성자 호출 !" << endl;
  string_length = 0;
  memory_capacity = 0;
  string_content = nullptr;
}

MyString::MyString(const char *str) {
  cout << "문자열 생성자 호출!" << endl;
  string_length = strlen(str);
  memory_capacity = string_length;

  string_content = new char[string_length];
  for(int i=0; i != string_length; i++) string_content[i] = str[i];
}

MyString::MyString(const MyString &str) {
  cout << "복사 생성자 호출!" << endl;
  string_length = str.string_length;
  memory_capacity = str.string_length;

  string_content = new char[string_length];
  for(int i=0; i != string_length; i++) string_content[i] = str.string_content[i];
}

MyString::MyString(MyString &&str) {
    cout << "이동 생성자 호출!" << endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // 임시 객체 소멸 시에 메모리를 해제하지 못하도록 한다.
    str.string_content = nullptr;
}

MyString::~MyString() { if(string_content) delete[] string_content; }

void MyString::reserve(int size) {
  if(size > memory_capacity) {
    char *prev_string_content = string_content;

    string_content = new char[size];
    memory_capacity = size;

    for(int i=0; i != string_length; i++) string_content[i] = prev_string_content[i];

    if(prev_string_content != nullptr) delete[] prev_string_content;
  }
}

MyString MyString::operator+(const MyString &s) {
  MyString str;
  str.reserve(string_length + s.string_length);
  for(int i=0; i<string_length; i++) str.string_content[i] = string_content[i];
  for(int i=0; i<s.string_length; i++) str.string_content[string_length+i] = s.string_content[i];

  str.string_length = string_length + s.string_length;
  return str;
}

int MyString::length() const { return string_length; }
void MyString::print() {
  for(int i=0; i != string_length; i++) cout << string_content[i];
}
void MyString::println() {
  for(int i=0; i != string_length; i++) cout << string_content[i];
  cout << endl;
}

int main(void) {
  MyString str1("abc");
  MyString str2("def");
  MyString str4 = str1;
  cout << "====================================" << endl;
  MyString str3 = str1 + str2;
  str3.println();
}
  





