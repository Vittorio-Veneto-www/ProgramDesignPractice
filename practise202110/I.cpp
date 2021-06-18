#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int n, a[15][2], f[1 << 15][2];

int score(int t1, int t2)
{
    if (t1 < t2)
        return 0;
    return t1 - t2;
}

int judge(int x1, int x2)
{
    int cnt, a1[15], a2[15];
    cnt = 0;
    while (x1)
    {
        a1[cnt++] = f[x1][1];
        x1 -= 1 << f[x1][1];
    }
    cnt = 0;
    while (x2)
    {
        a2[cnt++] = f[x2][1];
        x2 -= 1 << f[x2][1];
    }
    for (;cnt; cnt--)
        if (a1[cnt - 1] > a2[cnt - 1])
            return 0;
        else if (a1[cnt - 1] < a2[cnt - 1])
            return 1;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int t[1 << 15];
        char names[15][51];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%s%d%d", names[i], &a[i][0], &a[i][1]);
        t[0] = 0;
        memset(f, 0x7f, sizeof(f));
        f[0][0] = 0;
        for (int i = 1; i < 1 << n; i++)
            for (int j = 0; j < n; j++)
                if (i & 1 << j)
                {
                    int x = i - (1 << j);
                    t[i] = t[x] + a[j][1];
                    if (f[i][0] >= f[x][0] + score(t[i], a[j][0]))
                    {
                        if (f[i][0] > f[x][0] + score(t[i], a[j][0]) || judge(x, i - (1 << f[i][1])))
                            f[i][1] = j;
                        f[i][0] = f[x][0] + score(t[i] , a[j][0]);
                    }
                }
        printf("%d\n", f[(1 << n) - 1][0]);
        int cnt = 0, x = (1 << n) - 1, b[15];
        while (x)
        {
            b[cnt++] = f[x][1];
            x -= 1 << f[x][1];
        }
        for (;cnt; cnt--)
            printf("%s\n", names[b[cnt - 1]]);
    }
}