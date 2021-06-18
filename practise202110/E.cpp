#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int T = 0, n;
    while (scanf("%d", &n) != EOF)
    {
        int a[201][20];
        char ch[200];
        double p[200], f[201][20];
        printf("Case %d:\n", ++T);
        for (int i = 0; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            for (int j = 0; j < 20; j++)
                a[i][j] = (x & 1 << j) != 0;
        }
        scanf("%*c");
        for (int i = 0; i < n; i++)
            scanf("%*c%c", &ch[i]);
        for (int i = 0; i < n; i++)
            scanf("%lf", &p[i]);
        for (int i = 0; i < 20; i++)
            f[0][i] = a[0][i];
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 20; j++)
            {
                switch (ch[i - 1])
                {
                    case '&':f[i][j] = (1 & a[i][j]) * f[i - 1][j] + (0 & a[i][j]) * (1 - f[i - 1][j]);break;
                    case '|':f[i][j] = (1 | a[i][j]) * f[i - 1][j] + (0 | a[i][j]) * (1 - f[i - 1][j]);break;
                    case '^':f[i][j] = (1 ^ a[i][j]) * f[i - 1][j] + (0 ^ a[i][j]) * (1 - f[i - 1][j]);break;
                }
                f[i][j] = f[i - 1][j] * p[i - 1] + f[i][j] * (1 - p[i - 1]);
            }
        double ans = 0;
        for (int i = 0; i < 20; i++)
            ans += (1 << i) * f[n][i];
        printf("%.6lf\n", ans);
    }
}