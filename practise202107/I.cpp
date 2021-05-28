#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        int f[5];
        for (int i = 0; i < 5; i++)
            if (i % 2)
                f[i] = -1e9;
            else
                f[i] = 0;
        int x;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &x);
            for (int i = 1; i < 5; i++)
                f[i] = std::max(f[i], f[i - 1] + x * (i % 2 ? -1 : 1));
        }
        printf("%d\n", f[4]);
    }
}