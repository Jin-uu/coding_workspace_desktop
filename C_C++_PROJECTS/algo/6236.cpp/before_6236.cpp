// #define DEBUG

#define MAX 100000
#include <iostream>
#include <cstdio>


using namespace std;

int n=-1, m=-1;
int MONEY[MAX+1];     // MONEY[n] : 그날 쓸 돈

bool isPos(int k){
    int cnt = 0;
    int curr_money = 0;
    for(int i=1; i<n+1; i++){
        if(MONEY[i] > k) return false;  // 그날 쓸 돈이 인출할 수 있는 금액보다 큰 경우 false
        if(curr_money < MONEY[i]){      // 현재 돈이 써야하는 금액보다 적으면
            curr_money = k;             // 돈 넣고 k만큼 인출
            cnt++;                      // 인출 회수 + 1
        }
        if(cnt > m) return false;       // 최대 인출 회수 초과시 false
        curr_money -= MONEY[i];         // 현재 돈에서 그날 쓸 돈 지출
    }
    return true;
}

bool check(int mid) {	
	int temp = mid; 
	int cnt = 1; 
	for (int i = 1; i < n+1; i++) {
		if (MONEY[i] <= mid) {
			mid -= MONEY[i]; 
		}
		else {
			mid = temp; 
			cnt++; 
			if (MONEY[i] > mid)return false; 
			else
			mid -= MONEY[i]; 
		}
	}
	return cnt <= m; 
}

int main(void){
    // #ifdef DEBUG
    // FILE *in;
    // in = fopen("6236_test_00.txt","r");
    // if(in == NULL){
    //     cout << ">> file error" << endl;
    //     return 0;
    // }
    // fscanf(in, "%d %d", &n,&m);
    // for(int i=1; i<n+1; i++){
    //     fscanf(in,"%d",&MONEY[i]);
    // }
    // cout << "n, m : " << n << ", " << m << endl;
    // #endif
    // #ifndef DEBUG
    cin >> n;
    cin >> m;

    for(int i=1; i<n+1; i++){
        // cin >> MONEY[i];
        scanf("%d", &MONEY[i]);
    }
    
    isPos(100);
    isPos(101);
    isPos(102);
    isPos(103);
    isPos(104);
    // #endif

    // #ifdef DEBUG
    // cout << "MONEY : " << endl;
    // for(int i=1; i<n+1; i++){
    //     cout << MONEY[i] << endl;
    // }
    // #endif

    int total=0;
    for(int i=1; i<n+1; i++){
        total += MONEY[i];
    }

    int least = 1;

    // #ifdef DEBUG
    // cout << "total : " << total << endl;
    // cout << "least : " << least << endl;
    // #endif

    int left = least;
    int right = total;
    int mid= (left+right)/2;
    int ans =-1;
   
    while(left <= right){
        mid = (left+right)/2;
        #ifdef DEBUG
        cout << ">> " << left << ",  " << mid << ",  " << right << " : ";
        #endif
        if(isPos(mid)){         // 중간이 가능하면
            right = mid-1;      // 중간의 왼쪽 탐색
            ans = mid;
        }
        else{                   // 중간이 불가능하면
            left = mid+1;       // 중간의 오른쪽 탐색
        }
        #ifdef DEBUG
        cout << ans << endl;
        #endif
    }

    cout << ans;


}