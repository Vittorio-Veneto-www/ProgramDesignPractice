#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int T, cnt = 0;
    scanf("%d", &T);
    while (T--)
    {
        cnt++;
        int n, a[200], f[200][200];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        memset(f, 0x3f, sizeof(f));
        for (int i = 0; i < n; i++)
            f[i][i] = 1;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < n - i; j++)
            {
                if (a[j] == a[j + i])
                    if (i == 1)
                        f[j][j + i] = 1;
                    else
                        f[j][j + i] = f[j + 1][j + i - 1] + 1;
                for (int k = 0; k < i; k++)
                    if (a[j + k] == a[j + i] && i > 1)
                        f[j][j + i] = std::min(f[j][j + i], f[j][j + k] + f[j + k + 1][j + i - 1]);
                    else
                        f[j][j + i] = std::min(f[j][j + i], f[j][j + k] + f[j + k + 1][j + i]);
            }
        printf("Case #%d: %d\n", cnt, f[0][n - 1]);
    }
}