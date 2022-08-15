#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, input;
priority_queue<int, vector<int>, less<int>> pq;

int main(void){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> input;
        if(input == 0){
            if(pq.size() == 0){
                cout << '0' << '\n'; continue;
            }
            cout << pq.top() << '\n'; pq.pop();
            continue;
        }
        pq.push(input);        
    }
}
