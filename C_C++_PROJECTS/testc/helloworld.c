#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define room_format "./branch_%d_test_%d_info.dat"
#define SIZE_BRANCH_ABLE 6
#define SIZE_ROOM_ABLE 5
#define SIZE_ROOM_CAPACITY 10
#define SIZE_RESERVE_CNT 10
#define SIZE_USER_ID 10
#define SIZE_RESERVED_DATE 4
#define SIZE_RESERVED_TIME 4
#define SIZE_USING_TIME 4
#define SIZE_RESERVE 24
#define SIZE_ROOM_INFO_FILE_NAME 26
 
typedef struct _RESERVE{
    char user_id[10];
    int reserved_date;
    int reserved_time;
    int using_time;
} RESERVE;

int cnt = 0;

void read_reserve(int, int, int, RESERVE*);         // n번지점 n번 룸 n번째 예약 읽어오기
void write_reserve(int, int, int, RESERVE*);        // n번지점 n번 룸 n번째 예약 쓰기
void delete_reserve(int, int, int);                 // n번지점 n번 룸 n번째 예약 지우기
void open_file(FILE** filestream, char filename[]){
    FILE* check_file_exist = fopen(filename,"r");   // 인자로 받은 파일 열기 시도
    if(check_file_exist == NULL){                   // 파일이 없으면
        check_file_exist = fopen(filename, "w+");   // 파일 생성
        fclose(check_file_exist);                   // 생성된 파일 닫기
    }
    else{ fclose(check_file_exist); }

    *filestream = fopen(filename,"r+");     // 파일 열기
    if(filestream == NULL){                 // 잘 열렸는지 검사
        printf("ERROR open_file() (file name: \"%s\")\n",filename);
        exit(1);
    }
}
int main()
{
    char* filename = (char*)malloc(28);
    sprintf(filename, room_format, 1, 2);
    printf("%s\n", filename);

    FILE* fp;
    fp = fopen(filename,"a+");
    fseek(fp, 0 ,SEEK_SET);
    RESERVE r;

    strcpy(r.user_id, "user_id1");
    r.reserved_date = 220511;
    r.reserved_time = 11;
    r.using_time = 1;
    write_reserve(1,2,0, &r); cnt++;

    strcpy(r.user_id, "user_id2");
    r.reserved_date = 220512;
    r.reserved_time = 12;
    r.using_time = 2;
    write_reserve(1,2,1, &r); cnt++;

    strcpy(r.user_id, "user_id3");
    r.reserved_date = 220513;
    r.reserved_time = 13;
    r.using_time = 3;
    write_reserve(1,2,2, &r); cnt++;
    read_reserve(1,2,0,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);
    read_reserve(1,2,1,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);
    read_reserve(1,2,2,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);
    
    delete_reserve(1,2,1);

    read_reserve(1,2,0,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);
    read_reserve(1,2,1,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);
    read_reserve(1,2,2,&r);
    printf("%s,%d,%d,%d\n",r.user_id, r.reserved_date,r.reserved_time,r.using_time);

}

// n번지점 n번 룸 n번째 예약 읽어오기
void read_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*) malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename,room_format,branch_num, room_num);
    open_file(&fp,filename);
    fseek(fp, SIZE_RESERVE*rnn,SEEK_SET);
    fread(r, SIZE_RESERVE, 1, fp);
    free(filename);
    fclose(fp);
}                
// n번지점 n번 룸 n번째 예약 쓰기  
void write_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*) malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename,room_format,branch_num, room_num);
    open_file(&fp,filename);
    fseek(fp, SIZE_RESERVE*rnn,SEEK_SET);
    fwrite(r, SIZE_RESERVE, 1, fp);
    free(filename);
    fclose(fp);
}      
// n번지점 n번 룸 n번째 예약 지우기
void delete_reserve(int branch_num, int room_num, int rnn){
    FILE* fp;
    char* filename = (char*)malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename, room_format, branch_num, room_num);
    open_file(&fp,filename);
    int reserve_cnt = cnt;
    RESERVE r;
    read_reserve(branch_num,room_num, (reserve_cnt-1), &r);
    write_reserve(branch_num,room_num, rnn, &r);
    fclose(fp);
}