#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, k, a[1001], f[1001];
    scanf("%d%d", &n, &k);
    while (n)
    {
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        memset(f, 0x7f, sizeof(f));
        f[0] = 0;
        for (int i = 0; i < n; i++)
            for (int j = a[i]; j <= k; j++)
                f[j] = std::min(f[j], f[j - a[i]] + 1);
        if (f[k] != 0x7f7f7f7f)
            printf("%d\n", f[k]);
        else
            printf("-1\n");
        scanf("%d%d", &n, &k);
    }
}