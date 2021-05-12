#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, min = 1000000;
    char str[20];
    scanf("%d", &n);
    int *map = new int[n * n], *mark = new int[n * n];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", str);
        for (int j = 0; j < n; j++)
            map[i * n + j] = str[j] == 'y';
    }
    for (int i = 0; i < 1 << n; i++)
    {
        int cnt = 0;
        memcpy(mark, map, sizeof(int) * n * n);
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
            {
                cnt++;
                mark[j] = !mark[j];
                if (j != 0)
                    mark[j - 1] = !mark[j - 1];
                if (j != n - 1)
                    mark[j + 1] = !mark[j + 1];
                mark[n + j] = !mark[n + j];
            }
        for (int k = 1; k < n; k++)
            for (int j = 0; j < n; j++)
                if (!mark[(k - 1) * n + j])
                {
                    cnt++;
                    mark[k * n + j] = !mark[k * n + j];
                    if (j != 0)
                        mark[k * n + j - 1] = !mark[k * n + j - 1];
                    if (j != n - 1)
                        mark[k * n + j + 1] = !mark[k * n + j + 1];
                    if (k != n - 1)
                        mark[(k + 1) * n + j] = !mark[(k + 1) * n + j];
                }
        int mark1 = 1;
        for (int j = 0; j < n; j++)
            if (!mark[(n - 1) * n + j])
            {
                mark1 = 0;
                break;
            }
        if (mark1)
            min = std::min(min, cnt);
    }
    if (min != 1000000)
        printf("%d\n", min);
    else
        printf("inf\n");
}