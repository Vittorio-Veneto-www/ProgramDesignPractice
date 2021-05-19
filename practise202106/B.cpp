#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int gcd(int x, int y)
{
    while (y)
    {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main()
{
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    int max1 = 1, max2 = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
        {
            if (j * b >= i * a)
                break;
            if (gcd(i, j) == 1)
                if (j * max1 > i * max2)
                    max1 = i, max2 = j;
        }
    printf("%d %d\n", max2, max1);
}