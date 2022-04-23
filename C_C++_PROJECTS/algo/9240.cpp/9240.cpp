#include <bits/stdc++.h>

using namespace std;

int C;
vector<pair<float,float>> arrows;
vector<pair<float,float>> shell;

double dist(pair<float,float> a, pair<float,float> b){
    double dist;
    double x_dist = a.first - b.first;
    double y_dist = a.second - b.second;
    dist = sqrt(pow(x_dist,2)+pow(y_dist,2));
    return dist;
}

double ccw(pair<float,float> a, pair<float,float> b, pair<float,float> c) {
	return (b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first);
}

bool compare_arrows(pair<float,float> a, pair<float,float> b){
    double c = ccw(arrows[0], a,b);        // arrow[0]을 기준으로 ccw 수행
    if(c > 0) return 1;                 // 반시계 방향일 경우
    if(c < 0){                          // 시계 방향일 경우
        return 0;
    }                                   
    else if(dist(arrows[0], a) < dist(arrows[0],b)){    // 일직선상일 경우
        return 1;
    }
    return 0;
}


int main(void){
    cin >> C;

    for (int i = 0; i < C; i++) {
        float temp_x, temp_y;
        cin >> temp_x >> temp_y;
        pair<float, float> temp;
        temp.first = temp_x;
        temp.second = temp_y;
        arrows.push_back(temp);
    }

    // cout << "==========================\n";
	// for (int i=0;i<C;i++) cout<<arrows[i].first<< ","<<arrows[i].second << endl;
    sort(arrows.begin(), arrows.end());                     // x, y좌표 오름차순 정렬
    // cout << "==========================\n";
	// for (int i=0;i<C;i++) cout<<arrows[i].first<< ","<<arrows[i].second << endl;
    sort(arrows.begin()+1, arrows.end(), compare_arrows);   // arrow[0]기준으로 잡고 0제외 반시계 순으로 정렬
    // cout << "==========================\n";
	// for (int i=0;i<C;i++) cout<<arrows[i].first<< ","<<arrows[i].second << endl;
    
    shell.push_back(arrows[0]);      // 초기값 삽입
    shell.push_back(arrows[1]);      // 초기값 삽입

    for (int i = 2; i < C; i++) {       // 2번 화살부터 끝번 화살에 대해
        while(ccw(shell[shell.size()-2],shell.back(),arrows[i]) <= 0 && shell.size() >=2){
            shell.pop_back();
        }
        shell.push_back(arrows[i]);
    }

    // cout << "==========================\n";
    // for(int i=0; i<shell.size(); i++){
    //     cout << shell[i].first << ", " << shell[i].second << endl;
    // }

    double max_dist= -987654321;
    for (int i = 0; i < shell.size(); i++) {
        for(int j=i+1; j<shell.size(); j++){
            max_dist = max(max_dist, dist(shell[i],shell[j]));
            // cout << "dist(" << shell[i].first << "," << shell[i].second << ") ~ (" << shell[j].first << "," << shell[j].second << ") : ";
            // cout << dist(shell[i],shell[j]) << endl;
        }
    }
    printf("%.10f", max_dist);
}









