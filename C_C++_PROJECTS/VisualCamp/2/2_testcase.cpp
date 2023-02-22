#include <iostream>
#include <cstdlib>
#include <ctime>
#define MAX 100

using namespace std;

int main(void) {
	cout << MAX << endl;
	srand((unsigned int)time(NULL));
	int temp;
	for(int i=0; i<MAX; i++) {
		temp = rand()%101;
		cout << temp << " ";
		while(1) {
			temp = rand()%35;
			if(temp != 0) break;
		}
		cout << temp << " ";
		while(1) {
			temp = rand()%101;
			if(temp != 0) break;
		}
		cout << temp << " ";
		cout << endl;
	}
}


