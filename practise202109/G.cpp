#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, a[10000][3], f[10000][4];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i][0]);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i][1]);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i][2]);
    memset(f, 0, sizeof(f));
    f[0][0] = a[0][0];
    f[0][2] = a[0][1];
    for (int i = 1; i < n; i++)
    {
        f[i][0] = std::max(f[i - 1][2], f[i - 1][3]) + a[i][0];
        f[i][1] = std::max(f[i - 1][0], f[i - 1][1]) + a[i][1];
        f[i][2] = std::max(f[i - 1][2], f[i - 1][3]) + a[i][1];
        f[i][3] = std::max(f[i - 1][0], f[i - 1][1]) + a[i][2];
    }
    printf("%d\n", std::max(f[n - 1][0], f[n - 1][1]));
}