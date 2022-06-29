#include <stdio.h>		// 필요한 header file 추가 가능
#include <stdlib.h>
#include <string.h>
#include "student.h"

char filename[] = "records.dat";

int getLastListNum(FILE*);
int deleteRecord(FILE*, enum FIELD, char*);
int insertRecord(FILE*, char*, char*, char*, char*, char*);
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

//
// 학생 레코드 파일에서 "학번" 키값을 만족하는 레코드를 찾아서 이것을 삭제한다.
// 참고로, 검색 조건은 반드시 학번(ID)만을 사용한다. 레코드의 검색은 searchRecord() 함수와
// 유사한 방식으로 구현한다. 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int deleteRecord(FILE *fp, enum FIELD f, char *keyval){
	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error\n");
		return 0;
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	if(file_size <= 0){								// 빈파일이면
		HEADER h;
		h.records_num =0;
		h.next_rrn = -1;
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(HEADER), 1, fp);
	}
	fseek(fp,0,SEEK_SET);							// 헤더에서 저장된 레코드 개수 가져오기
	HEADER h;
	fread(&h, sizeof(HEADER), 1, fp);
	int cnt=0;
	for(int i=0; i<h.records_num; i++){
		STUDENT* read_s = (STUDENT*)malloc(sizeof(char)*RECORD_SIZE);
		fseek(fp, HEADER_SIZE + i*RECORD_SIZE, SEEK_SET);
		DEL d;
		fread(&d,sizeof(DEL), 1, fp);
		if(d.star == '*') continue;
		if(readRecord(fp,read_s,i) == 0){
			printf("error in readRecord()\n");
			return 0;
		}

		if(strcmp(read_s -> id, keyval) == 0){
			cnt++;
			DEL del_s;
			del_s.star = '*';
			del_s.next_rrn = -1;
			fseek(fp, HEADER_SIZE+RECORD_SIZE*i, SEEK_SET);
			fwrite(&del_s, sizeof(DEL), 1, fp);
			int last = getLastListNum(fp);

			if(last == -1){		// 첫 삭제인 경우
				HEADER mod_h;
				mod_h.records_num = h.records_num;
				mod_h.next_rrn = i;				
				fseek(fp, 0, SEEK_SET);
				fwrite(&mod_h, HEADER_SIZE,1, fp);
			}
			else{
				fseek(fp, HEADER_SIZE+RECORD_SIZE*last, SEEK_SET);
				del_s.star = '*';
				del_s.next_rrn = i;
				fwrite(&del_s, sizeof(DEL), 1, fp);
			}
		}		
	}
	if(cnt==0) return 0;
	return 1;
}


int getLastListNum(FILE *fp){
	int curr_del_rrn, cnt =0;
	HEADER h;
	fseek(fp,0,SEEK_SET);									// 헤더에서 저장된 레코드 개수 가져오기
	fread(&h, sizeof(HEADER), 1 , fp);
	curr_del_rrn = h.next_rrn;

	while(curr_del_rrn != -1){
		DEL d;
		fseek(fp, HEADER_SIZE + curr_del_rrn*RECORD_SIZE, SEEK_SET);
		fread(&d,sizeof(DEL), 1, fp); cnt++;
		if(d.next_rrn == -1) return curr_del_rrn;
		curr_del_rrn = d.next_rrn;

		if(cnt > h.records_num){
			printf("error in getLastListNum()\n");
			exit(1);
		}
	}

	return curr_del_rrn;
}

