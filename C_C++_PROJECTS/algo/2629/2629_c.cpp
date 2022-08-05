#include <iostream>
using namespace std;

int m, a[33], n, b;
bool d[33][15001];

void f(int depth,int weight) {
   if (depth > m) return;
   if (d[depth][weight]) return;

   
   d[depth][weight] = true;
   f(depth + 1, weight + a[depth+1]);
   f(depth + 1, abs(weight - a[depth+1]));
   f(depth + 1, weight);
}

int main(void) {
   int i, j;
   cin >> m; //추의 개수 입력
   for (i = 1; i <= m; i++) cin >> a[i]; //추의 무게들 입력
   f(0,0);
   cin >> n; //확인할 추의 개수 입력
   for (i = 1; i <= n; i++) {
      cin >> b; //확인할 추의 무게들 입력
      if (b > 15000) cout << "N "; //30*500 최대 무게이므로 15000이 넘으면 의미가 없음
      else if(d[m][b]) cout << "Y "; //DP table에서 해당 무게가 true이면 Y
      else cout << "N "; //그 외에는 N
   }
}