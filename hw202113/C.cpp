#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

char map[1 << 10][1 << 11];

void sierpinski(int depth, int x, int y)
{
    if (depth == 1)
    {
        map[x][y + 1] = '/';
        map[x][y + 2] = '\\';
        map[x + 1][y] = '/';
        map[x + 1][y + 1] = '_';
        map[x + 1][y + 2] = '_';
        map[x + 1][y + 3] = '\\';
        return;
    }
    sierpinski(depth - 1, x, y + (1 << depth - 1));
    sierpinski(depth - 1, x + (1 << depth - 1), y);
    sierpinski(depth - 1, x + (1 << depth - 1), y + (1 << depth));
}

int main(void)
{
    int x;
    scanf("%d", &x);
    while (x)
    {
        memset(map, ' ', sizeof(map));
        sierpinski(x, 0, 0);
        for (int i = 0; i < 1 << x; i++)
            map[i][(1 << x) + i + 1] = 0, printf("%s\n", map[i]);
        printf("\n");
        scanf("%d", &x);
    }
}