//
// 학생 레코드 파일에 새로운 레코드를 추가한다. 과제 설명서에서 언급한 대로, 삭제 레코드가
// 존재하면 반드시 삭제 레코드들 중 하나에 새로운 레코드를 저장한다. 삭제 레코드 리스트 관리와
// 삭제 레코드의 선택은 교재 방식을 따른다. 새로운 레코드의 추가는 appendRecord() 함수와 비슷한
// 방식으로 구현한다. 성공적으로 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
//
int insertRecord(FILE *fp, char *id, char *name, char *dept, char *addr, char *email){	
	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error\n");
		return 0;
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	if(file_size <= 0){								// 빈파일이면
		HEADER h;
		h.records_num =0;
		h.next_rrn = -1;
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(HEADER), 1, fp);
	}

	HEADER h;
	fseek(fp, 0, SEEK_SET);
	fread(&h, sizeof(HEADER), 1, fp);
	if(h.next_rrn  == -1){
		if(appendRecord(fp, id, name, dept, addr, email)==0) return 0;
	}
	else{
		int target = h.next_rrn;
		DEL d;
		fseek(fp, HEADER_SIZE + target*RECORD_SIZE, SEEK_SET);
		fread(&d, sizeof(DEL), 1, fp);
		STUDENT temp_s;
		strcpy(temp_s.id, id);
		strcpy(temp_s.name, name);
		strcpy(temp_s.dept, dept);
		strcpy(temp_s.addr, addr);
		strcpy(temp_s.email, email);
		writeRecord(fp, &temp_s, target);
		HEADER temp_h;
		temp_h.records_num = h.records_num;
		temp_h.next_rrn = d.next_rrn;
		fseek(fp, 0, SEEK_SET);
		fwrite(&temp_h, sizeof(HEADER), 1, fp);
	}
	return 1;
}

int readRecord(FILE *fp, STUDENT *s, int rrn){
	fp = fopen("records.dat","r+");
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	char* buf;
	buf = (char*)malloc(sizeof(char)*RECORD_SIZE+1);
	fseek(fp, HEADER_SIZE + RECORD_SIZE*rrn, SEEK_SET);
	int check = fread(buf, RECORD_SIZE, 1, fp);
	// printf("check:%d\n->",check);
	buf[RECORD_SIZE] = '\0';
	unpack(buf, s);
	// printRecord(s);
	free(buf);
	if(check == 1) return 1;
	else return 0;
}

void unpack(const char *recordbuf, STUDENT *s){
	char ch;
	int idx=0;
	int field_idx=0, field_num=0;
	while(idx < RECORD_SIZE){
		switch(field_num){
			case ID:
				// printf("id <- %c\n",recordbuf[idx]);
				s -> id[field_idx] = recordbuf[idx];
				s -> id[field_idx+1] = '\0';
				break;
			
			case NAME:
				// printf("name <- %c\n",recordbuf[idx]);
				s -> name[field_idx] = recordbuf[idx];
				s -> name[field_idx+1] = '\0';
				break;
			
			case DEPT:
				// printf("dept <- %c\n",recordbuf[idx]);
				s -> dept[field_idx] = recordbuf[idx];
				s -> dept[field_idx+1] = '\0';
				break;
			
			case ADDR:
				// printf("addr <- %c\n",recordbuf[idx]);
				s -> addr[field_idx] = recordbuf[idx];
				s -> addr[field_idx+1] = '\0';
				break;
			
			case EMAIL:
				// printf("email <- %c\n",recordbuf[idx]);
				s -> email[field_idx] = recordbuf[idx];
				s -> email[field_idx+1] = '\0';
				break;			
		}
		field_idx++;
		idx++;
		if(recordbuf[idx] == '#') {
			field_num++;
			idx++;
			field_idx=0;
		}
	}
}
int writeRecord(FILE *fp, const STUDENT *s, int rrn){
	char* buf;
	buf = malloc(sizeof(char)*RECORD_SIZE);
	pack(buf, s);
	// printf("rrn : %d\n", rrn);
	// printf("buf : %s\n", buf);
	
	fseek(fp, HEADER_SIZE+RECORD_SIZE*rrn, SEEK_SET);
	int check = fwrite(buf, RECORD_SIZE, 1, fp);
	// printf("write check:%d\n",check);
	free(buf);
	if(check == 1) return 1;
	else return 0;
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
	int check_1=1,check_2=1, check_3=1;

	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error in appendRecord()\n");
		exit(1);
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	if(file_size <= 0){								// 빈파일이면
		HEADER h;
		h.records_num =0;
		h.next_rrn = -1;
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(HEADER), 1, fp);
	}

	fseek(fp,0,SEEK_SET);							// 헤더에서 저장된 레코드 개수 가져오기
	int record_num;
	check_3 = fread(&record_num, sizeof(int), 1, fp);

	record_num++;									// 개수 +1
	
	fseek(fp, 0, SEEK_SET);							// +1한거 헤더에 갱신	
	check_1 = fwrite(&record_num, sizeof(int), 1, fp);

	writeRecord(fp, &temp_s, record_num-1);
	if(check_1 == 0 || check_2 == 0 || check_3==0) return 0;
	else return 1;
}

