#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>

int main(void)
{
    int n, m, a[100000], max = 0, sum = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]), max = std::max(max, a[i]), sum += a[i];
    int l = max, r = sum, mid;
    while (l != r)
    {
        mid = (l + r) >> 1;
        int cnt = 0, sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += a[i];
            if (sum > mid)
                sum = a[i], cnt++;
        }
        cnt++;
        if (cnt <= m)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", r);
}