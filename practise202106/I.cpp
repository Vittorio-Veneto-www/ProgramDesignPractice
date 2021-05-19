#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int cnt;

void work(int t, int x, int m, int n)
{
    if ((n - t) * x > m)
        return;
    if (t == n)
    {
        if (!m)
            cnt++;
        return;
    }
    else
        for (;x <= m; x++)
            work(t + 1, x, m - x, n);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d%d", &m, &n);
        cnt = 0;
        work(0, 0, m, n);
        printf("%d\n", cnt);
    }
}