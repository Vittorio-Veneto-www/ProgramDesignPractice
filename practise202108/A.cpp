#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int n;
    scanf("%d", &n);
    int x, y, z;
    for (int i = 2; i <= n; i++)
    {
        x = i * i * i;
        for (int j = 2; j * j * j <= x; j++)
        {
            y = j * j * j;
            for (int k = j; y + k * k * k <= x; k++)
            {
                z = k * k * k;
                for (int t = k; y + z + t * t * t <= x; t++)
                    if (y + z + t * t * t == x)
                        printf("Cube = %d, Triple = (%d,%d,%d)\n", i, j, k, t);
            }
        }
    }
}