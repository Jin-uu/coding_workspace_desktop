#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_N 100
#define MAX_EDGE 10000

using namespace std;

int n, e;
bool visited[100+10];
vector<int> edge[MAX_EDGE+10];
queue<int> q;


int main(void){
    cin >> n >> e;

    int temp_s, temp_a;
    for (int i = 0; i < e; i++) {
        cin >> temp_s >> temp_a;
        edge[temp_s].push_back(temp_a);
        edge[temp_a].push_back(temp_s);
    }


    visited[1] = true;
    q.push(1);

    int curr, ans=0;
    while(!q.empty()){
        curr = q.front(); q.pop(); ans++;

        for (int i = 0; i < edge[curr].size(); i++) {
            if(!visited[edge[curr][i]]) {
                q.push(edge[curr][i]);
                visited[edge[curr][i]] = true;
            }
        }
    }
    cout << ans-1 << endl;
}

