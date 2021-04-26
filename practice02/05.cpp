#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
    char tmp[32];
    for (int i = 30; i >= 0; i--)
        tmp[i] = (x % 2) + '0', x = x >> 1;
    tmp[31] = 0;
    return tmp;
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}