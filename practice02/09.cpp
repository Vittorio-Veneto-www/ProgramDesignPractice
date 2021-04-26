#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
    priority_queue<int, vector<int>, less<int> > q;
    int k;
    public:
        MyQueue(int k):k(k){}
        friend istream& operator>>(istream &is, MyQueue &x)
        {
            int tmp;
            is >> tmp;
            if (!(tmp % 2))
                x.q.push(tmp);
            return is;
        }
        friend ostream& operator<<(ostream &os, MyQueue &x)
        {
            while (x.k--)
            {
                os << x.q.top() << " ";
                x.q.pop();
            }
            return os;
        }
};
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		MyQueue q(k);
		for (int i = 0; i < n; ++i)
			cin >> q;
		cout<<q;
		cout << endl;
	}
	return 0; 
}