#include <iostream>
#include <vector>
using namespace std;
 
#define MAX 1000000
bool isPrime[MAX + 1];
int visited[MAX + 1];
 
 
void SieveOfEratosthenes() {
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true; // 처음에 모두 소수라고 가정
    }
    for (int i = 2; i * i <= MAX; i++) { //2 부터 sqrt(n) 까지
        if (!isPrime[i]) continue; //이미 지워진 수는 무시
        for (int j = i * i; j <= MAX; j += i) { // 자기자신을 제외한 배수를 모두
            isPrime[j] = false; // 지운다
        }
    }
}
 
int power(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y % 2 == 1) {
            res = res * x;
        }
        y /= 2;
        x = x * x;
    }
    return res;
}
 
int main(void) {
    SieveOfEratosthenes();
    int n;
    cin >> n;
    vector<int> plist;
    for (int i = 1; i <= MAX; i++) if (isPrime[i]) plist.push_back(i);
    vector<vector<int> > v(n, vector<int>(plist.size(), 0));
 
    for (int i = 0; i < n; i++) {
        int score;
        cin >> score;
        for (int j = 0; j < plist.size(); j++) {
            if (score == 1) break;
            while (score % plist[j] == 0) {
                score /= plist[j];
                visited[plist[j]]++;    //전체 들어있는 소수의 개수
                v[i][j]++;              // i번째 숫자에 사용되는 각 소수의 개수
            }
        }
    }
    int gcd = 1;
    int cnt = 0;
    for (int i = 0; i < plist.size(); i++) {
        int d = visited[plist[i]] / n; //최소로 분배되야할 각 소수의 개수
        for (int j = 0; j < n; j++) {
            if (v[j][i] < d) { 
                cnt += d - v[j][i]; // 분배
            }
        }
        gcd *= power(plist[i], d);
    }
    cout << gcd << " "<<cnt;
 
    return 0;
}
