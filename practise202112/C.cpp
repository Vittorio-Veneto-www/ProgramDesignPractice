#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, a[1000], f[1000][2];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        f[i][0] = 0, f[i][1] = 0;
        for (int j = 0; j < i; j++)
        {
            if (a[i] <= a[j])
            {
                f[i][0] = std::max(f[i][0], f[j][0]);
                f[i][1] = std::max(f[i][1], f[j][1]);
            }
            f[i][1] = std::max(f[i][1], f[j][0]);
        }
        f[i][0] += 1;
        f[i][1] += 1;
        max = std::max(max, f[i][0]);
        max = std::max(max, f[i][1]);
    }
    printf("%d\n", max);
}