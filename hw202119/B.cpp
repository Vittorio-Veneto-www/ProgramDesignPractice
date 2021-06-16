#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cmath>

int main(void)
{
    int n, m;
    double a[10000], max = 0;
    scanf("%d%d", &n, &m);
    m++;
    for (int i = 0; i < n; i++)
        scanf("%lf", &a[i]), a[i] = a[i] * a[i] * 4 * atan(1), max = std::max(max, a[i]);
    double l = 0, r = max, mid;
    while (r - l > 1e-6)
    {
        mid = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < n; i++)
            cnt += a[i] / mid;
        if (cnt < m)
            r = mid;
        else
            l = mid;
    }
    printf("%.3lf\n", l);
}