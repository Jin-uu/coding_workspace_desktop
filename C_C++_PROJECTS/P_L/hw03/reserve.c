#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>        // write(), close(), ftruncate()
#include <io.h>

// 필드 크기 상수
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
// 최대값 상수
const int BRANCH_NUM = 6;
const int MAX_ROOM_NUM = 5;

typedef struct _RESERVE{
    char user_id[10];
    int reserved_date;
    int reserved_time;
    int using_time;
} RESERVE;

// #define branch_format "./branch_%d_info.dat"
#define room_format "./branch_%d_room_%d_info.dat"

// 파일명
char BRANCH_INFO_FILE_NAME[] = "./branch_info.dat";
char BRANCH_1_INFO[] = "./branch_1_info.dat";
char BRANCH_2_INFO[] = "./branch_2_info.dat";
char BRANCH_3_INFO[] = "./branch_3_info.dat";
char BRANCH_4_INFO[] = "./branch_4_info.dat";
char BRANCH_5_INFO[] = "./branch_5_info.dat";
char BRANCH_6_INFO[] = "./branch_6_info.dat";

char branch_able_char[6] = {'a','a','a','a','a','a'};
bool branch_able_arr[6];
char room_able_char[SIZE_ROOM_ABLE] = {'i','i','i','i','i'};          // curr번 지점의 room 생성 여부
bool room_able_arr[5];
char  room_capacity_char[SIZE_ROOM_CAPACITY] = {'i','i','i','i','i','i','i','i','i','i'};      // 현재 지점의 room의 최대인원 정보
int room_capacity_arr[5];
char  room_reserve_cnt_char[SIZE_RESERVE_CNT] = {'i','i','i','i','i','i','i','i','i','i'};        // 현재 지점의 room의 예약 개수 정보
int room_reserve_cnt_arr[5];
// input func
int  get_user_input(void);                      // 사용자 입력 받기
void wrong_input(void);                         // 입력 오류시
void exit_program(void);                        // 프로그램 종료
//          
void mode_selection(void);                      // 초기 모드 선택 화면
// admin        
void mode_admin(void);                          // 관리자 모드 초기 화면
void mode_add_branch(int);                      // 지점 추가 모드
void mode_mod_branch(int);                      // 지점 수정 모드
void mode_del_branch(int);                      // 지점 삭제 모드
void mode_add_room(int, int);                   // 스터디 룸 추가 모드
void mode_mod_room(int, int);                   // 스터디 룸 수정 모드
void mode_del_room(int, int);                   // 스터디 룸 삭제 모드

// user 
void mode_user(void);                           // 사용자 모드 초기 화면
// file manage  
void open_file(FILE**, char*);                      // 파일 열기
void get_branch_able_info(void);                    // 지점 개설 여부 정보 불러오기
void get_branch_info(int);                          // 특정 지점 정보 불러와서 배열에 저장
bool is_file_empty(FILE*);                          // 파일이 비어있는지 검사
void init_branch_able_info(FILE*);                  // branch_able_info.dat 초기화
void init_branch_info(int);                         // branch_n_info.dat 초기화
void init_room_info(int,int);                       // branch_n_room_n_info.dat 초기화
void set_branch_able_info(char[]);                  // branch_able_info.dat 지점 개설 여부 갱신
void set_room_able_info(char[],int);                // branch_n_info.dat 스터디 룸 개설 여부 갱신
void set_room_capacity_info(char[], int);           // branch_n_info.dat 스터디 룸 최대인원 갱신
void set_room_reserve_cnt_info(char[], int);        // branch_n_info.dat 스터디 룸 예약 개수 갱신
void delete_file(char[]);                           // 파일 삭제
void read_reserve(int, int, int, RESERVE*);         // n번지점 n번 룸 n번째 예약 읽어오기
void write_reserve(int, int, int, RESERVE*);        // n번지점 n번 룸 n번째 예약 쓰기
void delete_reserve(int, int, int, RESERVE*);       // n번지점 n번 룸 n번째 예약 지우기
// translate
char* get_branch_file_name(int);                    // 지점 번호주면 파일명 반환
// FILE* get_file_pointer_with_num(int);               // 지점 번호주면 파일포인터 반환
char* get_room_file_name(int, int);                 // n번 지점의 n번 스터디룸 파일명 반환