void __debug__print_all(FILE *fp){
	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	// printf("file_size : %d\n", file_size);
	if(file_size <= 0){								// 빈파일이면
		HEADER h;
		h.records_num =0;
		h.next_rrn = -1;
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(HEADER), 1, fp);
	}
	fseek(fp,0,SEEK_SET);							// 헤더에서 저장된 레코드 개수 가져오기
	HEADER h;
	fread(&h, sizeof(HEADER), 1, fp);
	printf("record_num : %d\n", h.records_num);
	printf("next_rrn : %d\n", h.next_rrn);
	

	for (int i = 0; i < h.records_num; i++) {
		STUDENT* read_s = (STUDENT*)malloc(sizeof(char)*RECORD_SIZE);
		fseek(fp, HEADER_SIZE + i*RECORD_SIZE, SEEK_SET);
		DEL d;
		fread(&d,sizeof(DEL), 1, fp);
		if(d.star == '*') {
			printf("(%d) --deleted record-- %c : %d\n", i, d.star, d.next_rrn);
			continue;
		}
		if(readRecord(fp,read_s,i) == 0){
			printf("error in readRecord()\n");
			exit(1);
		}
		printf("(%d) ",i);
		printRecord(read_s);		
		free(read_s);
	}	
}

//
// 학생 레코드 파일에서 검색 키값을 만족하는 레코드가 존재하는지를 sequential search 기법을 
// 통해 찾아내고, 이를 만족하는 모든 레코드의 내용을 출력한다. 검색 키는 학생 레코드를 구성하는
// 어떤 필드도 가능하다. 내부적으로 readRecord() 함수를 호출하여 sequential search를 수행한다.
// 검색 결과를 출력할 때 반드시 printRecord() 함수를 사용한다. (반드시 지켜야 하며, 그렇지
// 않는 경우 채점 프로그램에서 자동적으로 틀린 것으로 인식함)
//
void searchRecord(FILE *fp, enum FIELD f, char *keyval){
	fp = fopen(filename, "r+");						//파일 열기
	if(fp == NULL){
		printf("file open error\n");
		exit(1);
	}
	int file_size=-1;								// 파일 사이즈 검사
	fseek(fp,0,SEEK_END);
	file_size = ftell(fp);
	// printf("file_size : %d\n", file_size);
	if(file_size <= 0){								// 빈파일이면
		HEADER h;
		h.records_num =0;
		h.next_rrn = -1;
		fseek(fp, 0, SEEK_SET);
		fwrite(&h, sizeof(HEADER), 1, fp);
	}
	fseek(fp,0,SEEK_SET);							// 헤더에서 저장된 레코드 개수 가져오기
	int record_num;
	fread(&record_num, sizeof(int), 1, fp);
	// printf("record_num : %d\n", record_num);

	for (int i = 0; i < record_num; i++) {
		STUDENT* read_s = (STUDENT*)malloc(sizeof(char)*RECORD_SIZE);
		fseek(fp, HEADER_SIZE + i*RECORD_SIZE, SEEK_SET);
		DEL d;
		fread(&d,sizeof(DEL), 1, fp);
		if(d.star == '*') continue;
		if(readRecord(fp,read_s,i) == 0){
			printf("error in readRecord()\n");
			exit(1);
		}
		// debug
		// printf("read student %d : ",i);
		// printRecord(read_s);
		//
		switch(f){
			case ID:
				// printf("compairing (%s)==(%s)\n",read_s -> id, keyval);
				if(strcmp((read_s -> id), keyval) == 0){
					//debug
					// printf("일치(%d)) --> ",f);
					//
					printRecord(read_s);
				}
				break;
			case NAME:
				// printf("compairing (%s)==(%s)\n",read_s -> name, keyval);
				if(strcmp((read_s -> name), keyval) == 0){
					//debug
					// printf("일치(%d)) --> ",f);
					//
					printRecord(read_s);
				}
				break;
			case DEPT:
				// printf("compairing (%s)==(%s)\n",read_s -> dept, keyval);
				if(strcmp((read_s -> dept), keyval) == 0){
					//debug
					// printf("일치(%d)) --> ",f);
					//
					printRecord(read_s);
				}
				break;
			case ADDR:
				// printf("compairing (%s)==(%s)\n",read_s -> addr, keyval);
				if(strcmp((read_s -> addr), keyval) == 0){
					//debug
					// printf("일치(%d)) --> ",f);
					//
					printRecord(read_s);
				}
				break;
			case EMAIL:
				// printf("compairing (%s)==(%s)\n",read_s -> email, keyval);
				if(strcmp((read_s -> email), keyval) == 0){
					//debug
					// printf("일치(%d)) --> ",f);
					//
					printRecord(read_s);
				}
				break;
		}
		free(read_s);
	}
	
}
void printRecord(const STUDENT *s){
	printf("%s | %s | %s | %s | %s\n", s->id, s->name, s->dept, s->addr, s->email);
}

