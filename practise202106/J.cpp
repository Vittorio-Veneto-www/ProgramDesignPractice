#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>


void hanoi(int t, char a, char b, char c)
{
    if (!t)
        return;
    hanoi(t - 1, a, c, b);
    printf("%c->%d->%c\n", a, t, b);
    hanoi(t - 1, c, b, a);
}

int main()
{
    int n;
    char a, b, c;
    scanf("%d%*c%c%*c%c%*c%c", &n, &a, &b, &c);
    hanoi(n, a, b, c);
}