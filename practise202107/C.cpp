#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int d, n, a[20][3];
    scanf("%d%d", &d, &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    int max = 0, cnt = 0;
    for (int i = 0; i <= 1024; i++)
        for (int j = 0; j <= 1024; j++)
        {
            int x = 0;
            for (int k = 0; k < n; k++)
                if (abs(a[k][0] - i) <= d && abs(a[k][1] - j) <= d)
                    x += a[k][2];
            if (max < x)
            {
                max = x;
                cnt = 1;
            }
            else if (max == x)
                cnt++;
        }
    printf("%d %d\n", cnt, max);
}