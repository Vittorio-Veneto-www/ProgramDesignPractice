#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int a, b, i, j;
    scanf("%d%d%d%d", &a, &b, &i, &j);
    for (;i <= j; i++)
        if (b & 1 << i)
        {
            if (a & 1 << i)
                a ^= 1 << i;
        }
        else
        {
            if (!(a & 1 << i))
                a |= 1 << i;
        }
    printf("%d\n", a);
}