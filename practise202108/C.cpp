#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    int a[3], b[3] = {0}, c[3][10], max = 0;
    scanf("%d%d%d", &a[0], &a[1], &a[2]);
    for (int i = 0; i < 3; i++)
        while (a[i])
        {
            c[i][b[i]++] = a[i] % 10;
            max = std::max(max, c[i][b[i] - 1]);
            a[i] /= 10;
        }
    int x;
    for (x = max + 1; x <= 16; x++)
    {
        for (int i = 0; i < 3; i++)
        {
            a[i] = 0;
            for (int j = b[i]; j; j--)
                a[i] = a[i] * x + c[i][j - 1];
        }
        if (a[0] * a[1] == a[2])
            break;
    }
    if (x != 17)
        printf("%d\n", x);
    else
        printf("0\n");
}