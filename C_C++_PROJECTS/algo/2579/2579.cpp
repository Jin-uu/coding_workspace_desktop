#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

#define MAX_S 300

using namespace std;

int n;
int S[MAX_S+1];
int D[MAX_S+1];

int main(void){
    cin >> n;
    for (int i = 0; i < n; i++) cin >> S[i];

    D[0] = S[0];
    D[1] = S[0] + S[1];
    D[2] = max(S[0]+S[2], S[1]+S[2]);

    for(int i=3; i<n; i++){
        D[i] = max(D[i-3] + S[i-1], D[i-2]) + S[i];
    }
    cout << D[n-1];
}