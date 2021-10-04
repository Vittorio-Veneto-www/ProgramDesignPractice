#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int a[2][100000], b[2][100000];

int main(void)
{
    int n;
    long long m;
	scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &a[0][i], &a[1][i]);
    memcpy(b, a, sizeof(a));
    std::sort(b[0], b[0] + n);
    std::sort(b[1], b[1] + n);
    int l = b[0][n / 2], r = b[1][n / 2] + 1;
    while (r - l > 1)
    {
        int mid = (l + r) >> 1;
        long long sum = 0;
        int cnt = n / 2, num = 0;
        for (int i = 0; i < n; i++)
            if (a[1][i] < mid)
            {
                sum += a[0][i];
                cnt--;
            }
            else if (a[0][i] > mid)
                sum += a[0][i];
            else
                b[0][num++] = a[0][i];
        std::sort(b[0], b[0] + num);
        for (int i = 0; i < cnt; i++)
            sum += b[0][i];
        sum += (long long)mid * (num - cnt);
        if (sum > m)
            r = mid;
        else
            l = mid;
    }
    printf("%d\n", l);
}