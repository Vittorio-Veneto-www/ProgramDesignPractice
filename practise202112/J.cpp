#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int map[8][100][100], a[100][100], mark[100][100][256], q[2560000][4], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    int n, m, cnt = 0;
    char s[100][101];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", s[i]);
    int x0, y0;
    memset(map, 0, sizeof(map));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            switch (s[i][j])
            {
                case '#': a[i][j] = 0;break;
                case '.': a[i][j] = 1;break;
                case 'I': q[0][0] = i;q[0][1] = j;a[i][j] = 1;break;
                case 'O': x0 = i;y0 = j;a[i][j] = 1;break;
                case 'w':
                case 'a':
                case 's':
                case 'd':
                    a[i][j] = 0;
                    break;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int x = i, y = j;
            switch (s[i][j])
            {
                case 'w':
                    x--;
                    while (x >= 0 && a[x][y])
                        map[cnt][x][y] = 1, x--;
                    cnt++;
                    break;
                case 'a':
                    y--;
                    while (y >= 0 && a[x][y])
                        map[cnt][x][y] = 1, y--;
                    cnt++;
                    break;
                case 's':
                    x++;
                    while (x < n && a[x][y])
                        map[cnt][x][y] = 1, x++;
                    cnt++;
                    break;
                case 'd':
                    y++;
                    while (y < m && a[x][y])
                        map[cnt][x][y] = 1, y++;
                    cnt++;
                    break;
            }
        }
    q[0][2] = 0;
    for (int i = 0; i < cnt; i++)
        if (map[i][q[0][0]][q[0][1]])
            q[0][2] |= 1 << i;
    memset(mark, 0, sizeof(mark));
    mark[q[0][0]][q[0][1]][q[0][2]] = 1;
    q[0][3] = 0;
    int h = -1, t = 0;
    [&]{
        while (h < t)
        {
            h++;
            int x = q[h][0], y = q[h][1], z = q[h][2];
            for (int i = 0; i < 4; i++)
            {
                int x1 = x + delta[i][0], y1 = y + delta[i][1], z1 = z;
                if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || !a[x1][y1])
                    continue;
                for (int i = 0; i < cnt; i++)
                    if (map[i][x1][y1])
                        z1 |= 1 << i;
                if (mark[x1][y1][z1])
                    continue;
                mark[x1][y1][z1] = 1;
                t++;
                q[t][0] = x1;
                q[t][1] = y1;
                q[t][2] = z1;
                q[t][3] = q[h][3] + 1;
                if (x1 == x0 && y1 == y0 && z1 == (1 << cnt) - 1)
                    return;
            }
        }
    }();
    if (h != t)
        printf("%d\n", q[t][3]);
    else
        printf("-1\n");
}