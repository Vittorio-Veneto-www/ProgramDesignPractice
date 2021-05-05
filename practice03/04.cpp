#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;
template <class T>
class Print
{
    int cnt, cur = 0;
    public:
        Print(int cnt):cnt(cnt){}
        Print& operator+(T x)
        {
            cout << x;
            cur++;
            if (cur == cnt)
                cout << endl;
            return *this;
        }
};
int main(){
	string s[20];
	int num[20];
	int m,n;
	
	while(cin >> m >> n){
		for(int i=0; i<m; i++){
			cin >> s[i];
		}
		accumulate(s, s+m, Print<string>(m));
		for(int i=0; i<n; i++){
			cin >> num[i];
		}
		accumulate(num, num+n, Print<int>(n));
	}
}