#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[1000], f[1001];

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (a[i] == i - j + 1)
                    f[j]++;
                f[j] = std::max(f[j], f[j - 1]);
            }
            if (a[i] == i + 1)
                f[0]++;
        }
        int max = 0;
        for (int i = 0; i < n; i++)
            max = std::max(max, f[i]);
        printf("%d\n", max);
    }
}