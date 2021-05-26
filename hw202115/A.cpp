#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    long long f[250][250];
    memset(f, 0, sizeof(f));
    for (int i = 1; i < 250; i++)
    {
        f[i][i] = 1;
        if (!(i % 2))
            f[i][i / 2] = 1;
        for (int j = (i - 1) / 2; j; j--)
        {
            int x = i - j * 2;
            for (int k = j; k <= x; k++)
                f[i][j] += f[x][k];
        }
    }
    for (int i = 1; i < 250; i++)
        for (int j = 0; j < i; j++)
            f[i][i] += f[i][j];
    int n;
    scanf("%d", &n);
    while (n)
    {
        printf("%d %lld\n", n, f[n][n]);
        scanf("%d", &n);
    }
}