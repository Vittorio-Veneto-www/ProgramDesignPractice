#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int a[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            scanf("%d", &a[i][j]);
    int min, max, x, y, mark = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            min = a[i][j], max = a[i][j];
            for (int k = 0; k < 5; k++)
                min = std::min(min, a[k][j]);
            for (int k = 0; k < 5; k++)
                max = std::max(max, a[i][k]);
            if (min == a[i][j] && max == a[i][j])
            {
                mark = 1;
                x = i;
                y = j;
            }
        }
    if (mark)
        printf("%d %d %d\n", x + 1, y + 1, a[x][y]);
    else
        printf("not found\n");
}