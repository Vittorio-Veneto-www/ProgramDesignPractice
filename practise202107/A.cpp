#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, x, y, a[100], b[100];
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 0; i < x; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < y; i++)
        scanf("%d", &b[i]);
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (a[i % x] == 0)
        {
            if (b[i % y] == 2)
                cnt++;
            else if (b[i % y] == 5)
                cnt--;
        }
        else if (a[i % x] == 2)
        {
            if (b[i % y] == 5)
                cnt++;
            else if (b[i % y] == 0)
                cnt--;
        }
        else
        {
            if (b[i % y] == 0)
                cnt++;
            else if (b[i % y] == 2)
                cnt--;
        }
    if (cnt == 0)
        printf("draw\n");
    else if (cnt > 0)
        printf("A");
    else
        printf("B\n");
}