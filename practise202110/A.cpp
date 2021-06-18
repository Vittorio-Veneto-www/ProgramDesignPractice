#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    long long f[100];
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= 50; i++)
        f[i] = f[i - 1] + f[i - 2];
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%lld\n", f[y - x]);
    }
}