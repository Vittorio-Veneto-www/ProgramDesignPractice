#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, T, a[10][10], mark[10][10], q[100][3];
        scanf("%d%d", &n, &T);
        int x0, y0;
        char s[11];
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < n; j++)
                switch (s[j])
                {
                    case '.':a[i][j] = 1;break;
                    case '#':a[i][j] = 0;break;
                    case 'S':a[i][j] = 1;q[0][0] = i;q[0][1] = j;mark[i][j] = 1;break;
                    case 'E':a[i][j] = 1;x0 = i;y0 = j;break;
                }
        }
        int h = -1, t = 0;
        q[0][2] = 0;
        [&]{
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                for (int i = 0; i < 4; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || !a[x1][y1] || mark[x1][y1])
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
            if (q[t][2] <= T)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("NO\n");
    }
}