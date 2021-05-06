#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
class Fib
{
    int num, a[3] = {0, 1, 1};
    public:
        Fib(int num):num(num){}
        void operator++()
        {
            a[0] = a[1];
            a[1] = a[2];
            a[2] = a[0] + a[1];
            num++;
        }
        int operator*()
        {
            return a[1];
        }
        int operator!=(const Fib &x) const
        {
            return num != x.num;
        }
};
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;
		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}