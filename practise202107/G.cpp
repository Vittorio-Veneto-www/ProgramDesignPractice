#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int a[1001], f[1001];

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        f[i] = a[i];
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                f[i] = std::max(f[i], f[j] + a[i]);
        max = std::max(max, f[i]);
    }
    printf("%d\n", max);
}