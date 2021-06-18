#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

char s[255][256];
int q[65536 * 5][4], mark[255][255][5], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, h1;
        scanf("%d%d%d", &n, &m, &h1);
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        int h = -1, t = 0;
        q[0][0] = 0;
        q[0][1] = 0;
        q[0][2] = h1 - 1;
        q[0][3] = 0;
        memset(mark, 0, sizeof(mark));
        mark[0][0][h - 1] = 1;
        [&](){
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1], z = q[h][2];
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1], z1 = z;
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || s[x1][y1] == '#')
                        continue;
                    if (s[x1][y1] == '*')
                        z1--;
                    if (z1 < 0 || mark[x1][y1][z1])
                        continue;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                    q[t][2] = z1;
                    q[t][3] = q[h][3] + 1;
                    mark[x1][y1][z1] = 1;
                    if (x1 == n - 1 && y1 == m - 1)
                        return;
                }
            }
        }();
        printf("%d\n", q[t][3]);
    }
}