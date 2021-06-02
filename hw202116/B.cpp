#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int n, k, a[8][8], cnt, sum, mark[8];

void dfs(int t)
{
    if (cnt == k)
    {
        sum++;
        return;
    }
    if (t == n)
        return;
    for (int i = 0; i < n; i++)
        if (a[t][i] && !mark[i])
        {
            mark[i] = 1;
            cnt++;
            dfs(t + 1);
            cnt--;
            mark[i] = 0;
        }
    dfs(t + 1);
}

int main(void)
{
    scanf("%d%d", &n, &k);
    while (n != -1)
    {
        char str[10];
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            for (int j = 0; j < n; j++)
                a[i][j] = str[j] == '#';
        }
        memset(mark, 0, sizeof(mark));
        cnt = 0;
        sum = 0;
        dfs(0);
        printf("%d\n", sum);
        scanf("%d%d", &n, &k);
    }
}