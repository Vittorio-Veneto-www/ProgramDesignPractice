#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, m, a[100][2], f[100][2];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    f[0][0] = a[0][0];
    f[0][1] = a[0][1];
    for (int i = 1; i < n; i++)
    {
        f[i][0] = std::max(f[i - 1][0], f[i - 1][1] - m) + a[i][0];
        f[i][1] = std::max(f[i - 1][0] - m, f[i - 1][1]) + a[i][1];
    }
    printf("%d\n", std::max(f[n - 1][0], f[n - 1][1]));
}