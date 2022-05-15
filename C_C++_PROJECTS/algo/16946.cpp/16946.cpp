#include <bits/stdc++.h>

using namespace std;

//그룹화??

int N, M;
bool MAP[1010][1010];
int ans[1010][1010];
bool isChecked[1010][1010];
int group[1010][1010];
vector<int> group_elem_num;
queue<pair<int,int>> togo;

void print_MAP(void){
    for(int i=0; i<=N+1; i++){
        for(int j=0; j<=M+1; j++) {
            cout << MAP[i][j] << "  ";
        }
        cout << "\n";
    }
}

void print_ans(void){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            cout << ans[i][j] % 10;
    
        }
        cout << "\n";
    }
}

void print_group(){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            cout << group[i][j] << "    ";
        }
        cout << "\n";
    }
    for (int i = 0; i < group_elem_num.size(); i++)
    {
        cout << group_elem_num[i] << " ";
    }
    cout << endl;
    
}

void bfs(int r, int c, int group_num){
    pair<int,int> temp_pair;
    temp_pair.first = r;
    temp_pair.second = c;
    isChecked[r][c]=true;
    togo.push(temp_pair);
    int elem_cnt = 0;

    while(!togo.empty()){
        temp_pair = togo.front();
        togo.pop();
        int curr_r = temp_pair.first;
        int curr_c = temp_pair.second;
        
        elem_cnt++;      // 해당 그룹 타일 수 +1
        group[curr_r][curr_c] = group_num;

                        
        if(MAP[curr_r-1][curr_c]==0){   // 상
            if(!isChecked[curr_r-1][curr_c]){
                isChecked[curr_r-1][curr_c]=true;
                temp_pair.first -= 1;
                togo.push(temp_pair);
                temp_pair.first += 1;
            }
        }
        if(MAP[curr_r+1][curr_c]==0){   // 하
            if(!isChecked[curr_r+1][curr_c]){
                isChecked[curr_r+1][curr_c]=true;
                temp_pair.first += 1;
                togo.push(temp_pair);
                temp_pair.first -= 1;
            }
        }
        if(MAP[curr_r][curr_c-1]==0){   // 좌
            if(!isChecked[curr_r][curr_c-1]){
                isChecked[curr_r][curr_c-1]=true;
                temp_pair.second -= 1;
                togo.push(temp_pair);
                temp_pair.second += 1;
            }
        }
        if(MAP[curr_r][curr_c+1]==0){   // 우
            if(!isChecked[curr_r][curr_c+1]){
                isChecked[curr_r][curr_c+1]=true;
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
            if(MAP[i][j]) continue;
            bfs(i,j, group_num++);
        }
    }    
}

void break_wall() {    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) {
            if(MAP[i][j]!=1) continue;
            int ans_cnt=1;
            set<int> included_groups;
            if(MAP[i-1][j]!=1){
                included_groups.insert(group[i-1][j]);
            }
            if(MAP[i+1][j]!=1){
                included_groups.insert(group[i+1][j]);
            }
            if(MAP[i][j-1]!=1){
                included_groups.insert(group[i][j-1]);
            }
            if(MAP[i][j+1]!=1){
                included_groups.insert(group[i][j+1]);
            }
            set<int>::iterator iter;
            for(iter = included_groups.begin(); iter != included_groups.end(); iter++){
                ans_cnt = (ans_cnt + group_elem_num[*iter]) % 10;                
            }
            ans[i][j] = ans_cnt;
        }
    }
}

void solve(){
    grouping();
    // print_group();
    break_wall();
}

int main(void){
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    fill(&MAP[0][0], &MAP[1010-1][1010],1);
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++){
            MAP[i][j] = (int)getc(stdin) - '0';
        }
        getc(stdin);
    }

    solve();
    print_ans();
}