#include <bits/stdc++.h>

using namespace std;

int N, M;
int MAP[1010][1010];
int group[1010][1010];
vector<int> group_elem_num;
queue<pair<int,int>> togo;

void print_MAP(void){       // 디버깅용
    for(int i=0; i<=N+1; i++){
        for(int j=0; j<=M+1; j++) {
            cout << MAP[i][j] << "  ";
        }
        cout << "\n";
    }
}

void print_ans(void){       // 정답출력
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            if(MAP[i][j]==-1) cout << 0;
            else cout << MAP[i][j] % 10;
        }
        cout << "\n";
    }
}
void print_group(void){     // 디버깅용
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            cout << group[i][j] << " ";
        }
        cout << "\n";
    }
    for(int i=0; i<=group_elem_num.size(); i++){
        cout << group_elem_num[i] << ',';
    }
    cout << endl;
}

void bfs(int r, int c, int group_num){
    pair<int,int> temp_pair;
    temp_pair.first = r; temp_pair.second = c;
    group[r][c] = group_num;
    togo.push(temp_pair);
    int elem_cnt = 0;

    while(!togo.empty()){
        temp_pair = togo.front(); togo.pop();
        int curr_r = temp_pair.first; int curr_c = temp_pair.second;
        elem_cnt++;         // 해당 그룹 타일 수 +1
                        
        if(MAP[curr_r-1][curr_c]==0){   // 상
            if(group[curr_r-1][curr_c]==-1){
                group[curr_r-1][curr_c] = group_num;
                temp_pair.first -= 1;
                togo.push(temp_pair);
                temp_pair.first += 1;
            }
        }
        if(MAP[curr_r+1][curr_c]==0){   // 하
            if(group[curr_r+1][curr_c]==-1){
                group[curr_r+1][curr_c] = group_num;
                temp_pair.first += 1;
                togo.push(temp_pair);
                temp_pair.first -= 1;
            }
        }
        if(MAP[curr_r][curr_c-1]==0){   // 좌
            if(group[curr_r][curr_c-1]==-1){
                group[curr_r][curr_c-1] = group_num;
                temp_pair.second -= 1;
                togo.push(temp_pair);
                temp_pair.second += 1;
            }
        }
        if(MAP[curr_r][curr_c+1]==0){   // 우
            if(group[curr_r][curr_c+1]==-1){
                group[curr_r][curr_c+1] = group_num;
                temp_pair.second += 1;
                togo.push(temp_pair);
                temp_pair.second -= 1;
            }
        }
    }
    group_elem_num.push_back(elem_cnt);
}

void grouping(){
    int group_num = 0;
    memset(group,-1,sizeof(group));
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(group[i][j] != -1) continue;
            if(MAP[i][j]==1) continue;
            bfs(i,j, group_num++);
        }
    }    
}

void break_wall() {    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            if(MAP[i][j]==0) continue;      // 벽이 아니면 패스
            int ans_cnt=1;
            set<int> included_groups;
            if(MAP[i-1][j]==0){     //상
                included_groups.insert(group[i-1][j]);
            }
            if(MAP[i+1][j]==0){     //하
                included_groups.insert(group[i+1][j]);
            }
            if(MAP[i][j-1]==0){     //좌
                included_groups.insert(group[i][j-1]);
            }
            if(MAP[i][j+1]==0){     //우
                included_groups.insert(group[i][j+1]);
            }
            set<int>::iterator iter;
            for(iter = included_groups.begin(); iter != included_groups.end(); iter++){
                ans_cnt = (ans_cnt + group_elem_num[*iter]) % 10;                
            }
            if(ans_cnt == 0) MAP[i][j] = -1;
            else MAP[i][j] = ans_cnt;
        }
    }
}

void solve(){
    grouping();
    break_wall();
}

int main(void){
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    fill(&MAP[0][0], &MAP[1010-1][1010],1);

    // 1
    // cin >> N >> M;
    // getc(stdin);
    // for(int i=1; i<=N; i++) {
    //     for(int j=1; j<=M; j++){
    //         MAP[i][j] = (int)getc(stdin) - '0';
    //     }
    //     getc(stdin);
    // }

    // 2
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        string Inp;
        cin >> Inp;
        for (int j = 1; j <= Inp.length(); j++) {
            MAP[i][j] = Inp[j-1] - '0';
        }
    }
    solve();
    print_ans();
}



