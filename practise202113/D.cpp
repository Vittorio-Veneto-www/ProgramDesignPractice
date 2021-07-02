#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, a[10][10];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        int q[10], mark[10];
        memset(mark, 0, sizeof(mark));
        int h = -1, t = 0;
        q[0] = 0;
        mark[0] = 1;
        while (h < t)
        {
            h++;
            int x = q[h];
            for (int i = 0; i < n; i++)
                if (!mark[i] && a[x][i] != -1)
                {
                    t++;
                    q[t] = i;
                    mark[i] = 1;
                }
        }
        if (mark[n - 1])
            printf("YES\n");
        else
            printf("NO\n");
    }
}