#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int a[65536];

int work(int dep, int x, int y, double total)
{
    if (fabs(1 - total) < 1e-6)
        if (!x)
        {
            printf("%d", dep);
            for (int i = 0; i < dep; i++)
                printf(" %d", a[i]);
            printf("\n");
            return 1;
        }
    if (total > 1)
        return 0;
    for (int i = y; i <= x; i++)
    {
        a[dep] = i;
        if (work(dep + 1, x - i, i, total + (double)1 / i))
            return 1;
    }
    return 0;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        if (!work(0, n, 1, 0))
            printf("-1\n");
    }
}