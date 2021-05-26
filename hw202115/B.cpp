#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int n, m, a[200], f[10001];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = m; j >= a[i]; j--)
            f[j] += f[j - a[i]];
    int cnt = 0, b[200];
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        for (int j = 0; j * a[i] <= m; j++)
            x += pow(-1, j) * f[m - j * a[i]];
        if (!x)
            b[cnt++] = a[i];
    }
    std::sort(b, b + cnt);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
    {
        if (i)
            printf(" ");
        printf("%d", b[i]);
    }
}