#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int f[4001][4001];

int main(void)
{
    int n, a[4001][2];
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    memset(f, 0x7f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (f[i - 1][j] != 0x7f7f7f7f)
                for (int k = 0; k < 2; k++)
                    if (f[i - 1][j] > a[i][k] * (i - 1))
                        f[i][j + 1] = std::min(f[i][j + 1], f[i - 1][j] + a[i][k]);
                    else
                        f[i][j] = std::min(f[i][j], f[i - 1][j] + a[i][k]);
    int i = 0;
    for (; f[n][i] == 0x7f7f7f7f; i++);
    printf("%d\n", i);
}