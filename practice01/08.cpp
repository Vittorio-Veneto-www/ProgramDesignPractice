#include <set>
#include <iostream>
#include <string>
using namespace std;
struct myComp
{
    bool operator()(const std::pair<int, int> &x, const std::pair<int, int> &y) const
    {
        if (y.first == -1)
            return x.second > y.second;
        return x.first < y.first;
    }
};
int main() {
	string cmd;
	set<pair<int, int>, myComp> S;
	while (cin >> cmd) {
		if (cmd == "A") {
			int x, y;
			cin >> x >> y;
			S.insert(make_pair(x, y));
		} else if (cmd == "Qx") {
			int x;
			cin >> x;
			cout << S.lower_bound(make_pair(x, -1))->second << endl;
		} else if (cmd == "Qy") {
			int y;
			cin >> y;
			cout << S.lower_bound(make_pair(-1, y))->first << endl;
		} else {
			int x, y;
			cin >> x >> y;
			S.erase(make_pair(x, y));
		}
	}
	return 0;
}