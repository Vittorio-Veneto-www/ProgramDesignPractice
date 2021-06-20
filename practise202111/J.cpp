#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

char s[26], ans[26], min;

void work(int x, int y, int dep)
{
    if (dep >= min)
        return;
    if (x == y)
    {
        min = dep;
        s[dep] = 0;
        memcpy(ans, s, 26);
        return;
    }
    int z = log(x / y) / log(2);
    if (dep + z >= min)
        return;
    s[dep] = 'H';
    work(x * 3, y, dep + 1);
    s[dep] = 'O';
    work(x / 2, y, dep + 1);
}

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    while (n)
    {
        min = 26;
        work(n, m, 0);
        printf("%d\n%s\n", min, ans);
        scanf("%d%d", &n, &m);
    }
}