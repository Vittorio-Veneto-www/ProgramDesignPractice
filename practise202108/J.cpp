#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

long long f[101][101][2];
int mark[101], ans[100], anscnt;

void work(int n, long long ord, int i, int j)
{
    if (!n)
        return;
    long long x = 0;
    j = !j;
    if (j)
        i = 1;
    for (; i <= n; i++)
    {
        if (x + f[n][i][j] >= ord)
            break;
        x += f[n][i][j];
    }
    ord -= x;
    int cnt = 0;
    for (x = 1; cnt < i; x++)
        if (!mark[x])
            cnt++;
    mark[x - 1] = 1;
    ans[anscnt++] = x - 1;
    work(n - 1, ord, i, j);
}

int main(void)
{
    memset(f, 0, sizeof(f));
    f[1][1][0] = 1;
    f[1][1][1] = 1;
    for (int i = 2; i <= 100; i++)
        for (int j = 1; j <= i; j++)
        {
            for (int k = 1; k < j; k++)
                f[i][j][0] += f[i - 1][k][1];
            for (int k = j; k < i; k++)
                f[i][j][1] += f[i - 1][k][0];
        }
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        long long ord;
        scanf("%d%lld", &n, &ord);
        memset(mark, 0, sizeof(mark));
        anscnt = 0;
        int i, j;
        long long x = 0;
        for (i = 1; i <= n; i++)
        {
            for (j = 0; j < 2; j++)
            {
                if (x + f[n][i][j] >= ord)
                    break;
                x += f[n][i][j];
            }
            if (j != 2)
                break;
        }
        ord -= x;
        mark[i] = 1;
        ans[anscnt++] = i;
        work(n - 1, ord, i, j);
        for (int i = 0; i < n; i++)
        {
            if (i)
                printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }
}