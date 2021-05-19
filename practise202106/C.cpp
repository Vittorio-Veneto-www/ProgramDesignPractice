#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main()
{
    int a, n, m, x;
    scanf("%d%d%d%d", &a, &n, &m, &x);
    int f[20][2];
    f[1][0] = 1;
    f[1][1] = 0;
    f[2][0] = 0;
    f[2][1] = 1;
    for (int i = 3; i <= n; i++)
        f[i][0] = f[i - 2][0] + f[i - 1][0], f[i][1] = f[i - 2][1] + f[i - 1][1];
    int f1[20][2];
    f1[1][0] = 1;
    f1[1][1] = 0;
    f1[2][0] = 1;
    f1[2][1] = 0;
    for (int i = 3; i < n; i++)
        f1[i][0] = f1[i - 1][0] + f[i - 2][0], f1[i][1] = f1[i - 1][1] + f[i - 2][1];
    int b = m - f1[n - 1][0] * a;
    b /= f1[n - 1][1];
    printf("%d\n", a * f1[x][0] + b * f1[x][1]);
}