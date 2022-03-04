// #define DEBUG
#include <iostream>
#define MAX 10000

using namespace std;


int T[MAX+1][3]={};             // 트리 정보 배열
int X[MAX+1];                   // X[n] : x좌표가 n인 노드번호
int Y[MAX+1];                   // Y[n] : x좌표 n에 위치한 노드의 Y값
int depth = 1;
int level = 1;
int MAX_level =1;

void inorder_traverse(int curr_node){       // 트리를 중위 순회하며 X좌표 설정
    if(curr_node == -1){                    // 더미 노드면
        return;
    }
    if(T[curr_node][1] != -1 || T[curr_node][2] != -1){     // 자식이 하나라도 존재하면
        level++;
        inorder_traverse(T[curr_node][1]);
        level--;
        X[depth] = curr_node;
        Y[depth] = level;
        depth++;
        level++;
        inorder_traverse(T[curr_node][2]);
        level--;
    }
    else{                                                   // 꼬리 노드면
        X[depth] = curr_node;
        Y[depth] = level;
        depth++;
        if(level > MAX_level) MAX_level = level;            // 최대 level 갱신
    }
}

int main(void) {
    int n;      // 노드의 개수
    cin >> n;   // 입력

    int node_input;
    for(int i=0; i<n; i++){     // n 줄 입력
        cin >> node_input;      // 배열의 n째 줄에 n번 노드 저장
        T[node_input][0] = node_input;
        cin >> T[node_input][1];
        cin >> T[node_input][2];
    }

    #ifdef DEBUG
    cout << "T : " << endl;
    for(int i=1; i<n+1; i++){
        for(int j=0; j<3; j++){
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
    #endif
    
    int LEV[n+1];               // 노드의 레벨을 담을 배열
    for(int i=1; i<n+1; i++){   // 모두 1로 초기화
        LEV[i] = 1;
    }

    int head_node_num=-1;       // head node의 번호
    // head node 탐색
    for(int i=1; i<n+1; i++){
        if(T[i][1] != -1){      // 왼쪽 자식 노드가 있으면
            LEV[T[i][1]] += 1;  // 해당 자식 노드의 레벨 +1 (2로 조정됨)
        }
        if(T[i][2] != -2){      // 오른쪽 자식 노드가 있으면
            LEV[T[i][2]] += 1;  // 해당 자식 노드의 레벨 +1 (2로 조정됨)
        }
    }
    for(int i=1; i<n+1; i++){
        if(LEV[i]==1){          // 레벨이 1이면
            head_node_num = i;  // head node로 지정
            break;
        }
    }

    // LEV, head_node_num 출력
    #ifdef DEBUG
    cout << "LEV : ";
    for(int i=1; i<n+1; i++){
        cout << LEV[i] << ',';
    }
    cout << endl;
    cout << "head_node_num : " << head_node_num << endl;
    #endif

    inorder_traverse(head_node_num);

    // X, Y, MAX_level 출력
    #ifdef DEBUG
    cout << "X : ";
    for(int i=1; i<n+1; i++){
        cout << X[i] << ',';
    }
    cout << endl;
    cout << "Y : ";
    for(int i=1; i<n+1; i++){
        cout << Y[i] << ',';
    }
    cout << endl;
    cout << "MAX_level : ";
    cout << MAX_level;
    cout << endl;
    #endif

    int first_node = -1;
    int width[MAX_level+1];             // width[n] : level n의 너비
    for(int i=1; i< MAX_level+1; i++){  
        width[i] = 1;                   // 1로 초기화
    }
    for(int i=1; i<MAX_level+1; i++){   // 모든 level에 대해
        for(int j=1; j<n+1; j++){       // 모든 노드에 대해
            if(Y[j] == i){              // 해당 level 이면
                if(first_node == -1){   // 첫 노드가 존재하지 않으면
                    first_node = j;
                }
                else if(width[i] < j - first_node+1){     // 너비 최대값보다 크면
                    width[i] = j - first_node+1;          // 갱신
                }
            }
        }
        first_node = -1;     
    }

    int MAX_width_idx = -1;
    int MAX_width = -1;
    for(int i=1; i<MAX_level+1; i++){
        if(width[i] > MAX_width){
            MAX_width = width[i];
            MAX_width_idx = i;
        }
    }

    cout << MAX_width_idx << " " << MAX_width;

    return 0;
}
