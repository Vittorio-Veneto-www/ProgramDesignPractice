#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n;
    scanf("%d", &n);
    int min = 4 * n + n * n;
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            if (!(n % (i * j)))
            {
                int k = n / i / j;
                min = std::min(min, 2 * i * j + 2 * j * k + 2 * k * i);
            }
    printf("%d\n", min);
}