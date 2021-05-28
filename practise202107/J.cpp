#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, m, a[20], f[1001];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = m; j >= a[i]; j--)
            f[j] += f[j - a[i]];
    printf("%d\n", f[m]);
}