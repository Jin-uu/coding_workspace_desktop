// #define DEBUG

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define MAX_LEN 17000

typedef struct {
    unsigned char _00 : 2;      
    unsigned char _01 : 2;
    unsigned char _10 : 2;
    unsigned char _11 : 2;
} tracker;

using namespace std;

string str1;
string str2;

int dp[2][MAX_LEN+1];
tracker tracker_log[MAX_LEN/2 +1][MAX_LEN/2 +1];

void set_tracker(int i, int j, int where){      // 0:copy / 1:m / 2:d / 3:a
    if(i%2 == 0){
        if(j%2 == 0){
            tracker_log[i/2][j/2]._00 = where;
        }
        else{
            tracker_log[i/2][j/2]._01 = where;
        }
    }
    else{
        if(j%2 == 0){
            tracker_log[i/2][j/2]._10 = where;
        }
        else{
            tracker_log[i/2][j/2]._11 = where;
        }
    }
}

int get_tracker(int X, int Y){
    int x = X%2;
    int y = Y%2;
    if(x == 0){
        if(y == 0){
            return tracker_log[X/2][Y/2]._00;
        }
        else{
            return tracker_log[X/2][Y/2]._01;
        }
    }
    else{
        if(y == 0){
            return tracker_log[X/2][Y/2]._10;
        }
        else{
            return tracker_log[X/2][Y/2]._11;
        }
    }
}

void print_dp(void){            // debug
    cout << "dp[0][] : ";
    for(int i=0; i<=str2.length() ; i++){
        cout << dp[0][i] << " ";
    }
    cout << endl << "dp[1][] : ";
    for(int i=0; i<=str2.length() ; i++){
        cout << dp[1][i] << " ";
    }
    cout << endl;
}

void print_tracker(void){       // debug
    cout << "tracker[][] :" << endl;
    for(int i=0; i<=str1.length() ; i++){
        for(int j=0; j<=str2.length(); j++){
            cout << get_tracker(i,j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void get_user_input(void){
    cin >> str1;
    cin >> str2;
    #ifdef DEBUG
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;    
    #endif
}

void set_dp(void){
    for(int i=0; i<=str2.length(); i++){        // dp[0][?] init
        dp[0][i] = i;
        set_tracker(0,i,3);
    }

    for(int i=1; i<=str1.length(); i++){
        dp[i%2+1][0] = i-1;
        dp[i%2][0] = i;
        set_tracker(i,0,2);
        if(i%2 == 1){                               // i가 홀수면
            for(int j=1; j<=str2.length(); j++){    // dp[1] 채우기
                if(str1[i-1]==str2[j-1]){           // 새로 추가되는 두 알파벳이 같으면
                    dp[1][j] = dp[0][j-1];          // 'c' 사용
                    set_tracker(i,j,0);
                }
                else{                               // 다르면
                    dp[1][j] = min({dp[0][j-1],dp[0][j],dp[1][j-1]}) + 1;   // 'm', 'd', 'a' 중 최소 사용
                    if(dp[0][j-1] > dp[0][j]){
                        if(dp[0][j] > dp[1][j-1]){
                            set_tracker(i,j,3);         // 'a' 사용
                        }
                        else
                            set_tracker(i,j,2);         // 'd' 사용
                    }
                    else{
                        if(dp[0][j-1] > dp[1][j-1]){
                            set_tracker(i,j,3);         // 'a' 사용
                        }
                        else
                            set_tracker(i,j,1);         // 'm' 사용
                    }
                }
            }
        }
        else{                                       // i가 짝수면
            for(int j=1; j<=str2.length(); j++){    // dp[0] 채우기
                if(str1[i-1]==str2[j-1]){           // 새로 추가되는 두 알파벳이 같으면
                    dp[0][j] = dp[1][j-1];          // 'c' 사용
                    set_tracker(i,j,0);
                }
                else{                               // 다르면
                    dp[0][j] = min({dp[1][j-1],dp[1][j],dp[0][j-1]}) + 1;   // 'm', 'd', 'a' 중 최소 사용
                    if(dp[1][j-1] > dp[1][j]){
                        if(dp[1][j] > dp[0][j-1]){
                            set_tracker(i,j,3);         // 'a' 사용
                        }
                        else
                            set_tracker(i,j,2);         // 'd' 사용
                    }
                    else{
                        if(dp[1][j-1] > dp[0][j-1]){
                            set_tracker(i,j,3);         // 'a' 사용
                        }
                        else
                            set_tracker(i,j,1);         // 'm' 사용
                    }
                }
            }
        }
        #ifdef DEBUG
        print_dp();
        #endif
    }
}

void print_ans(void){
    int curr_x = str1.length(), curr_y = str2.length(), ans_len =0;;
    vector<int> track;
    track.push_back(get_tracker(curr_x,curr_y));
        #ifdef DEBUG
        cout << "track[] : ";
        #endif
    while(curr_x >= 0 && curr_y >= 0){
        #ifdef DEBUG
        cout << track[ans_len] << " ";
        #endif
        if(track[ans_len]==0){
            curr_x -= 1;
            curr_y -=1;
            track.push_back(get_tracker(curr_x, curr_y));
        }        
        else if(track[ans_len]==1){
            curr_x -= 1;
            curr_y -=1;
            track.push_back(get_tracker(curr_x, curr_y));
        }    
        else if(track[ans_len]==2){
            curr_x -= 1;
            track.push_back(get_tracker(curr_x, curr_y));
        }    
        else{
            curr_y -=1;
            track.push_back(get_tracker(curr_x, curr_y));
        }
        ans_len++;
    }
    int curr_loc1=0;
    int curr_loc2=0;
    // cout << endl;
    for(int i = track.size()-3; i>=0; i--){
        if(track[i] == 0){
            cout << "c " << str1[curr_loc1] << endl;
            curr_loc1++;
            curr_loc2++;
        }
        else if(track[i] == 1){
            cout << "m " << str2[curr_loc2] << endl;
            curr_loc1++;
            curr_loc2++;
        }
        else if(track[i] == 2){
            cout << "d " << str1[curr_loc1] << endl;
            curr_loc1++;
        }
        else if(track[i] == 3){
            cout << "a " << str2[curr_loc2] << endl;
            curr_loc2++;
        }
    }
}

int main(void){
    get_user_input();
    set_dp();
    #ifdef DEBUG
    print_tracker();
    #endif
    print_ans();    
}