int main(void){
    while(1) mode_selection();
    // RESERVE* r = (RESERVE* )malloc(sizeof(RESERVE));

    // strcpy(r->user_id, "user_id");
    // r->reserved_date = 220515;
    // r->reserved_time = 15;
    // r->using_time = 2;

    // write_reserve(1,2,0,r);
    // read_reserve(1,2,0,r);
    // printf("%s,%d,%d,%d\n",r->user_id, r->reserved_date,r->reserved_time,r->using_time);

    // strcpy(r->user_id, "user_id2");
    // r->reserved_date = 220516;
    // r->reserved_time = 13;
    // r->using_time = 3;
    
    // write_reserve(1,2,1,r);
    // read_reserve(1,2,1,r);
    // printf("%s,%d,%d,%d\n",r->user_id, r->reserved_date,r->reserved_time,r->using_time);

    return 0;
}

int get_user_input(void){
    int input;
    scanf("%d", &input);
    return input;
}

void wrong_input(void){
    printf(">> 올바르지 않은 입력입니다...\n");
    exit_program();
}

void exit_program(void){
    printf(">> 프로그램을 종료합니다...\n");
    exit(0);
}


// 초기 모드 선택 화면
void mode_selection(void){
    printf("------------<모드 선택>------------\n");
    printf("        1. 관리자 모드 (1)\n");
    printf("        2. 사용자 모드 (2)\n");
    printf("        3. 프로그램 종료 (0)\n");
    printf("-----------------------------------\n");
    printf("모드를 선택하세요.\n>> ");
    switch(get_user_input()){
        case 1:
            mode_admin();
            break;
        case 2:
            // mode_user();
            break;
        case 0:
            exit_program();
            break;
        default:
            wrong_input();            
    }
}

// 관리자 모드 초기 화면
void mode_admin(void){
    get_branch_able_info();                  // branch_able_char 에 정보 저장
    printf("--------<관리자 모드>--------\n");
    printf("---------<지점 현황>---------\n");
    for (int i = 1; i <= BRANCH_NUM; i++) {
        printf("    지점 %d", i);
        if(branch_able_arr[i-1]){                  // 지점 개설 되었으면
            printf(" (개설됨)\n");
        }
        else { printf(" (개설되지 않음)\n"); }  // 개설 이전이면
    }
    printf("프로그램 종료 : (0)\n");
    printf("-----------------------------\n");
    printf("지점을 선택하세요.\n>> ");          // 지점선택 입력 받기
    int input_branch_selection = get_user_input();
    if(input_branch_selection == 0) exit_program();
    printf("지점 %d에 대한 작업을 선택하세요.\n", input_branch_selection);   // 선택된 지점에 대한 작업 입력 받기
    printf(" (1) 추가    (2) 수정    (3) 삭제   (4) 프로그램 종료\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_branch(input_branch_selection);
            break; 
        case 2:
            mode_mod_branch(input_branch_selection);
            break;
        case 3:
            mode_del_branch(input_branch_selection);
            break;
        case 4:
            exit_program();
            break;
        default:
            wrong_input();
    }
}     

// 지점 추가 모드
void mode_add_branch(int branch_num){
    if(branch_able_arr[branch_num-1]){          // 이미 개설 된 지점인지 검사
        printf(">> 이미 개설된 지점입니다.\n");
        return;
    }
    // 개설되지 않은 지점이면
    branch_able_char[branch_num-1] = '1';
    set_branch_able_info(branch_able_char);
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fclose(fp);
    printf("지점 %d을 개설했습니다.\n", branch_num);
}

