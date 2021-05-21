#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>


int main(void)
{
    int t, n, a[100], f[100][100];
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i++)
        {
            f[i][i] = 1;
            for (int j = 0; j < i; j++)
                for (int k = j; k < i; k++)
                    if (a[k] > a[i])
                        f[j][i] = std::max(f[j][i], f[j][k] + 1);
        }
        for (int i = n - 1; i >= 0; i--)
        {
            f[i][i] = 1;
            for (int j = n - 1; j > i; j--)
                for (int k = j; k > i; k--)
                    if (a[k] > a[i])
                        f[j][i] = std::max(f[j][i], f[j][k] + 1);
        }
        int max = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                max = std::max(max, f[j][i]);
        printf("%d\n", max);
    }
}