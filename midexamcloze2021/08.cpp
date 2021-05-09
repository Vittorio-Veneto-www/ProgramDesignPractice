#include<iostream>
using namespace std;
unsigned int calc(unsigned int n,unsigned m,int x,int y) {
	for (int i = 0; i < x; i++)
		if (n & 1 << i)
			if (!(m & 1 << i))
				m |= 1 << i;
			else;
		else
			if (m & 1 << i)
				m ^= 1 << i;
			else;
	for (int i = 0; i < y; i++)
		if (n & 1 << (31 - i))
			if (!(m & 1 << (31 - i)))
				m |= 1 << (31 - i);
			else;
		else
			if (m & 1 << (31 - i))
				m ^= 1 << (31 - i);
			else;
	return m;
}
int main() {
  int x, y, t;
  unsigned int n, m;
  cin >> t;
  while (t--) { 
    cin >> n >> m >> x >> y;
    cout << calc(n, m, x, y) << endl;
  }
  return 0;
}
