#include <cstdio>
#include <iostream>
using namespace std;

class f {
	int x, z;
	public:
		f(int x):x(x){}
		f(int x, int z):x(x), z(z){}
		int operator()(int y)
		{
			return y - x;
		}
		operator int()
		{
			return z * x;
		}
};

int main() {
  cout << f(3)(5) << endl;
  cout << f(4)(10) << endl;
  cout << f(114)(514) << endl;
  cout << f(9,7) << endl;
  cout << f(2,3) << endl;
  cout << f(2,5) << endl;
}
