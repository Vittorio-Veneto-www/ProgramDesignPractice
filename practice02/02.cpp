#include <iostream>
using namespace std;
template <class T>
class Add{
public:
    T n;
    Add(T n):n(n){}
    T operator()(T a, T b)
    {
        return a + b - n;
    }
};

int main(){
	double f;
	int n;
	while( cin >> f >> n) {
		
		Add<double> a1(f);
		Add<int> a2(n);
		double x,y;
		int p,q;
		cin >> x >> y >> p >> q;
		cout << a1(x, y) << endl;
		cout << a2(p, q) << endl;
	}
	return 0;
}