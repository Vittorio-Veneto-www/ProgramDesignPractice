#include <iostream>
using namespace std;
class Number {
public: 
    int num;
    Number(int n): num(n) {}
    Number(const Number &x): num(x.num) {}
    Number operator*(int x)
    {
        Number tmp(num * x);
        return tmp;
    }
    friend int operator==(int x, Number &y)
    {
        return x == y.num;
    }
    friend ostream& operator<<(ostream &os, const Number &x)
    {
        os << x.num;
        return os;
    }
};
int main() {
	int t;
	int m,n;
	cin >> t;
	while(t--) {
	    cin >> m>> n;
	    Number n1(m), n2 = n1 * n;
	    if( m * n == n2 )
	    	cout << n2 << endl;
	}
    return 0;
}