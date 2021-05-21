#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, a[100][100], f[100][100], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int work(int x, int y)
{
    if (f[x][y])
        return f[x][y];
    int max = 1;
    for (int i = 0; i < 4; i++)
    {
        int x1 = x + delta[i][0], y1 = y + delta[i][1];
        if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m)
            continue;
        if (a[x][y] > a[x1][y1])
            max = std::max(max, work(x1, y1) + 1);
    }
    return f[x][y] = max;
}

int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    memset(f, 0, sizeof(f));
    int max = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            max = std::max(max, work(i, j));
    printf("%d\n", max);
}