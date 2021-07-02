#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, m;
    char a[10][11], b[10][11];
    scanf("%d%d", &n, &m);
    while (n)
    {
        for (int i = 0; i < n; i++)
            scanf("%s", a[i]);
        for (int i = 0; i < m; i++)
            scanf("%s", b[i]);
        int x, y;
        [&]{
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (b[i][j] == '*')
                    {
                        x = i;
                        y = j;
                        return;
                    }
        }();
        auto func = [&]{
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (a[i][j] == '*')
                    {
                        for (int k = 0; k < m; k++)
                            for (int t = 0; t < m; t++)
                                if (b[k][t] == '*')
                                {
                                    int x1 = i + k - x, y1 = j + t - y;
                                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || a[x1][y1] != '*')
                                        return 0;
                                    a[x1][y1] = '.';
                                }
                        return 1;
                    }
            return 0;
        };
        if (!func())
        {
            printf("0\n");
            scanf("%d%d", &n, &m);
            continue;
        }
        if (!func())
        {
            printf("0\n");
            scanf("%d%d", &n, &m);
            continue;
        }
        x = -1;
        [&]{
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (a[i][j] == '*')
                    {
                        x = i;
                        return;
                    }
        }();
        if (x == -1)
            printf("1\n");
        else
            printf("0\n");
        scanf("%d%d", &n, &m);
    }
}