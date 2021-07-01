#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef struct{
    int v, x, y;
} clue;

clue clues[10000];
int delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int cmp(const clue &a, const clue &b)
{
    return a.v < b.v;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, cnt = 0, a[100][100], mark[100][100], q[10000][3];
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &a[i][j]);
                if (a[i][j] > 1)
                {
                    clues[cnt].v = a[i][j];
                    clues[cnt].x = i;
                    clues[cnt].y = j;
                    cnt++;
                }
            }
        std::sort(clues, clues + cnt, cmp);
        int cx = 0, cy = 0, length = 0;
        for (int i = 0; i < cnt; i++)
        {
            memset(mark, 0, sizeof(mark));
            q[0][0] = cx;
            q[0][1] = cy;
            q[0][2] = 0;
            int x0 = clues[i].x, y0 = clues[i].y;
            if (cx == x0 && cy == y0)
                continue;
            mark[cx][cy] = 1;
            int h = -1, t = 0;
            [&]{
                while (h < t)
                {
                    h++;
                    int x = q[h][0], y = q[h][1];
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
            if (h == t)
                break;
            length += q[t][2];
            cx = x0, cy = y0;
        }
        if (cx == clues[cnt - 1].x && cy == clues[cnt - 1].y)
            printf("%d\n", length);
        else
            printf("-1\n");
    }
}