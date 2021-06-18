#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    char s[1001];
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", s);
        int n = strlen(s);
        int a[1002], b[1002];
        a[0] = 0;
        for (int i = 1; i <= n; i++)
            a[i] = a[i - 1] + (s[i - 1] == '1');
        b[n] = 0;
        for (int i = n - 1; i >= 0; i--)
            b[i] = b[i + 1] + (s[i] == '0');
        int min = n - 1;
        for (int i = 0; i <= n; i++)
            min = std::min(min, a[i] + b[i]);
        printf("%d\n", min);
    }
}