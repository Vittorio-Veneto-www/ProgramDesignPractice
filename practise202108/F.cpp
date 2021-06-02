#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int n, a[1000], f[2][1000];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
    {
        f[0][i] = 1;
        for (int j = 0; j < i; j++)
            if (a[i] > a[j])
                f[0][i] = std::max(f[0][i], f[0][j] + 1);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        f[1][i] = 1;
        for (int j = n - 1; j > i; j--)
            if (a[i] > a[j])
                f[1][i] = std::max(f[1][i], f[1][j] + 1);
    }
    int max = 0;
    for (int i = 0; i < n; i++)
        max = std::max(max, f[0][i] + f[1][i] - 1);
    printf("%d\n", max);
}