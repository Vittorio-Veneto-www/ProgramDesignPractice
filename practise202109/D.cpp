#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int m, a[100][2];
    scanf("%d", &m);
    while (m != -1)
    {
        int n = 0, x, y;
        scanf("%d%d", &x, &y);
        while (x != -1)
        {
            a[n][0] = x;
            a[n][1] = y;
            n++;
            scanf("%d%d", &x, &y);
        }
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            int x = m, y = 0, j = i;
            while (j < n && x >= a[j][1])
            {
                x -= a[j][1];
                y += a[j][0];
                j++;
            }
            max = std::max(max, y);
        }
        printf("%d\n", max);
        scanf("%d", &m);
    }
}