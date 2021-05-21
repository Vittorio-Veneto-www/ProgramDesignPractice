#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
    int len, a[210];
    public:
        CHugeInt(char *s)
        {
            len = strlen(s);
            for (int i = strlen(s) - 1; i >= 0; i--)
                a[len - i - 1] = s[i] - '0';
        }
        CHugeInt(int n)
        {
            char s[20];
            sprintf(s, "%d", n);
            len = strlen(s);
            for (int i = strlen(s) - 1; i >= 0; i--)
                a[len - i - 1] = s[i] - '0';
        }
        CHugeInt() {}
        CHugeInt(const CHugeInt & x)
        {
            len = x.len;
            memcpy(a, x.a, sizeof(a));
        }
        CHugeInt & operator=(CHugeInt x)
        {
            len = x.len;
            memcpy(a, x.a, sizeof(a));
            return *this;
        }
        friend CHugeInt operator+(CHugeInt x, CHugeInt y)
        {
            CHugeInt tmp(x);
            return tmp += y;
        }
        CHugeInt operator+=(CHugeInt x)
        {
            int i, x1, r = 0, len1 = std::min(len, x.len);
            for (i = 0; i < len1; i++)
                x1 = a[i], a[i] = (x1 + x.a[i] + r) % 10, r = (x1 + x.a[i] + r) / 10;
            for (; i < len; i++)
                x1 = a[i], a[i] = (x1 + r) % 10, r = (x1 + r) / 10;
            for (; i < x.len; i++)
                a[i] = (x.a[i] + r) % 10, r = (x.a[i] + r) / 10;
            len = std::max(len, x.len);
            if (r)
                a[len++] = r;
            return *this;
        }
        friend CHugeInt operator++(CHugeInt & x)
        {
            x += 1;
            return x;
        }
        CHugeInt operator++(int k)
        {
            CHugeInt tmp(*this);
            *this += 1;
            return tmp;
        }
        friend CHugeInt operator+(int x1, CHugeInt x)
        {
            return x + x1;
        }
        friend ostream & operator<< (ostream & os, const CHugeInt &x)
        {
            for (int i = x.len - 1; i >= 0; i--)
                os << x.a[i];
            return os;
        }
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}