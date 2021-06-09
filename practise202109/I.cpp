#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int a[100][100], mark[100][100][10], q[100000][3], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, k, x0, y0, xe, ye;
        scanf("%d%d%d", &n, &m, &k);
        char s[200];
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < m; j++)
                switch (s[j])
                {
                    case '.': a[i][j] = 1;break;
                    case 'S': a[i][j] = 1;x0 = i;y0 = j;break;
                    case 'E': a[i][j] = 1;xe = i;ye = j;break;
                    case '#': a[i][j] = 0;break;
                }
        }
        memset(mark, 0, sizeof(mark));
        int h = -1, t = 0;
        q[0][0] = x0;
        q[0][1] = y0;
        q[0][2] = 0;
        mark[x0][y0][0] = 1;
        while (h < t)
        {
            h++;
            int x = q[h][0], y = q[h][1], z = q[h][2];
            z++;
            auto f = [&](){
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || mark[x1][y1][z % k])
                        continue;
                    if (a[x1][y1])
                    {
                        t++;
                        q[t][0] = x1;
                        q[t][1] = y1;
                        q[t][2] = z;
                        mark[x1][y1][z % k] = 1;
                    }
                    else
                        if (!(z % k))
                        {
                            t++;
                            q[t][0] = x1;
                            q[t][1] = y1;
                            q[t][2] = z;
                            mark[x1][y1][z % k] = 1;
                        }
                    if (x1 == xe && y1 == ye)
                        return 1;
                }
                return 0;
            };
            if (f())
                break;
        }
        if (h != t)
            printf("%d\n", q[t][2]);
        else
            printf("Oop!\n");
    }
}