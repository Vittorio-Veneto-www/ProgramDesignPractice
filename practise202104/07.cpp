#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class CMean {
    int &average, cnt, sum;
    public:
        CMean(int &average):average(average), cnt(0), sum(0){}
        void operator()(int x)
        {
            cnt++;
            sum += x;
            average = sum / cnt;
        }
};

int main(int argc, char* argv[]) {
	int  v;
	int t;
	cin >> t;
	while ( t -- ) {
		cin >> v;
		vector<int> vec;
		while (v) {
			vec.push_back(v);
			cin >> v;
		}
		int myAver = 0;
		for_each(vec.begin(), vec.end(), CMean(myAver));
		cout << myAver << endl;
	}
	return 0;
}