#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int work(int n, int x)
{
    if (n == 1)
        return 1;
    int cnt = 0;
    for (int i = x; i <= n; i++)
        if (!(n % i))
            cnt += work(n / i, i);
    return cnt;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        printf("%d\n", work(n, 2));
    }
}