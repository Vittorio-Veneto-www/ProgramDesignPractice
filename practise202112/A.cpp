#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, a[100][100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    int mark = 2, x = -1, y = -1;
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            cnt += a[i][j];
        if (cnt % 2)
            if (mark == 2)
            {
                mark = 1;
                x = i;
            }
            else
            {
                mark = 0;
                break;
            }
    }
    if (!mark)
    {
        printf("Corrupt\n");
        return 0;
    }
    mark = 2;
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            cnt += a[j][i];
        if (cnt % 2)
            if (mark == 2)
            {
                mark = 1;
                y = i;
            }
            else
            {
                mark = 0;
                break;
            }
    }
    if (!mark || ((x == -1) ^ (y == -1)))
    {
        printf("Corrupt\n");
        return 0;
    }
    if (x == -1)
        printf("OK\n");
    else
        printf("%d %d\n", x + 1, y + 1);
}