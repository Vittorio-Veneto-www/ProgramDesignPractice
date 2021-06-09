#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int m, n, s, a[100][4], f[361][1001], max;
    scanf("%d%d%d", &m, &n, &s);
    char str[20];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d%s", &a[i][0], &a[i][1], &a[i][2], str);
        a[i][3] = str[0] == 'u';
    }
    max = 0;
    for (int i = 1; i <= std::min(m, 15); i++)
    {
        int t = i * 24, m = s - 200 * (i / 3);
        switch (i % 3)
        {
            case 1: m -= 100;break;
            case 2: m -= 150;break;
        }
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i++)
            if (a[i][3])
                for (int j = a[i][2]; j <= t; j++)
                    for (int k = a[i][1]; k <= m; k++)
                        f[j][k] = std::max(f[j][k], f[j - a[i][2]][k - a[i][1]] + a[i][0]);
            else
                for (int j = t; j >= a[i][2]; j--)
                    for (int k = m; k >= a[i][1]; k--)
                        f[j][k] = std::max(f[j][k], f[j - a[i][2]][k - a[i][1]] + a[i][0]);
        max = std::max(max, f[t][m]);
    }
    printf("%d\n", max);
}