// 지점 수정 모드
void mode_mod_branch(int branch_num){
    if(!branch_able_arr[branch_num-1]){          // 개설 여부 확인
        printf(">> 아직 개설되지 않은 지점입니다.\n");
        return;
    }
    get_branch_info(branch_num);
    printf("---------<지점%d 현황>---------\n", branch_num);
    for (int i = 1; i <= MAX_ROOM_NUM; i++) {
        printf("    스터디 룸 %d", i);
        if(room_able_arr[i-1]){                     // 스터디 룸 개설 되었으면
            printf("(허용인원: %d, 예약 현황: %d개)\n",room_capacity_arr[i-1],room_reserve_cnt_arr[i-1]);
        }
        else { printf(" (개설되지 않음)\n"); }      // 개설 이전이면
    }
    printf("프로그램 종료 : (0)\n");
    printf("-----------------------------\n");
    printf("작업할 스터디 룸 번호를 선택하세요.\n>> ");    // 스터디룸 번호 입력 받기
    int input_room_selection = get_user_input();
    if(input_room_selection == 0) exit_program();
    if(input_room_selection<0 || input_room_selection>5) wrong_input();

    printf(">>스터디 룸 %d에 대한 작업을 선택하세요.\n", input_room_selection);   // 선택된 지점에 대한 작업 입력 받기
    printf(" (1) 추가    (2) 수정    (3) 삭제   (4) 프로그램 종료\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_room(branch_num, input_room_selection);
            break;  
        case 2:
            mode_mod_room(branch_num, input_room_selection);
            break;
        case 3:
            mode_del_room(branch_num, input_room_selection);
            break;
        case 4:
            exit_program();
            break;
        default:
            wrong_input();
    }

}
// 스터디 룸 추가 모드
void mode_add_room(int branch_num, int room_num){
    if(room_able_arr[room_num-1]){          // 이미 개설 된 스터디 룸인지 검사
        printf(">> 이미 개설된 스터디 룸입니다.\n");
        return;
    }
    // 개설되지 않은 지점이면
    printf(">> 스터디 룸 %d의 최대 허용 인원을 입력하세요.(1~10)\n>>",room_num);
    int max_capacity = get_user_input();
    char ten, one;
    if(max_capacity>10 || max_capacity < 1){
        wrong_input();
    }
    else if(max_capacity == 10){
        ten = '1'; one = '0';
    }
    else{
        ten = '0'; one = max_capacity+'0';
    }

    room_able_char[room_num-1] = '1';
    room_capacity_char[(room_num-1)*2] = ten; room_capacity_char[(room_num-1)*2+1] = one;
    room_reserve_cnt_char[(room_num-1)*2] = '0'; room_reserve_cnt_char[(room_num-1)*2+1] = '0';
    set_room_able_info(room_able_char, branch_num);
    set_room_capacity_info(room_capacity_char,branch_num);
    set_room_reserve_cnt_info(room_reserve_cnt_char,branch_num);
    
    char* filename = (char*)malloc(28);
    sprintf(filename, room_format, branch_num, room_num);
    FILE* temp_fp;      
    open_file(&temp_fp, filename);
    fclose(temp_fp);
    printf("스터디 룸 %d을 개설했습니다.\n", room_num);
}            
// 스터디 룸 수정 모드
void mode_mod_room(int branch_num, int room_num){
    if(!room_able_arr[room_num-1]){          // 개설 된 지점인지 검사
        printf(">> 개설되지 않은 스터디 룸입니다.\n");
        return;
    }
    printf(">> 스터디 룸 %d의 변경할 최대 인원 수를 입력하세요. (현재 : %d)\n>>",room_num,room_capacity_arr[room_num]);
    int max_capacity = get_user_input();
    char ten,one;
    if(max_capacity>10 || max_capacity < 1){
        wrong_input();
    }
    else if(max_capacity == 10){
        ten = '1'; one = '0';
    }
    else{
        ten = '0'; one = max_capacity+'0';
    }
    room_capacity_char[(room_num-1)*2] = ten; room_capacity_char[(room_num-1)*2+1] = one;
    set_room_capacity_info(room_capacity_char, branch_num);
}             
// 스터디 룸 삭제 모드
void mode_del_room(int branch_num, int room_num){
    if(!room_able_arr[room_num-1]){          // 이미 삭제 된 지점인지 검사
        printf(">> 이미 삭제된 스터디 룸입니다.\n");
        return;
    }

    // branch_%d_info.dat. 초기화
    room_able_char[room_num-1] = '0';
    room_capacity_char[room_num-1] = '0';
    room_reserve_cnt_char[room_num-1] = '0';
    set_room_able_info(room_able_char, branch_num);
    set_room_capacity_info(room_capacity_char, branch_num);
    set_room_reserve_cnt_info(room_reserve_cnt_char,branch_num);
    // branch_%d_room_%d_info.dat 삭제
    char* filename = (char*)malloc(28);
    sprintf(filename, room_format, branch_num, room_num);            
    delete_file(filename);
    printf("스터디 룸 %d을 삭제했습니다.\n", room_num);
}                 

