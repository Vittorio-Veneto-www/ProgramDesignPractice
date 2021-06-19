#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

long long a[100000], f[100000];

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lld", &a[i]);
        memset(f, 0, sizeof(f));
        f[0] = std::max(f[0], a[0]);
        if (n > 1)
            f[1] = std::max(std::max(f[0], a[1]), f[1]);
        for (int i = 2; i < n; i++)
            f[i] = std::max(std::max(f[i - 1], f[i - 2] + a[i]), f[i]);
        printf("%lld\n", f[n - 1]);
    }
}