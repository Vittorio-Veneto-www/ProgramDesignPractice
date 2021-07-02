#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    int T, T1 = 0;
    scanf("%d", &T);
    while (T1 < T)
    {
        T1++;
        int n, m, a[100][100], q[10000][3], mark[100][100];
        char s[100][101];
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        int x0, y0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                switch (s[i][j])
                {
                    case '#': a[i][j] = 0;break;
                    case '.': a[i][j] = 1;break;
                    case 'I': q[0][0] = i;q[0][1] = j;a[i][j] = 1;break;
                    case 'B': x0 = i;y0 = j;a[i][j] = 1;break;
                    default: a[i][j] = 1;
                }
        memset(mark, 0, sizeof(mark));
        mark[q[0][0]][q[0][1]] = 1;
        q[0][2] = 0;
        int h = -1, t = 0;
        [&]{
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                if (s[x][y] >= 'a' && s[x][y] <= 'z')
                {
                    int x1, y1;
                    for (x1 = 0; x1 < n; x1++)
                    {
                        for (y1 = 0; y1 < m; y1++)
                            if (s[x1][y1] == s[x][y] && (x != x1 || y != y1))
                                break;
                        if (y1 < m)
                            break;
                    }
                    if (!mark[x1][y1])
                    {
                        mark[x1][y1] = 1;
                        t++;
                        q[t][0] = x1;
                        q[t][1] = y1;
                        q[t][2] = q[h][2] + 1;
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || mark[x1][y1] || !a[x1][y1])
                        continue;
                    mark[x1][y1] = 1;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                    q[t][2] = q[h][2] + 1;
                    if (x1 == x0 && y1 == y0)
                        return;
                }
            }
        }();
        if (h != t)
            printf("Case #%d: %d\n", T1, q[t][2]);
        else
            printf("Case #%d: -1\n", T1);
    }
}