//
// 레코드의 필드명을 enum FIELD 타입의 값으로 변환시켜 준다.
// 예를 들면, 사용자가 수행한 명령어의 인자로 "NAME"이라는 필드명을 사용하였다면 
// 프로그램 내부에서 이를 NAME(=1)으로 변환할 필요성이 있으며, 이때 이 함수를 이용한다.
//
enum FIELD getFieldID(char *fieldname){
	if(strcmp(fieldname,"ID") == 0){
		return ID;
	}
	else if(strcmp(fieldname,"NAME") == 0){
		return NAME;
	}
	else if(strcmp(fieldname,"DEPT") == 0){
		return DEPT;
	}
	else if(strcmp(fieldname,"ADDR") == 0){
		return ADDR;
	}
	else if(strcmp(fieldname,"EMAIL") == 0){
		return EMAIL;
	}
	else{
		return -1;
	}
}

void main(int argc, char *argv[])
{
	FILE* fp;
	// fp = argv[2];			// 모든 file processing operation은 C library를 사용할 것
	// strcpy(filename, argv[2]);
	// printf("argv[2]: %s\n", argv[2]);
	// printf("filename: %s\n", filename);
	char* input_id, input_name, input_dept, input_addr, input_email;
	if(strcmp(argv[1],"-a") == 0){	// append
		if(appendRecord(fp, argv[3], argv[4], argv[5], argv[6], argv[7]) == 0){
			printf("error in appendRecord()\n");
			exit(1);
		}
	}
	else if(strcmp(argv[1],"-s")==0){
		STUDENT temp_s;
		char *ptr = strtok(argv[3],"=");
		// printf("prt len : %d\n", strlen(ptr));
		char *target_field = (char*) malloc(sizeof(char)*strlen(ptr));
		sprintf(target_field, "%s", ptr);
		// printf("target field : (%s)\n", target_field);          // 자른 문자열 출력

		ptr = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
		// printf("prt len : %d\n", strlen(ptr));
		char *target_key = (char*) malloc(sizeof(char)*strlen(ptr));
		sprintf(target_key, "%s", ptr);
		// printf("target key : (%s)\n", target_key);          // 자른 문자열 출력

		searchRecord(fp, getFieldID(target_field), target_key);

		free(target_field);
		free(target_key);
	}
	else if(strcmp(argv[1],"-d")==0){
		char *ptr = strtok(argv[3],"=");
		char *target_field = (char*) malloc(sizeof(char)*strlen(ptr));
		sprintf(target_field, "%s", ptr);
		ptr = strtok(NULL, " ");
		char *target_key = (char*) malloc(sizeof(char)*strlen(ptr));
		sprintf(target_key, "%s", ptr);
		if(deleteRecord(fp,ID,target_key) == 0){
			printf("error in deleteRecord()\n");
			exit(1);
		}
		free(target_field);
		free(target_key);
	}
	else if(strcmp(argv[1],"-i")==0){
		if(insertRecord(fp, argv[3], argv[4], argv[5], argv[6], argv[7]) == 0){
			printf("error in insertRecord()\n");
			exit(1);
		}
	}
	else if(strcmp(argv[1],"-z")==0){		// 디버깅용
		printf("debug--print--all\n");
		__debug__print_all(fp);
	}
	else {
		printf("option input error!!\n");
	}
}


