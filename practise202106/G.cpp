#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int judge(int x, int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (x % (n - 1))
            break;
        else
            x = x / (n - 1) * n + 1;
    if (i == n)
    {
        printf("%d\n", x);
        return 0;
    }
    else
        return 1;
}

int main()
{
    int n;
    scanf("%d", &n);
    int x = n - 1;
    for (;judge(x, n); x += n - 1);
}