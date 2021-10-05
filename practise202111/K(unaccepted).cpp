#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int m, min, a[1000], b[1000], c[1000], f[1001][1001][11];

int main(void)
{
    int n, K, h;
    scanf("%d%d%d%d", &n, &K, &m, &h);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    memset(f, 0x3f, sizeof(f));
    f[0][m][0] = h;
    if (h <= b[0])
    {
        printf("1\n");
        return 0;
    }
    for (int i = 1; i < n; i++)
    {
        //int cur = i % 2, last = !cur;
        //memset(f[cur], 0x3f, sizeof(f) / 2);
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k < K; k++)
                f[i][j][k + 1] = f[i - 1][j][k];
            for (int k = 0; k <= K; k++)
            {
                if (j + a[i - 1] == m)
                {
                    if (f[i - 1][j + a[i - 1]][k] != 0x3f3f3f3f)
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][j + a[i - 1]][k] - b[i - 1]);
                    for (int t = 0; t < m && t <= c[i - 1]; t++)
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][m - t][k]);
                }
                if (j + a[i - 1] < m)
                {
                    if (f[i - 1][j + a[i - 1]][k] != 0x3f3f3f3f)
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][j + a[i - 1]][k] - b[i - 1]);
                    if (j + a[i - 1] - c[i - 1] > 0)
                        f[i][j][k] = std::min(f[i][j][k], f[i - 1][j + a[i - 1] - c[i - 1]][k]);
                }
                if (f[i][j][k] <= b[i])
                {
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
        for (int k = 0; k <= K; k++)
            printf("%d ", f[i][j][k]);
        printf("\n");
        }
        printf("\n");
    }
                    printf("%d\n", i + 1);
                    return 0;
                }
            }
        }
    }
    printf("FAIL\n");
}