#include <iostream>
#include <vector>

#define MAX_N 1024
#define MAX_M 100'000

using namespace std;

int n, m;
int MAP[MAX_N+2][MAX_N+2];
vector<pair<pair<int,int>, pair<int,int>>> input;

int solve(int curr){
    int x1 = input[curr].first.first;
    int y1 = input[curr].first.second;
    int x2 = input[curr].second.first;
    int y2 = input[curr].second.second;
    
    return MAP[x2][y2] - (MAP[x2][y1-1] + MAP[x1-1][y2] - MAP[x1-1][y1-1]);

}

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++){
            cin >> MAP[i][j];
            MAP[i][j] += MAP[i-1][j] + MAP[i][j-1] - MAP[i-1][j-1];
        }
    }

    int temp_x1, temp_y1, temp_x2, temp_y2;
    for (int i = 0; i < m; i++) {
        cin >> temp_x1 >> temp_y1 >> temp_x2 >> temp_y2;
        input.push_back({{temp_x1,temp_y1},{temp_x2, temp_y2}});
    }

    for (int i = 0; i < m; i++) {
        cout << solve(i) << '\n';
    }
}

