#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int n, a[16][16], f[1 << 16][16];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    memset(f, 0x7f, sizeof(f));
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; i++)
        for (int j = 0; j < n; j++)
            if (i & 1 << j)
            {
                int x = i ^ 1 << j;
                for (int k = 0; k < n; k++)
                    if (x & 1 << k)
                        f[i][j] = std::min(f[i][j], f[x][k] + a[k][j]);
            }
    printf("%d\n", f[(1 << n) - 1][n - 1]);
}