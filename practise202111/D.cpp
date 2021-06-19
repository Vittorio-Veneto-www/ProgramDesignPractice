#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[15][2];
    for (int i = 0; i < 15; i++)
        scanf("%d%d", &a[i][0], &a[i][1]);
    int max = 0;
    for (int i = 0; i < 1 << 15; i++)
    {
        int money = 0, cost = 0, d1 = 0, d2 = 0;
        for (int j = 0; j < 10; j++)
            if (i & 1 << j)
            {
                d1++;
                money += a[j][0];
                cost += a[j][1];
            }
        for (int j = 10; j < 15; j++)
            if (i & 1 << j)
            {
                d2++;
                money += a[j][0];
                cost += a[j][1];
            }
        if (d1 <= d2 && cost <= n && money > max)
            max = money;
    }
    printf("%d\n", max);
}