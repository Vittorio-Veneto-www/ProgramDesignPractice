#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, v, a[100][100], mark[100][100][11][4], q[440000][4], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int h, t, x0, y01;
char s[100][101];

int jump(int x1, int y1, int v, int i)
{
    for (int j = 1; j <= v; j++)
    {
        int x2 = x1 + delta[i][0] * j, y2 = y1 + delta[i][1] * j;
        if (x2 < 0)
            x2 = 0;
        if (x2 >= n)
            x2 = n - 1;
        if (y2 < 0)
            y2 = 0;
        if (y2 >= m)
            y2 = m - 1;
        if (s[x2][y2] == '#' || mark[x2][y2][j][i])
            continue;
        mark[x2][y2][j][i] = 1;
        if (s[x2][y2] == 'E')
            if (jump(x2, y2, j, i))
                return 1;
        t++;
        q[t][0] = x2;
        q[t][1] = y2;
        q[t][2] = j;
        q[t][3] = q[h][3] + 1;
        if (x2 == x0 && y2 == y01)
            return 1;
    }
    return 0;
}

int main(void)
{
    int T = 0;
    scanf("%d%d%d", &n, &m, &v);
    while (n)
    {
        T++;
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s[i]);
            for (int j = 0; j < m; j++)
                switch (s[i][j])
                {
                    case 'S':q[0][0] = i;q[0][1] = j;mark[i][j][v][0] = 1;break;
                    case 'T':x0 = i;y01 = j;break;
                }
        }
        h = -1;
        t = 0;
        q[0][2] = v;
        q[0][3] = 0;
        [&]{
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1], v = q[h][2];
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || s[x1][y1] == '#' || mark[x1][y1][v][i])
                        continue;
                    if (s[x1][y1] == 'E')
                        if (jump(x1, y1, v, i))
                            return;
                    mark[x1][y1][v][i] = 1;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                    q[t][2] = v;
                    q[t][3] = q[h][3] + 1;
                    if (x1 == x0 && y1 == y01)
                        return;
                }
            }
        }();
        if (h != t)
            printf("Case #%d: %d\n", T, q[t][3]);
        else
            printf("Case #%d: -1\n", T);
        scanf("%d%d%d", &n, &m, &v);
    }
}