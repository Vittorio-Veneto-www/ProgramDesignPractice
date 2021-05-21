#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

class CHugeInt {
    int len, a[210];
    public:
        CHugeInt(char *s)
        {
            while (*s == '0' && *(s + 1)) s++;
            len = strlen(s);
            for (int i = strlen(s) - 1; i >= 0; i--)
                a[len - i - 1] = s[i] - '0';
        }
        CHugeInt(const CHugeInt & x)
        {
            len = x.len;
            memcpy(a, x.a, sizeof(a));
        }
        CHugeInt(){}
        CHugeInt& operator=(CHugeInt x)
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
        int operator<(const CHugeInt &x) const
        {
            if (len < x.len)
                return 1;
            if (len > x.len)
                return 0;
            for (int i = len; i ; i--)
                if (a[i - 1] < x.a[i - 1])
                    return 1;
                else if (a[i - 1] > x.a[i - 1])
                    return 0;
            return 0;
        }
        friend std::ostream & operator<< (std::ostream & os, const CHugeInt &x)
        {
            for (int i = x.len - 1; i >= 0; i--)
                os << x.a[i];
            return os;
        }
};

int n, m;
CHugeInt a[50][50], f[50][50];

int main(void)
{
    int m;
    while (scanf("%d", &m) != EOF)
    {
        char str[100], temp[100];
        scanf("%s", str);
        int n = strlen(str);
        for (int i = 0; i < n; i++)
        {
            strncpy(temp, str + i, 1);
            temp[1] = 0;
            a[i][i] = temp;
            for (int j = 0; j < i; j++)
            {
                strncpy(temp, str + j, i - j + 1);
                temp[i - j + 1] = 0;
                a[j][i] = temp;
            }
        }
        for (int i = 0; i < n; i++)
        {
            f[i][0] = a[0][i];
            for (int j = 1; j <= m && j <= i; j++)
            {
                f[i][j] = f[i - 1][j - 1] + a[i][i];
                for (int k = j - 1; k < i; k++)
                    f[i][j] = std::min(f[i][j], f[k][j - 1] + a[k + 1][i]);
            }
        }
        std::cout << f[n - 1][m] << std::endl;
    }
}