#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, x, a[9], b[9], mark[9];

void work(int t)
{
    if (t == n)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (b[i] - a[i] >= x)
                cnt++;
        if (cnt > n / 2)
        {
            for (int i = 0; i < n; i++)
            {
                if (i)
                    printf(" ");
                printf("%d", b[i]);
            }
            printf("\n");
        }
        return;
    }
    for (int i = 0; i < n; i++)
        if (!mark[i])
        {
            mark[i] = 1;
            b[t] = i + 1;
            work(t + 1);
            mark[i] = 0;
        }
}

int main(void)
{
    scanf("%d%d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    memset(mark, 0, sizeof(mark));
    work(0);
}