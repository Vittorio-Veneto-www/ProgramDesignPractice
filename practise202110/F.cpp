#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int f[100000], q[1200000][4], mark[100000][4][3];

int main(void)
{
    memset(f, 0x7f, sizeof(f));
    memset(mark, 0, sizeof(mark));
    f[12345] = 0;
    int h = -1, t = 0;
    q[0][0] = 12345;
    q[0][1] = 0;
    q[0][2] = 0;
    q[0][3] = 0;
    mark[12345][0][0] = 1;
    while (h < t)
    {
        h++;
        int x = q[h][0], a[5];
        for (int i = 0; i < 5; i++)
            a[i] = x % 10, x /= 10;
        for (int i = 0; i < 4; i++)
        {
            std::swap(a[i], a[i + 1]);
            int x = 0;
            for (int i = 4; i >= 0; i--)
                x = x * 10 + a[i];
            if (!mark[x][q[h][1]][q[h][2]])
            {
                f[x] = std::min(f[x], q[h][3] + 1);
                mark[x][q[h][1]][q[h][2]] = 1;
                t++;
                q[t][0] = x;
                q[t][1] = q[h][1];
                q[t][2] = q[h][2];
                q[t][3] = q[h][3] + 1;
            }
            std::swap(a[i], a[i + 1]);
        }
        for (int i = 0; i < 5; i++)
        {
            int x, y = a[i];
            a[i] = (y + 1) % 10;
            x = 0;
            for (int i = 4; i >= 0; i--)
                x = x * 10 + a[i];
            if (q[h][1] < 3 && !mark[x][q[h][1] + 1][q[h][2]])
            {
                f[x] = std::min(f[x], q[h][3] + 1);
                mark[x][q[h][1] + 1][q[h][2]] = 1;
                t++;
                q[t][0] = x;
                q[t][1] = q[h][1] + 1;
                q[t][2] = q[h][2];
                q[t][3] = q[h][3] + 1;
            }
            a[i] = (y * 2) % 10;
            x = 0;
            for (int i = 4; i >= 0; i--)
                x = x * 10 + a[i];
            if (q[h][2] < 2 && !mark[x][q[h][1]][q[h][2] + 1])
            {
                f[x] = std::min(f[x], q[h][3] + 1);
                mark[x][q[h][1]][q[h][2] + 1] = 1;
                t++;
                q[t][0] = x;
                q[t][1] = q[h][1];
                q[t][2] = q[h][2] + 1;
                q[t][3] = q[h][3] + 1;
            }
            a[i] = y;
        }
    }
    char s[6];
    while (scanf("%s", s) != EOF)
    {
        int x = 0;
        for (int i = 0; i < 5; i++)
            x = x * 10 + s[i] - '0';
        if (f[x] != 0x7f7f7f7f)
            printf("%d\n", f[x]);
        else
            printf("-1\n");
    }
}