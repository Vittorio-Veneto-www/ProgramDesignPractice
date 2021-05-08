#include <iostream>
using namespace std;

class A {
public:
    int val;
    A(int val): val(val) {}
    A(const A &x): val(x.val) {}
    A& operator+=(A x)
    {
        val += x.val;
        return *this;
    }
    A& operator-=(A x)
    {
        val -= x.val;
        return *this;
    }
    int& getValue()
    {
        return val;
    }
    friend ostream& operator<<(ostream &os, const A &x)
    {
        os << x.val;
        return os;
    }
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}