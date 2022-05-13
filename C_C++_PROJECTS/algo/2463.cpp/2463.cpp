#include <bits/stdc++.h>
using namespace std;



int N,M;
long long total_weight;
long long static MOD = 1'000'000'000;
vector<pair<int,pair<int,int>>> edges;      // W[i].first = weight, W[i].second.first|second = x|y
int root[100'001];
long long group_elem_num[100'001];

bool cmp(pair<int,pair<int,int>> &left, pair<int,pair<int,int>> &right){
    return left.first >= right.first;       // edges 의 weight 기준 내림차순 정렬
}

int get_root(int a){
    // if(root[a] != a) return root[a] = get_root(root[a]);
    // else return a;
    if (a == root[a])
        return a;
    return root[a] = get_root(root[a]);
}

void merge(int left, int right){     // right를 left에 병합
    root[right] = left;
    group_elem_num[left] += group_elem_num[right];
    group_elem_num[right] = 1;
}


int main(void){
    ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    total_weight = 0;

    cin >> N >> M;
    for (int i = 0; i < M; i++){
        long long temp_weight, temp_x, temp_y;
        cin >> temp_x >> temp_y >> temp_weight;
        edges.push_back({temp_weight, {temp_x, temp_y}});
        total_weight += temp_weight;
    }

    sort(edges.begin(), edges.end(), cmp);      // edges 의 weight 기준 내림차순 정렬
    
    for(int i=0; i<=N; i++){
        root[i] = i;
        group_elem_num[i] = 1;
    }

    long long ans=0;
    for(int i=0; i<edges.size(); i++){
        int x = edges[i].second.first;  int x_root = get_root(x);
        int y = edges[i].second.second; int y_root = get_root(y);
        long long weight = edges[i].first;
        if(x_root != y_root){       // 두 노드가 다른 집합이면
            // x,y에 속한 노드 개수 곱하고 지금까지 그어지지 않은 간선 가중치 합 곱함
            ans = (ans + (((group_elem_num[x_root] * group_elem_num[y_root]) % MOD) * total_weight) % MOD) % MOD;
            merge(x_root, y_root);      // 두 그룹 머지
        }
        total_weight -= weight;         // 선 그었으니까 해당 간선 가중치 제거
    }

    cout << ans << endl;
    return 0;
}