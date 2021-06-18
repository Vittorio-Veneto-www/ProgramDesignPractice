#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int a[1400][2], f[100001];

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        int N = 0;
        for (int i = 0; i < n; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            int t = 1;
            while (t < z)
            {
                z -= t;
                a[N][0] = x * t;
                a[N][1] = y * t;
                t *= 2;
                N++;
            }
            a[N][0] = x * z;
            a[N][1] = y * z;
            N++;
        }
        memset(f, 0, sizeof(f));
        for (int i = 0; i < N; i++)
            for (int j = 100000; j >= a[i][1]; j--)
                f[j] = std::max(f[j], f[j - a[i][1]] + a[i][0]);
        int i;
        for (i = 0; f[i] < p && i <= 100000; i++);
        if (i > 100000)
        {
            for (int i = 0; i < m; i++)
            {
                int x, y, z;
                scanf("%d%d%d", &x, &y, &z);
            }
            printf("FAIL\n");
            continue;
        }
        p = i;
        N = 0;
        for (int i = 0; i < m; i++)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            int t = 1;
            while (t < z)
            {
                z -= t;
                a[N][0] = x * t;
                a[N][1] = y * t;
                t *= 2;
                N++;
            }
            a[N][0] = x * z;
            a[N][1] = y * z;
            N++;
        }
        memset(f, 0, sizeof(f));
        for (int i = 0; i < N; i++)
            for (int j = 50000; j >= a[i][1]; j--)
                f[j] = std::max(f[j], f[j - a[i][1]] + a[i][0]);
        for (i = 0; f[i] < p && i <= 50000; i++);
        if (i <= 50000)
            printf("%d\n", i);
        else
            printf("FAIL\n");
    }
}