// 지점 삭제 모드
void mode_del_branch(int branch_num){
    if(!branch_able_arr[branch_num-1]){          // 이미 삭제 된 지점인지 검사
        printf(">> 이미 삭제된 지점입니다.\n");
        return;
    }

    branch_able_char[branch_num-1] = '0';
    set_branch_able_info(branch_able_char);
    // branch_%d_room_%d_info.dat 삭제
    get_branch_info(branch_num);
    for (int i = 0; i < 6; i++) {
        if(room_able_arr[i]){
            char* filename = (char*)malloc(28);
            sprintf(filename, room_format, branch_num, i+1);            
            delete_file(filename);
        }
    }
    // branch_%d_info.dat 삭제
    delete_file(get_branch_file_name(branch_num));
    
    printf("지점 %d을 삭제했습니다.\n", branch_num);
}

// 사용자 모드 초기 화면
void mode_user(void){

}

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

// 지점 정보 불러오기
void get_branch_able_info(void){
    FILE* fp;
    open_file(&fp ,BRANCH_INFO_FILE_NAME);         // 파일 열기
    if(is_file_empty(fp)){                         // 파일이 비어있으면
        init_branch_able_info(fp);                 // 초기화 (지점 없음)
        open_file(&fp ,BRANCH_INFO_FILE_NAME);     // 파일 열기
    }
    
    fseek(fp, 0, SEEK_SET);            // 파일 포인터 시작점 설정
    fread(branch_able_char,strlen(branch_able_char), sizeof(char),fp);   // 읽기
    for (int i = 0; i < 6; i++) {
        if(branch_able_char[i] == '0'){             // char 형에서 bool 형 배열로 변환
            branch_able_arr[i] = false;          
        }
        else { branch_able_arr[i] = true; }
    }

    fclose(fp);                        // 정보 다 읽고 파일 닫기
}

// 파일이 비어있는지 검사
bool is_file_empty(FILE *filestream){
    fseek(filestream, 0, SEEK_END);
    int file_size = ftell(filestream);

    if(file_size < 1) return true;          // 파일 비었음
    return false;                           // 파일 안비었음
}

// branch_able_info.txt. 초기화
void init_branch_able_info(FILE* filestream){
    char branch_able_info_init_string[] = "000000";
    if(fwrite(branch_able_info_init_string, strlen(branch_able_info_init_string), sizeof(char),filestream) < 1){
        printf("error in init branch able info!\n");
        exit(1);
    }
    fclose(filestream);               // 파일 닫아서 저장
}

