#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int a[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            scanf("%d", &a[i][j]);
    int f[25][3], h = -1, t = 0, delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    f[0][0] = 0;
    f[0][1] = 0;
    while (h < t)
    {
        h++;
        for (int i = 0; i < 4; i++)
        {
            int x = f[h][0] + delta[i][0], y = f[h][1] + delta[i][1];
            if ( x < 0 || x >= 5 || y < 0 || y >= 5 || a[x][y])
                continue;
            a[x][y] = 1;
            t++;
            f[t][0] = x, f[t][1] = y, f[t][2] = h;
            if (f[t][0] == 5 && f[t][1] == 5)
                break;
        }
        if (f[t][0] == 4 && f[t][1] == 4)
            break;
    }
    int q[25][2], cnt = 0;
    while (t)
    {
        q[cnt][0] = f[t][0], q[cnt][1] = f[t][1];
        cnt++;
        t = f[t][2];
    }
    printf("(0, 0)\n");
    for (int i = cnt; i; i--)
        printf("(%d, %d)\n", q[i - 1][0], q[i - 1][1]);
}