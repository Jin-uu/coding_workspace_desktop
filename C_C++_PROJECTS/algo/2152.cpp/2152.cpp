#include <bits/stdc++.h>
#define MAX_N 10'000
#define MAX_M 100'000


using namespace std;

int N, M, S, T;
vector<int> edges[MAX_M];       // 간선 정보
int id, d[MAX_N+1];             // 도시마다 고유 id 값 부여
stack<int> stk;                 // 타잔 scc algo
bool is_finished[MAX_M+1];      // 검사 여부
vector<vector<int>> scc;        // scc[i][j] = i번째 scc에 속해있는 j번째 도시 번호
int scc_id[MAX_N+1];            // scc[i] = i번째 도시가 속해있는 scc 번호
int scc_idx;                    
vector<int> scc_elem_num;       // scc_elem_num[i] = i번째 scc에 속해있는 도시 개수
vector<vector <int>> scc_map;
queue<int> q;
int ans[MAX_N];

int dfs(int curr){              // 타잔 scc 알고리즘
    d[curr] = ++id;             // 고유 id값 지정
    stk.push(curr);             // 스택 삽입

    int parent = d[curr];       // 현재 도시의 id값을 부모 값으로 설정
    for (int i = 0; i < edges[curr].size(); i++) {      // 해당 도시로 부터 출발하는 모든 간선에 대해
        int to = edges[curr][i];                        // to = 해당 간선 목적지
        if(d[to] == 0) parent = min(parent, dfs(to));   // 목적지도시가 아직 dfs를 호출하기 전이라면 돌리고 parent갱신
        else if(!is_finished[to]) parent = min(parent, d[to]);  // 이미 호출했지만 scc에 포함되기 전이라면 parent갱신
    }

    if(parent == d[curr]){                      // parent값이 자기 자신id값이라면
        vector<int> temp_scc;
        int curr_size=0;
        while(1){
            int top = stk.top(); stk.pop();     // 현재 스택 pop
            temp_scc.push_back(top);            // 현재 scc에 pop한 도시 id값 추가
            is_finished[top] = true;            // 추가한 도시 scc포함여부 true로 갱신
            curr_size++;                        // 현재 scc에 포함된 도시 개수 +1
            scc_id[top] = scc_idx;              // 해당 도시가 포함된 scc번호 저장
            if(top == curr) break;              // 만약 pop한 도시가 현재 도시면 그만
        }
        scc_elem_num.push_back(curr_size);      // 현재 scc 포함된 도시 개수 저장
        scc_idx++;                              // scc번호 +1
        scc.push_back(temp_scc);                // 추가
    }
    
    return parent;
}

void set_scc_map(){    
    scc_map.resize(scc_idx);
    for (int i = 1; i <= N; i++) {                              // 모든 도시에 대해
        for (int j = 0; j < edges[i].size(); j++) {             // 해당 도시에서 갈 수 있는 도시에 대해
            int from = i; int to = edges[i][j];
            if(scc_id[from] != scc_id[to]){                     // from과 to가 서로 다른 scc에 속해 있으면
                scc_map[scc_id[from]-1].push_back(scc_id[to]-1);    // scc 그룹 기준 map 생성
            }
        }        
    }
}

void bfs(int start, int target){
    q.push(start);  // 시작 scc번호 삽입
    ans[start] = scc_elem_num[start];       // 
    
    while(!q.empty()){
        int curr = q.front(); q.pop();
        for (int i = 0; i < scc_map[curr].size(); i++) {        // 해당 scc에서 갈 수 있는 다른 scc에 대해
            int next = scc_map[curr][i];                        // 
            if(ans[next] < ans[curr] + scc_elem_num[next]){
                ans[next] = ans[curr] + scc_elem_num[next];
                q.push(next);
            }
        }                
    }
}

int main(void){
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> S >> T;            // 기본 정보 입력
    for (int i = 0; i < M; i++) {       // 간선 입력
        int from, to;
        cin >> from >> to;
        edges[from].push_back(to);
    }

    // 초기화
    memset(d, 0, sizeof(d));
    memset(is_finished, false, sizeof(is_finished));
    scc_idx = 1;
    
    // 모든 도시에 대해 dfs 수행
    for (int i = 1; i <= N; i++) {
        if(d[i] == 0) dfs(i);
    }
    scc_idx--;

    // cout << "scc_idx : " << scc_idx << endl;
    // cout << "scc_map.size()" << scc_map.size() << endl;
    // cout << "scc :" << endl;
    // for (int i = 0; i < scc.size(); i++) {
    //     cout << i <<"(" << scc_elem_num[i] << "," << scc[i].size() << ") :";
    //     for (int j = 0; j < scc[i].size(); j++) {
    //         cout << scc[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "scc_id : ";
    // for (int i = 1; i <= N; i++) {
    //     cout << scc_id[i] << " ";
    // }
    // cout << endl;


    // 구한 scc기반 새로운 map생성
    set_scc_map();

    // cout << "scc_map : " << endl;
    // for (int i = 0; i < scc_map.size(); i++) {
    //     cout << "scc(" << i << ") : ";
    //     for (int j = 0; j < scc_map[i].size(); j++)
    //     {
    //         cout << scc_map[i][j] << " ";
    //     }
    //     cout << endl;        
    // }
    // cout << endl;
    
    int start = scc_id[S]-1;
    int target = scc_id[T]-1;

    // cout << "start : " << start << endl;
    // cout << "target : " << target << endl;

    if(start == target){                        // 시작|끝 도시가 같은 scc에 속하는 경우
        cout << scc_elem_num[start] << endl;    // 해당 scc 포함 도시개수 출력 후 종료
        return 0;
    }

    // 시작|끝 도시가 다른 scc에 속하는 경우
    bfs(start, target);
    cout << ans[target];
    return 0;
}