void init_branch_info(int branch_num){
    FILE* fp;
    open_file(&fp , get_branch_file_name(branch_num));
    char branch_info_room_able_init_string[] ="00000";
    char branch_info_room_capacity_init_string[] ="0000000000";
    char branch_info_room_reserve_cnt_init_string[] ="0000000000";
    set_room_able_info(branch_info_room_able_init_string,branch_num);
    set_room_capacity_info(branch_info_room_capacity_init_string,branch_num);
    set_room_reserve_cnt_info(branch_info_room_reserve_cnt_init_string,branch_num);
    fseek(fp,0,SEEK_SET);
    if(fwrite(branch_info_room_able_init_string,strlen(branch_info_room_able_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_able_char)!\n");
        exit(1);
    }
    fseek(fp,SIZE_ROOM_ABLE,SEEK_SET);
    if(fwrite(branch_info_room_capacity_init_string,strlen(branch_info_room_capacity_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_capacity)!\n");
        exit(1);
    }
    fseek(fp,SIZE_ROOM_ABLE + SIZE_ROOM_CAPACITY,SEEK_SET);
    if(fwrite(branch_info_room_reserve_cnt_init_string,strlen(branch_info_room_reserve_cnt_init_string), sizeof(char), fp) <1){
        printf("branch info init error(room_reserve_cnt)!\n");
        exit(1);
    }
    fclose(fp);
}
// branch_n_room_n_info.dat 생성
void init_room_info(int branch_num,int room_num){
    char* filename = (char*)malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename, room_format, branch_num, room_num);
    FILE* fp;
    open_file(&fp,filename);
    fclose(fp);
}                       

void get_branch_info(int branch_num){
    FILE* fp;    
    open_file(&fp ,get_branch_file_name(branch_num));         // 파일 열기
    if(is_file_empty(fp)){                                    // 파일이 비어있으면
        init_branch_info(branch_num);                         // 초기화 (지점 없음)
        // open_file(&fp ,get_branch_file_name(branch_num));     // 파일 열기
    }
    
    fseek(fp, 0, SEEK_SET);            // 파일 포인터 시작점 설정
    fread(room_able_char,strlen(room_able_char), sizeof(char),fp);   // 읽기    
    fseek(fp, SIZE_ROOM_ABLE, SEEK_SET);            // 파일 포인터 시작점 설정
    fread(room_capacity_char,strlen(room_capacity_char), sizeof(char),fp);   // 읽기    
    fseek(fp, SIZE_ROOM_ABLE + SIZE_ROOM_CAPACITY, SEEK_SET);            // 파일 포인터 시작점 설정
    fread(room_reserve_cnt_char,strlen(room_reserve_cnt_char), sizeof(char),fp);   // 읽기
    // printf("ra:%s\nrc:%s\nrcnt:%s\n", room_able_char, room_capacity_char, room_reserve_cnt_char);

    printf("room_able_arr[]: ");
    for (int i = 0; i < 5; i++) {
        if(room_able_char[i] == '0') room_able_arr[i] = false;
        else room_able_arr[i] = true;
        printf("%d ", room_able_arr[i]);
    }
    printf("\nroom_capacity_arr[]: ");
    for (int i = 0; i < 5; i++) {
        room_capacity_arr[i] = (room_capacity_char[i*2] - '0')*10 + (room_capacity_char[i*2+1] - '0');
        printf("%d ", room_capacity_arr[i]);
    }
    printf("\nreserve_cnt_arr[]: ");
    for (int i = 0; i < 5; i++) {
        room_reserve_cnt_arr[i] = (room_reserve_cnt_char[i*2] - '0')*10 + (room_reserve_cnt_char[i*2+1] - '0');
        printf("%d ", room_reserve_cnt_arr[i]);
    }
    printf("\n");
    fclose(fp);
}

// branch_able_info.txt 갱신
void set_branch_able_info(char new_branch_info[]){
    FILE* fp;
    open_file(&fp ,BRANCH_INFO_FILE_NAME);         // brnach_info.txt 파일 열기
    if(fwrite(new_branch_info, strlen(new_branch_info), sizeof(char),fp) < 1){
        printf("error in set branch able info!\n");
        exit(1);
    }
    fclose(fp);               // 파일 닫아서 저장
}  
// branch_n_info.dat 갱신
void set_room_able_info(char new_room_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    if(fwrite(new_room_info, strlen(new_room_info), sizeof(char),fp) < 1){
        printf("error in set room able info!\n");
        exit(1);
    }
    fclose(fp);               // 파일 닫아서 저장
}

void set_room_capacity_info(char new_room_capacity_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fseek(fp, SIZE_ROOM_ABLE, SEEK_SET);
    if(fwrite(new_room_capacity_info, strlen(new_room_capacity_info), sizeof(char),fp) < 1){
        printf("error in set room capacity info!\n");
        exit(1);
    }
    fclose(fp);               // 파일 닫아서 저장
}

void set_room_reserve_cnt_info(char new_room_reserve_cnt_info[], int branch_num){
    FILE* fp;
    open_file(&fp, get_branch_file_name(branch_num));
    fseek(fp, SIZE_ROOM_ABLE+SIZE_ROOM_CAPACITY, SEEK_SET);
    if(fwrite(new_room_reserve_cnt_info, strlen(new_room_reserve_cnt_info), sizeof(char),fp) < 1){
        printf("error in set room reserve_cnt info!\n");
        exit(1);
    }
    fclose(fp);               // 파일 닫아서 저장
}
// 파일 삭제
void delete_file(char filename[]){
    if(remove(filename)==0){
        return;
    }
    else{
        printf("error in remove file(%s)\n", filename);
        exit(1);
    } 

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
void delete_reserve(int branch_num, int room_num, int rnn, RESERVE* r){
    FILE* fp;
    char* filename = (char*)malloc(SIZE_ROOM_INFO_FILE_NAME);
    sprintf(filename, room_format, branch_num, room_num);
    open_file(&fp,filename);
    get_branch_info(branch_num);
    int reserve_cnt = room_reserve_cnt_arr[room_num];
    RESERVE r;
    read_reserve(branch_num,room_num, (reserve_cnt-1), &r);
    write_reserve(branch_num,room_num, rnn, &r);

    //TODO : reserve cnt -- 적용
    fclose(fp);
    free(filename);
}

int get_file_size(char filename[]){
    FILE* fp;
    fopen(fp, filename);
    int size = fseek(fp, 0, SEEK_END);
    fclose(fp);
    return size;
}

// 지점 번호주면 파일명 반환
char* get_branch_file_name(int branch_num){
    switch(branch_num){
        case 1:
            return BRANCH_1_INFO;
        case 2:
            return BRANCH_2_INFO;
        case 3:
            return BRANCH_3_INFO;
        case 4:
            return BRANCH_4_INFO;
        case 5:
            return BRANCH_5_INFO;
        case 6:
            return BRANCH_6_INFO;
    }
}

// n번 지점의 n번 스터디룸 파일명 반환
char* get_room_file_name(int branch_num, int room_num){
    char* file = (char*)malloc(sizeof(char)*30);
    sprintf(file,room_format, branch_num, room_num);
    return file;
}

// 지점 번호주면 파일포인터 반환
// FILE* get_file_pointer_with_num(int branch_num){
//     switch(branch_num){
//         case 1:
//             return branch_1_info;
//         case 2:
//             return branch_2_info;
//         case 3:
//             return branch_3_info;
//         case 4:
//             return branch_4_info;
//         case 5:
//             return branch_5_info;
//         case 6:
//             return branch_6_info;
//     }
// }

void pack(char* recordbuf, const RESERVE *s){
    sprintf(recordbuf,"%s#%s#%s#", s->user_id, s->reserved_time, s->using_time);
}

// void unpack(const char *recordbuf, RESERVE *s){
//     int idx=0;
//     int field_idx=0, field_num=0;
//     while(idx < SIZE_RESERVE){
//         switch(field_num){
//             case 0:
//                 s -> user_id[field_idx] = recordbuf[idx];
//                 s -> user_id[field_idx+1] = '\0';
//                 break;
//             case 1:
//                 s -> reserved_time[field_idx] = recordbuf[idx];
//                 s -> reserved_time[field_idx+1] = '\0';
//                 break;
//             case 2:
//                 s -> using_time[field_idx] = recordbuf[idx];
//                 s -> using_time[field_idx+1] = '\0';
//                 break;
//         }
//         field_idx++; idx++; field_idx=0;
//     }
// }