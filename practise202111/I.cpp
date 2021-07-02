#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[300][300];
char mark[300][300][300][2];

int work(int x, int l, int r)
{
    if (mark[x][l][r][0])
        return mark[x][l][r][1];
    mark[x][l][r][0] = 1;
    if (l != x)
    {
        int i;
        for (i = l; i < x; i++)
            if (a[x][i] && work(i, l, x - 1))
                break;
        if (i == x)
        {
            mark[x][l][r][1] = 0;
            return 0;
        }
    }
    if (x != r)
    {
        int i;
        for (i = x + 1; i <= r; i++)
            if (a[x][i] && work(i, x + 1, r))
                break;
        if (i > r)
        {
            mark[x][l][r][1] = 0;
            return 0;
        }
    }
    mark[x][l][r][1] = 1;
    return 1;
}

int main(void)
{
    char s[301];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s);
        for (int j = 0; j < n; j++)
            a[i][j] = s[j] == 'W';
    }
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i < n; i++)
        mark[i][i][i][0] = 1, mark[i][i][i][1] = 1;
    int mark1 = 0;
    for (int i = 0; i < n; i++)
        if (work(i, 0, n - 1))
        {
            if (mark1)
                printf(" ");
            mark1 = 1;
            printf("%d", i + 1);
        }
}