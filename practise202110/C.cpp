#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int a[100][100], q[10000][2], delta[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int n, m;
    scanf("%d%d", &n, &m);
    while (n)
    {
        char s[101];
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < m; j++)
                a[i][j] = s[j] == '@';
        }
        int cnt = 0;
        auto func = [&](int x, int y){
            cnt++;
            int h = -1, t = 0;
            q[0][0] = x;
            q[0][1] = y;
            a[x][y] = 0;
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                for (int i = 0; i < 8; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || !a[x1][y1])
                        continue;
                    t++;
                    q[t][0] = x1, q[t][1] = y1;
                    a[x1][y1] = 0;
                }
            }
        };
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i][j])
                    func(i, j);
        printf("%d\n", cnt);
        scanf("%d%d", &n, &m);
    }
}