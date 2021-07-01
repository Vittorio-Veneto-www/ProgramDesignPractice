#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, x, a[100];
        memset(a, 0, sizeof(a));
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &x), a[x - 1] = 1;
        int max = 0;
        for (int i = 0; i < 100; i++)
        {
            int x = 0, j;
            for (j = i; j < 100 && x <= m; j++)
                if (a[j])
                    x++;
            if (x > m)
                j--;
            max = std::max(max, j - i);
        }
        printf("%d\n", max);
    }
}