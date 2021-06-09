#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int q[3200000][5], a[100][100], mark[100][100][10][32], snake[5][2], cnt, delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char s[100][101];

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    while (n)
    {
        cnt = 0;
        memset(a, 0, sizeof(a));
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s[i]);
            for (int j = 0; j < n; j++)
                if (s[i][j] == '#')
                    a[i][j] = 1;
                else if (s[i][j] == 'K')
                    q[0][0] = i, q[0][1] = j, mark[i][j][0][0] = 1;
                else if (s[i][j] == 'S')
                {
                    snake[cnt][0] = i, snake[cnt][1] = j;
                    cnt++;
                }
        }
        int h = -1, t = 0;
        q[0][2] = 0;
        q[0][3] = 0;
        q[0][4] = 0;
        auto f = [&](){
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                if (s[x][y] == 'S')
                {
                    int num;
                    for (num = 0; !(snake[num][0] == x && snake[num][1] == y); num++);
                    if (!(q[h][3] & 1 << num))
                    {
                        t++;
                        q[t][0] = x;
                        q[t][1] = y;
                        q[t][2] = q[h][2];
                        q[t][3] = q[h][3] | 1 << num;
                        q[t][4] = q[h][4] + 1;
                        mark[x][y][q[t][2]][q[t][3]] = 1;
                        continue;
                    }
                }
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1], z = q[h][2];
                    if (s[x1][y1] >= '1' && s[x1][y1] <= '9')
                        if (z == s[x1][y1] - '1')
                            z++;
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || a[x1][y1] || mark[x1][y1][z][q[h][3]])
                        continue;
                    t++;
                    if (s[x1][y1] == 'T' && z == m)
                        return;
                    q[t][0] = x1, q[t][1] = y1;
                    q[t][2] = z;
                    q[t][3] = q[h][3];
                    q[t][4] = q[h][4] + 1;
                    mark[x1][y1][q[t][2]][q[t][3]] = 1;
                }
            }
        };
        f();
        if (h != t)
            printf("%d\n", q[h][4] + 1);
        else
            printf("impossible\n");
        scanf("%d%d", &n, &m);
    }
}