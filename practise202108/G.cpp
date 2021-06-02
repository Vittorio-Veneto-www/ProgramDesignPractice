#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int f[11][101];
    memset(f, 0x7f, sizeof(f));
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 100; j++)
            f[i][j] = j;
    for (int i = 2; i <= 10; i++)
        for (int j = 2; j <= 100; j++)
            for (int k = 1; k < j; k++)
                f[i][j] = std::min(f[i][j], std::max(f[i - 1][k - 1], f[i][j - k]) + 1);
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
        printf("%d\n", f[m][n]);
}