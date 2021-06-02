#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int cnt, cur, lst[10], pos[70][10];

void work(int n, int l)
{
    int x = cur;
    cur++;
    for (int i = l + 3; i < n; i++)
    {
        lst[x] = i;
        pos[cnt][0] = x + 1;
        for (int i = 0; i <= x; i++)
            pos[cnt][i + 1] = lst[i];
        cnt++;
        work(n, i);
    }
    cur--;
}

int main(void)
{
    int n, m, a[100][10], f[100][70][70];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        char str[20];
        scanf("%s", str);
        for (int j = 0; j < n; j++)
            a[i][j] = str[j] == 'P';
    }
    cnt = 0, cur = 0;
    pos[0][0] = 0;
    cnt++;
    work(m, -3);
    memset(f, 0, sizeof(f));
    for (int i = 0; i < cnt; i++)
    {
        int t;
        for (t = 1; t <= pos[i][0]; t++)
            if (!a[0][pos[i][t]])
                break;
        if (t <= pos[i][0])
            continue;
        f[0][i][0] = std::max(f[0][i][0], pos[i][0]);
    }
    int mark[10];
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt; j++)
        {
            memset(mark, 0, sizeof(mark));
            int t;
            for (t = 1; t <= pos[i][0]; t++)
                if (!a[1][pos[i][t]] || mark[pos[i][t]])
                    break;
                else
                    mark[pos[i][t]] = 1;
            if (t <= pos[i][0])
                continue;
            for (t = 1; t <= pos[j][0]; t++)
                if (!a[0][pos[j][t]] || mark[pos[j][t]])
                    break;
                else
                    mark[pos[j][t]] = 1;
            if (t <= pos[j][0])
                continue;
            f[1][i][j] = std::max(f[1][i][j], pos[i][0] + pos[j][0]);
        }
    for (int i = 2; i < n; i++)
        for (int j = 0; j < cnt; j++)
            for (int x = 0; x < cnt; x++)
                for (int y = 0; y < cnt; y++)
                {
                    memset(mark, 0, sizeof(mark));
                    int t;
                    for (t = 1; t <= pos[j][0]; t++)
                        if (!a[i][pos[j][t]] || mark[pos[j][t]])
                            break;
                        else
                            mark[pos[j][t]] = 1;
                    if (t <= pos[j][0])
                        continue;
                    for (t = 1; t <= pos[x][0]; t++)
                        if (!a[i - 2][pos[x][t]] || mark[pos[x][t]])
                            break;
                        else
                            mark[pos[x][t]] = 1;
                    if (t <= pos[x][0])
                        continue;
                    for (t = 1; t <= pos[y][0]; t++)
                        if (!a[i - 1][pos[y][t]] || mark[pos[y][t]])
                            break;
                        else
                            mark[pos[y][t]] = 1;
                    if (t <= pos[y][0])
                        continue;
                    f[i][j][y] = std::max(f[i][j][y], f[i - 1][y][x] + pos[j][0]);
                }
    int max = 0;
    for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt; j++)
        max = std::max(max, f[n - 1][i][j]);
    printf("%d\n", max);
}