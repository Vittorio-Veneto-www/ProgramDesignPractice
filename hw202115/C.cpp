#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int n, m, a[3402][2], f[12881];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; i++)
        for (int j = m; j >= a[i][0]; j--)
            f[j] = std::max(f[j - a[i][0]] + a[i][1], f[j]);
    int max = 0;
    for (int j = 0; j <= m; j++)
        max = std::max(max, f[j]);
    printf("%d\n", max);
}