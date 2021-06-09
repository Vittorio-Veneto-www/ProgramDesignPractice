#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

char map[27 * 27][27 * 27 + 1];

void fraction(int depth, int x, int y, int end)
{
    if (depth == 1)
    {
        map[x][y] = 'X';
        if (end)
            map[x][y + 1] = 0;
        return;
    }
    int z = pow(3, depth - 2);
    fraction(depth - 1, x, y, 0);
    fraction(depth - 1, x, y + z * 2, 1 & end);
    fraction(depth - 1, x + z, y + z, 1 & end);
    fraction(depth - 1, x + z * 2, y, 0);
    fraction(depth - 1, x + z * 2, y + z * 2, 1 & end);
}

int main(void)
{
    int x;
    scanf("%d", &x);
    while (x != -1)
    {
        memset(map, ' ', sizeof(map));
        fraction(x, 0, 0, 1);
        int z = pow(3, x - 1);
        for (int i = 0; i < z; i++)
            printf("%s\n", map[i]);
        printf("-\n");
        scanf("%d", &x);
    }
}