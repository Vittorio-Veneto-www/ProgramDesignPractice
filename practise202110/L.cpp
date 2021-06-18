#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int a[3][100][2], b[3], c[3][4], mark[41][41][41][41], q[5000000][5], mark1[41][41], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int judge(int x, int dx1, int dy1, int y, int dx2, int dy2)
{
    if (c[x][0] + dx1 > c[y][0] + dx2)
    {
        std::swap(x, y);
        std::swap(dx1, dx2);
        std::swap(dy1, dy2);
    }
    if (c[x][2] + dx1 < c[y][0] + dx2)
        return 1;
    if (c[x][1] + dy1 > c[y][1] + dy2)
    {
        std::swap(x, y);
        std::swap(dx1, dx2);
        std::swap(dy1, dy2);
    }
    if (c[x][3] + dy1 < c[y][1] + dy2)
        return 1;
    return 0;
}

int main(void)
{
    while (1)
    {
        scanf("%d%d%d", &b[0], &b[1], &b[2]);
        if (!b[0])
            break;
        for (int i = 0; i < 3; i++)
        {
            c[i][0] = 10, c[i][1] = 10, c[i][2] = 0, c[i][3] = 0;
            for (int j = 0; j < b[i]; j++)
            {
                scanf("%d%d", &a[i][j][0], &a[i][j][1]);
                c[i][0] = std::min(c[i][0], a[i][j][0]);
                c[i][1] = std::min(c[i][1], a[i][j][1]);
                c[i][2] = std::max(c[i][2], a[i][j][0]);
                c[i][3] = std::max(c[i][3], a[i][j][1]);
            }
        }
        if (judge(0, 0, 0, 1, 0, 0) && judge(0, 0, 0, 2, 0, 0) && judge(1, 0, 0, 2, 0, 0))
        {
            printf("0\n");
            continue;
        }
        int h = -1, t = 0;
        q[0][0] = 0;
        q[0][1] = 0;
        q[0][2] = 0;
        q[0][3] = 0;
        q[0][4] = 0;
        memset(mark, 0 ,sizeof(mark));
        mark[0][0][0][0] = 1;
        [&]{
            while (h < t)
            {
                h++;
                int x1 = q[h][0], y1 = q[h][1], x2 = q[h][2], y2 = q[h][3];
                for (int i = 0; i < 4; i++)
                {
                    int dx1, dy1, dx2, dy2;
                    auto func = [&](){
                        int &m = mark[dx1 + 20][dy1 + 20][dx2 + 20][dy2 + 20];
                        if (m)
                            return 0;
                        else
                            m = 1;
                        memset(mark1, 0, sizeof(mark1));
                        for (int i = 0; i < b[0]; i++)
                            mark1[a[0][i][0] + 20][a[0][i][1] + 20] = 1;
                        for (int i = 0; i < b[1]; i++)
                        {
                            int &x = mark1[a[1][i][0] + dx1 + 20][a[1][i][1] + dy1 + 20];
                            if (x)
                                return 0;
                            else
                                x = 1;
                        }
                        for (int i = 0; i < b[2]; i++)
                        {
                            int &x = mark1[a[2][i][0] + dx2 + 20][a[2][i][1] + dy2 + 20];
                            if (x)
                                return 0;
                            else
                                x = 1;
                        }
                        t++;
                        q[t][0] = dx1;
                        q[t][1] = dy1;
                        q[t][2] = dx2;
                        q[t][3] = dy2;
                        q[t][4] = q[h][4] + 1;
                        if (judge(0, 0, 0, 1, dx1, dy1) && judge(0, 0, 0, 2, dx2, dy2) && judge(1, dx1, dy1, 2, dx2, dy2))
                            return 1;
                        return 0;
                    };
                    dx1 = x1 + delta[i][0];
                    dy1 = y1 + delta[i][1];
                    dx2 = x2;
                    dy2 = y2;
                    if (func())
                        return;
                    dx1 = x1;
                    dy1 = y1;
                    dx2 = x2 + delta[i][0];
                    dy2 = y2 + delta[i][1];
                    if (func())
                        return;
                    dx1 = x1 + delta[i][0];
                    dy1 = y1 + delta[i][1];
                    dx2 = x2 + delta[i][0];
                    dy2 = y2 + delta[i][1];
                    if (func())
                        return;
                }
            }
        }();
        if (h < t)
            printf("%d\n", q[t][4]);
        else
            printf("-1\n");
    }
}