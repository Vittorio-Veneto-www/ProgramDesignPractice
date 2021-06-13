#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int t, a[500][500], mark[500][500], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, q[250000][2];

int main(void)
{
    char s[501];
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < m; j++)
                a[i][j] = s[j] == 'O';
        }
        auto func = [&](int x, int y){
            int h = -1, t = 0;
            q[0][0] = x;
            q[0][1] = y;
            a[x][y] = 0;
            mark[x][y] = 1;
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || !a[x1][y1])
                        continue;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                    a[x1][y1] = 0;
                    mark[x1][y1] = 1;
                }
            }
        };
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
        {
            if (a[i][0])
                func(i, 0);
            if (a[i][m - 1])
                func(i, m - 1);
        }
        for (int i = 0; i < m; i++)
        {
            if (a[0][i])
                func(0, i);
            if (a[n - 1][i])
                func(n - 1, i);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                printf("%c", mark[i][j] ? 'O': 'X');
            printf("\n");
        }
        printf("\n");
    }
}