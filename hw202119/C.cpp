#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>

int main(void)
{
    int L, n, m, a[50000];
    scanf("%d%d%d", &L, &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    a[n] = L;
    int l = 0, r = L + 1, mid;
    while (r - l > 1)
    {
        mid = (l + r) >> 1;
        int pos = 0, cnt = 0;
        for (int i = 0; i <= n; i++)
            if (pos + mid > a[i])
                cnt++;
            else
                pos = a[i];
        if (cnt > m)
            r = mid;
        else
            l = mid;
    }
    printf("%d\n", l);
}