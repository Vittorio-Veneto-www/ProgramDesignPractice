#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, m, a[1000];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int l = 1, r = 10000000;
    while (l < r)
    {
        int mid = (l + r) >> 1, cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += a[i] / mid + !!(a[i] % mid);
        if (cnt > m)
            l = mid + 1;
        else
            r = mid;
    }
    printf("%d\n", l);
}