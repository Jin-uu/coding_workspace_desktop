#include <stdio.h>		// 필요한 header file 추가 가능
#include <stdlib.h>
#include <string.h>
#include "student.h"

char filename[] = "records.dat";

int readRecord(FILE *fp, STUDENT *s, int rrn);
void unpack(const char*, STUDENT*);
int writeRecord(FILE *fp, const STUDENT *s, int rrn);
void pack(char *recordbuf, const STUDENT *s);
int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email);
void searchRecord(FILE *fp, enum FIELD f, char *keyval);
void printRecord(const STUDENT *s);
enum FIELD getFieldID(char *fieldname);
void printRecord(const STUDENT *s);
char* get_fields(char*);

int readRecord(FILE *fp, STUDENT *s, int rrn){
	fp = fopen("records.dat","r+");
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	char* buf;
	buf = (char*)malloc(sizeof(char)*RECORD_SIZE+1);
	fseek(fp, HEADER_SIZE + RECORD_SIZE*rrn, SEEK_SET);
	fread(buf, RECORD_SIZE, 1, fp);
	buf[RECORD_SIZE] = '\0';
	printf("read: %s", buf);
	// unpack(buf, s);
}

void unpack(const char *recordbuf, STUDENT *s){
	char ch;
	int idx=0;
	int field_idx=0, field_num=1;
	while(idx < RECORD_SIZE){
		switch(field_num){
			case ID:
				s -> id[field_idx] = recordbuf[idx];
				break;
			
			case NAME:
				s -> name[field_idx] = recordbuf[idx];
				break;
			
			case DEPT:
				s -> dept[field_idx] = recordbuf[idx];
				break;
			
			case ADDR:
				s -> addr[field_idx] = recordbuf[idx];
				break;
			
			case EMAIL:
				s -> email[field_idx] = recordbuf[idx];
				break;
			
		}
		field_idx++;
		idx++;
		if(recordbuf[idx] == '#') {
			field_num++;
			field_idx=0;
		}
	}
}
int writeRecord(FILE *fp, const STUDENT *s, int rrn){
	char* buf;
	buf = malloc(sizeof(char)*RECORD_SIZE);
	pack(buf, s);
	printf("rrn : %d\n", rrn);
	printf("buf : %s\n", buf);
	
	fseek(fp, HEADER_SIZE+RECORD_SIZE*rrn, SEEK_SET);
	fwrite(buf, RECORD_SIZE, 1, fp);
}

void pack(char *recordbuf, const STUDENT *s){
	sprintf(recordbuf, "%s#%s#%s#%s#%s#", s->id, s->name, s->dept, s->addr, s->email);
}

int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email){
	STUDENT temp_s;
	strcpy(temp_s.id, id);
	strcpy(temp_s.name, name);
	strcpy(temp_s.dept, dept);
	strcpy(temp_s.addr, addr);
	strcpy(temp_s.email, email);

	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	printf("file_size : %d\n", file_size);
	if(file_size <= 0){								// 빈파일이면
		fseek(fp, 0, SEEK_SET);
		int header = 0;							// 헤더 추가
		fwrite(&header, sizeof(int), 1, fp);
	}

	fseek(fp,0,SEEK_SET);							// 헤더에서 저장된 레코드 개수 가져오기
	int record_num;
	fread(&record_num, sizeof(int), 1, fp);
	// printf("recordnum[d] : %d\n", record_num);

	record_num++;									// 개수 +1
	// printf("recordnum[d] : %d\n", record_num);
	
	fseek(fp, 0, SEEK_SET);							// +1한거 헤더에 갱신	
	fwrite(&record_num, sizeof(int), 1, fp);

	writeRecord(fp, &temp_s, record_num-1);
}

//
// 학생 레코드 파일에서 검색 키값을 만족하는 레코드가 존재하는지를 sequential search 기법을 
// 통해 찾아내고, 이를 만족하는 모든 레코드의 내용을 출력한다. 검색 키는 학생 레코드를 구성하는
// 어떤 필드도 가능하다. 내부적으로 readRecord() 함수를 호출하여 sequential search를 수행한다.
// 검색 결과를 출력할 때 반드시 printRecord() 함수를 사용한다. (반드시 지켜야 하며, 그렇지
// 않는 경우 채점 프로그램에서 자동적으로 틀린 것으로 인식함)
//
void searchRecord(FILE *fp, enum FIELD f, char *keyval);
void printRecord(const STUDENT *s);

//
// 레코드의 필드명을 enum FIELD 타입의 값으로 변환시켜 준다.
// 예를 들면, 사용자가 수행한 명령어의 인자로 "NAME"이라는 필드명을 사용하였다면 
// 프로그램 내부에서 이를 NAME(=1)으로 변환할 필요성이 있으며, 이때 이 함수를 이용한다.
//
enum FIELD getFieldID(char *fieldname){
	if(fieldname == "ID"){
		return ID;
	}
	else if(fieldname == "NAME"){
		return NAME;
	}
	else if(fieldname == "DEPT"){
		return DEPT;
	}
	else if(fieldname == "ADDR"){
		return ADDR;
	}
	else if(fieldname == "EMAIL"){
		return EMAIL;
	}
	else{
		return -1;
	}
}

void main(int argc, char *argv[])
{
	FILE *fp;			// 모든 file processing operation은 C library를 사용할 것
	char* input_id, input_name, input_dept, input_addr, input_email;
	if(strcmp(argv[1],"-a") == 0){	// append
		appendRecord(fp, argv[2], argv[3], argv[4], argv[5], argv[6]);
	}
	else{
		STUDENT temp_s;
		readRecord(fp,&temp_s,0);
	}
}

void printRecord(const STUDENT *s)
{
	printf("%s | %s | %s | %s | %s\n", s->id, s->name, s->dept, s->addr, s->email);
}
