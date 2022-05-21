#include <stdio.h>		// �ʿ��� header file �߰� ����
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

	fp = fopen(filename, "r+");						//���� ����
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	int file_size=-1;								// ���� ������ �˻�
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	printf("file_size : %d\n", file_size);
	if(file_size <= 0){								// �������̸�
		fseek(fp, 0, SEEK_SET);
		int header = 0;							// ��� �߰�
		fwrite(&header, sizeof(int), 1, fp);
	}

	fseek(fp,0,SEEK_SET);							// ������� ����� ���ڵ� ���� ��������
	int record_num;
	fread(&record_num, sizeof(int), 1, fp);
	// printf("recordnum[d] : %d\n", record_num);

	record_num++;									// ���� +1
	// printf("recordnum[d] : %d\n", record_num);
	
	fseek(fp, 0, SEEK_SET);							// +1�Ѱ� ����� ����	
	fwrite(&record_num, sizeof(int), 1, fp);

	writeRecord(fp, &temp_s, record_num-1);
}

//
// �л� ���ڵ� ���Ͽ��� �˻� Ű���� �����ϴ� ���ڵ尡 �����ϴ����� sequential search ����� 
// ���� ã�Ƴ���, �̸� �����ϴ� ��� ���ڵ��� ������ ����Ѵ�. �˻� Ű�� �л� ���ڵ带 �����ϴ�
// � �ʵ嵵 �����ϴ�. ���������� readRecord() �Լ��� ȣ���Ͽ� sequential search�� �����Ѵ�.
// �˻� ����� ����� �� �ݵ�� printRecord() �Լ��� ����Ѵ�. (�ݵ�� ���Ѿ� �ϸ�, �׷���
// �ʴ� ��� ä�� ���α׷����� �ڵ������� Ʋ�� ������ �ν���)
//
void searchRecord(FILE *fp, enum FIELD f, char *keyval);
void printRecord(const STUDENT *s);

//
// ���ڵ��� �ʵ���� enum FIELD Ÿ���� ������ ��ȯ���� �ش�.
// ���� ���, ����ڰ� ������ ��ɾ��� ���ڷ� "NAME"�̶�� �ʵ���� ����Ͽ��ٸ� 
// ���α׷� ���ο��� �̸� NAME(=1)���� ��ȯ�� �ʿ伺�� ������, �̶� �� �Լ��� �̿��Ѵ�.
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
	FILE *fp;			// ��� file processing operation�� C library�� ����� ��
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
