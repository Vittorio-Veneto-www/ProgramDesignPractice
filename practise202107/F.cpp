#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int a[31];

int work(int n)
{
    if (a[n])
        return a[n];
    switch (n)
    {
        case 0: return 1;break;
        case 1: return 0;break;
        case 2: return 3;break;
        case 3: return 0;break;
        default: a[n] = 3 * work(n - 2);for (int i = 4; i <= n; i += 2) a[n] += 2 * work(n - i);return a[n];
    }
}

int main(void)
{
    int n;
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    while (n != -1)
    {
        printf("%d\n", work(n));
        scanf("%d", &n);
    }
}