#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_OP 1000000

using namespace std;

struct max_cmp {
  bool operator()(pair<int,int> a, pair<int,int> b) {
    return a.first < b.first;
  }
};
struct min_cmp {
  bool operator()(pair<int,int> a, pair<int,int> b) {
    return a.first > b.first;
  }
};

int t, k,input, elem_num;
char cmd;
bool isDel[MAX_OP+1];
priority_queue <pair<int,int>, vector<pair<int,int>>, min_cmp> min_pq;
priority_queue <pair<int,int>, vector<pair<int,int>>, max_cmp> max_pq;


void set_q(){
    while(1){
      if(max_pq.empty()) break;
      if(isDel[max_pq.top().second]){
        max_pq.pop();
        continue;
      }
      break;
    }
    while(1){
      if(min_pq.empty()) break;
      if(isDel[min_pq.top().second]){
        min_pq.pop();
        continue;
      }
      break;
    }
}

void solve(){
    elem_num = 0;
    memset(isDel, false, sizeof(isDel));
    priority_queue <pair<int,int>, vector<pair<int,int>>, min_cmp> min_mt; swap(min_pq, min_mt);
    priority_queue <pair<int,int>, vector<pair<int,int>>, max_cmp> max_mt; swap(max_pq, max_mt);

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> cmd >> input;
        if(cmd == 'I'){
            elem_num++;
            min_pq.push({input, i});
            max_pq.push({input, i});
            continue;
        }
        if(input == -1){         
            set_q();
            if(min_pq.empty()) continue;
            isDel[min_pq.top().second] = true;
            min_pq.pop();
            continue;
        }
        if(input == 1){       
            set_q();
            if(max_pq.empty()) continue;
            isDel[max_pq.top().second] = true;  
            max_pq.pop();
            continue;
        }    
    }

    set_q();    
    if(min_pq.size() <= 0 || max_pq.size() <= 0){
      cout << "EMPTY" << endl;
      return;
    }
    cout << max_pq.top().first << " " << min_pq.top().first << '\n';
}

int main(void){
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}