#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main()
{
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int i = d + 1;
    for (;(i - a) % 23; i++);
    for (;(i - b) % 28; i += 23);
    for (;(i - c) % 33; i += 23 * 28);
    printf("%d\n", i - d);
}