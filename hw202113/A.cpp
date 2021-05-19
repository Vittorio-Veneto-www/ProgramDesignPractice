#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int ops[100], val[100], cntop, cntval;

void proc(int op)
{
    int x, y;
    if (op != -1)
        while (cntop && op >= ops[cntop - 1])
        {
            switch (ops[cntop - 1])
            {
                case 0:
                    x = val[--cntval];
                    val[cntval++] = !x;
                    break;
                case 1:
                    x = val[--cntval], y = val[--cntval];
                    val[cntval++] = x & y;
                    break;
                case 2:
                    x = val[--cntval], y = val[--cntval];
                    val[cntval++] = x | y;
                    break;
            }
            cntop--;
        }
    else
    {
        while (ops[cntop - 1] != 3)
        {
            switch (ops[cntop - 1])
            {
                case 0:
                    x = val[--cntval];
                    val[cntval++] = !x;
                    break;
                case 1:
                    x = val[--cntval], y = val[--cntval];
                    val[cntval++] = x & y;
                    break;
                case 2:
                    x = val[--cntval], y = val[--cntval];
                    val[cntval++] = x | y;
                    break;
            }
            cntop--;
        }
        cntop--;
    }
}

int main(void)
{
    char str[10000];
    int t = 0;
    while (scanf("%[^\n]%*c", str) != EOF)
    {
        int len = strlen(str);
        cntop = 0;
        cntval = 0;
        for (int i = 0; i < len; i++)
            switch (str[i])
            {
                case 'V': val[cntval++] = 1;break;
                case 'F': val[cntval++] = 0;break;
                case '!': ops[cntop++] = 0;break;
                case '&': proc(1);ops[cntop++] = 1;break;
                case '|': proc(2);ops[cntop++] = 2;break;
                case '(': ops[cntop++] = 3;break;
                case ')': proc(-1);break;
            }
        proc(3);
        printf("Expression %d: %c\n", ++t, val[0] ? 'V' : 'F');
    }
}