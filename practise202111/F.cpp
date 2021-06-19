#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, T, a[255][255], mark[255][255], q[65535][2], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    scanf("%d%d%d", &n, &m, &T);
    while (n)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &a[i][j]);
        memset(mark, 0, sizeof(mark));
        auto func = [&](int x, int y){
            int h = -1, t = 0;
            mark[x][y] = 1;
            q[0][0] = x;
            q[0][1] = y;
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || abs(a[x1][y1] - a[x][y]) > T || mark[x1][y1])
                        continue;
                    mark[x1][y1] = 1;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                }
            }
        };
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!mark[i][j])
                {
                    cnt++;
                    func(i, j);
                }
        printf("%d\n", cnt);
        scanf("%d%d%d", &n, &m, &T);
    }
}