#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int area(int x, int y, int l, int r, int b, int t)
{
    if (x <= l || y <= b)
        return x * y;
    if (x >= r && y >= t)
        return x * y - (r - l) * (t - b);
    return x * y - (x - l) * (y - b);
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m, L;
        scanf("%d%d%d", &n, &m, &L);
        int l, r, b, t;
        scanf("%d%d%d%d", &l, &r, &b, &t);
        int max = 0;
        for (int i = 1; i <= m; i++)
        {
            int j = L / 2 - i;
            if (j > n)
                j = n;
            if (j <= 0)
                break;
            if (i >= r - l && j >= t - b)
                max = std::max(max, i * j - (r - l) * (t - b));
            max = std::max(max, area(i, j, l, r, b, t));
            max = std::max(max, area(i, j, l, r, n - t, n - b));
            max = std::max(max, area(i, j, m - r, m - l, b, t));
            max = std::max(max, area(i, j, m - r, m - l, n - t, n - b));
        }
        printf("%d\n", max);
    }
}