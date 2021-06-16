#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>

int main(void)
{
    int n, a[1000];
    while (scanf("%d", &n) != EOF)
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]), sum += a[i];
        std::sort(a, a + n);
        if (a[n - 1] * 2 > sum)
            printf("%.1f\n", sum - a[n - 1]);
        else
            printf("%.1f\n", sum / 2);
    }
}