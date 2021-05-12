#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

char table[9][10] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};

void op(int* time, int x)
{
    for (int i = strlen(table[x]); i; i--)
    {
        int y = table[x][i - 1] - 'A';
        time[y] = (time[y] + 1) % 4;
    }
}

int main(void)
{
    int time[9];
    for (int i = 0; i < 9; i++)
        scanf("%d", &time[i]);
    int mark[9];
    memset(mark, 0 ,sizeof(mark));
    for (int t = 0; t < 1 << 18; t++)
    {
        mark[0]++;
        op(time, 0);
        for (int i = 0; mark[i] == 4; i++)
        {
            mark[i] = 0;
            mark[i + 1]++;
            op(time, i + 1);
        }
        int m = 1;
        for (int i = 0; i < 9; i++)
            if (time[i])
                m = 0;
        if (m)
            break;
    }
    int first = 1;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < mark[i]; j++)
        {
            if (!first)
                printf(" ");
            first = 0;
            printf("%d", i + 1);
        }
}