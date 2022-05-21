#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int BRANCH_NUM = 6;
const int MAX_ROOM_NUM = 10;
char BRANCH_INFO_FILE_NAME[] = "./branch_info.txt";
char ROOM_INFO_FILE_NAME[] = "./room_info.txt";

FILE *branch_info;
char branch_info_arr[6] = {'a','a','a','a','a','a'};
bool is_branch_able[6];

// input func
int  get_user_input(void);              // 사용자 입력 받기
void wrong_input(void);                 // 입력 오류시
void exit_program(void);                // 프로그램 종료
// init 
void mode_selection(void);              // 초기 모드 선택 화면
// admin    
void mode_admin(void);                  // 관리자 모드 작업선택
void mode_add_branch(int);             // 지점 추가 모드
void mode_mod_branch(int);             // 지점 수정 모드
void mode_del_branch(int);             // 지점 삭제 모드
void get_branch_info(void);             // 지점 정보 불러오기
// user 
void mode_user(void);                   // 사용자 모드 시작
// file manage  
void open_file(FILE**, char*);          // 파일 열기
bool is_file_empty(FILE*);              // 파일이 비어있는지 검사
void init_branch_info(FILE*);           // branch_info.txt 초기화
void set_branch_info(char[]);           // brnach_info.txt 갱신

int main(void){
    while(1) mode_selection();

    return 0;
}

void exit_program(void){
    printf(">> 프로그램을 종료합니다...\n");
    exit(0);
}

void wrong_input(void){
    printf(">> 올바르지 않은 입력입니다...\n");
    exit_program();
}

int get_user_input(void){
    int input;
    scanf("%d", &input);
    return input;
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

// 지점 추가 모드
void mode_admin(void){
    get_branch_info();                  // branch_info_arr 에 정보 저장
    printf("--------<관리자 모드>--------\n");
    printf("---------<지점 현황>---------\n");
    for (int i = 1; i <= BRANCH_NUM; i++) {
        printf("    지점 %d", i);
        if(is_branch_able[i]){                  // 지점 개설 되었으면
            printf(" (개설됨)\n");
        }
        else { printf(" (개설되지 않음)\n"); }  // 개설 이전이면
    }
    printf("프로그램 종료 : (0)\n");
    printf("-----------------------------\n");
    printf("지점을 선택하세요.\n>> ");          // 지점선택 입력 받기
    int input_branch_selection = get_user_input();
    if(input_branch_selection == 0) exit_program();
    printf("%d 지점에 대한 작업을 선택하세요.\n", input_branch_selection);   // 선택된 지점에 대한 작업 입력 받기
    printf(" (1) 추가    (2) 수정    (3) 삭제   (4) 프로그램 종료\n");
    printf(">> ");
    switch(get_user_input()){
        case 1:
            mode_add_branch(input_branch_selection);
            break;
        case 2:
            // mode_mod_branch(input_branch_selection);
            break;
        case 3:
            // mode_del_branch(input_branch_selection);
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
    if(is_branch_able[branch_num]){          // 이미 개설 된 지점인지 검사
        printf(">> 이미 개설된 지점입니다.\n");
        return;
    }
    // 개설되지 않은 지점이면
    branch_info_arr[branch_num] = '1';
    set_branch_info(branch_info_arr);
    printf("%d 지점을 개설했습니다.\n", branch_num);
}

// 지점 수정 모드
void mode_mod_branch(int branch_num){

}

// 지점 삭제 모드
void mode_del_branch(int branch_num){

}    

// 지점 정보 불러오기
void get_branch_info(void){
    open_file(&branch_info ,BRANCH_INFO_FILE_NAME);         // 파일 열기
    if(is_file_empty(branch_info)){                         // 파일이 비어있으면
        init_branch_info(branch_info);                      // 초기화 (지점 없음)
        open_file(&branch_info ,BRANCH_INFO_FILE_NAME);     // 파일 열기
    }
    
    fseek(branch_info, 0, SEEK_SET);            // 파일 포인터 시작점 설정
    fread(branch_info_arr,strlen(branch_info_arr), sizeof(char),branch_info);   // 읽기
    for (int i = 0; i < 6; i++) {
        if(branch_info_arr[i] == '0'){          // char 형에서 bool 형 배열로 변환
            is_branch_able[i] = false;          
        }
        else { is_branch_able[i] = true; }
    }

    fclose(branch_info);                        // 정보 다 읽고 파일 닫기
}

// 파일이 비어있는지 검사
bool is_file_empty(FILE *filestream){
    fseek(filestream, 0, SEEK_END);
    int file_size = ftell(filestream);

    if(file_size < 1) return true;          // 파일 비었음
    return false;                           // 파일 안비었음
}

// branch_info.txt. 초기화
void init_branch_info(FILE* filestream){
    char branch_info_init_string[] = "000000";
    if(fwrite(branch_info_init_string, strlen(branch_info_init_string), sizeof(char),branch_info) < 1){
        printf("NULL!\n");
        exit(1);
    }
    fclose(branch_info);               // 파일 닫아서 저장
}

// branch_info.txt 갱신
void set_branch_info(char new_branch_info[]){
    open_file(&branch_info ,BRANCH_INFO_FILE_NAME);         // brnach_info.txt 파일 열기
    if(fwrite(new_branch_info, strlen(new_branch_info), sizeof(char),branch_info) < 1){
        printf("NULL!\n");
        exit(1);
    }
    fclose(branch_info);               // 파일 닫아서 저장
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
