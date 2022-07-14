#include <iostream>
#include <vector>

using namespace std;
vector<int> vec;

int Data[10000];

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) cin >> Data[i];

    vec.push_back(Data[0]);
    for (int i = 1; i < N; i++) {
        if (vec.back() < Data[i]) {
            vec.push_back(Data[i]);
           // cout << Data[i] << "    push_back" << endl;
        }
        // else if (vec.back() == Data[i]) continue;
        else {
            // vec[lower_bound(vec.begin(),vec.end(),Data[i]) - vec.begin()] = Data[i];

            for (int j =vec.size()-1; j >= 0; j--) {
                if (j==0 && vec[j] > Data[i]){ vec[j] = Data[i]; break;}
                else if (vec[j] < Data[i]) {
                   // cout << vec.at(j+1) << " << " << Data[i] << endl;
                    vec[j+1] = Data[i];
                    break;
                }
            }
        }
    }

    //for (int i = 0; i < vec.size(); i++) cout << vec.at(i); 

    cout << vec.size() << endl;
    return 0;
}