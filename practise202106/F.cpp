#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n = 5, m = 6, min = 1000000;
    char str[20];
    int *map = new int[30], *mark = new int[30], *push = new int[30];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &map[i * m + j]), map[i * m + j] = !map[i * m + j];
    for (int i = 0; i < 1 << m; i++)
    {
        memcpy(mark, map, sizeof(int) * n * m);
        memset(push, 0, sizeof(int) * n * m);
        for (int j = 0; j < m; j++)
            if (i & (1 << j))
            {
                push[j] = 1;
                mark[j] = !mark[j];
                if (j != 0)
                    mark[j - 1] = !mark[j - 1];
                if (j != m - 1)
                    mark[j + 1] = !mark[j + 1];
                mark[m + j] = !mark[m + j];
            }
        for (int k = 1; k < n; k++)
            for (int j = 0; j < m; j++)
                if (!mark[(k - 1) * m + j])
                {
                    push[k * m + j] = 1;
                    mark[k * m + j] = !mark[k * m + j];
                    if (j != 0)
                        mark[k * m + j - 1] = !mark[k * m + j - 1];
                    if (j != m - 1)
                        mark[k * m + j + 1] = !mark[k * m + j + 1];
                    if (k != n - 1)
                        mark[(k + 1) * m + j] = !mark[(k + 1) * m + j];
                }
        int mark1 = 1;
        for (int j = 0; j < m; j++)
            if (!mark[(n - 1) * m + j])
            {
                mark1 = 0;
                break;
            }
        if (mark1)
        {
            for (int i = 0; i < n; i++)
            {
                printf("%d", push[i * m]);
                for (int j = 1; j < m; j++)
                    printf(" %d", push[i * m + j]);
                printf("\n");
            }
        }
    }
}