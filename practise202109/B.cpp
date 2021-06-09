#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, k, a[20][20], b[101], c[101][400][2], mark[20][20], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, max;

void work(int x, int y, int step)
{
    max = std::max(max, step);
    for (int i = 0; i < b[a[x][y]]; i++)
        mark[c[a[x][y]][i][0]][c[a[x][y]][i][1]] = 1;
    for (int i = 0; i < 4; i++)
    {
        int x1 = x + delta[i][0], y1 = y + delta[i][1];
        if (mark[x1][y1] || x1 < 0 || x1 >= n || y1 < 0 || y1 >= m)
            continue;
        work(x1, y1, step + 1);
    }
    for (int i = 0; i < b[a[x][y]]; i++)
        mark[c[a[x][y]][i][0]][c[a[x][y]][i][1]] = 0;
}

int main(void)
{
    scanf("%d%d%d", &n, &m, &k);
    memset(b, 0, sizeof(b));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
            c[a[i][j]][b[a[i][j]]][0] = i;
            c[a[i][j]][b[a[i][j]]][1] = j;
            b[a[i][j]]++;
        }
    memset(mark, 0, sizeof(mark));
    max = 0;
    work(0, 0, 1);
    printf("%d\n", max);
}