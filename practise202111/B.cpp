#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        char s[101];
        scanf("%s", s);
        int n = strlen(s), f[100][100];
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; i++)
            f[i][i] = 1;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < n - i; j++)
                if (s[j] == s[j + i])
                    if (i == 1)
                        f[j][j + i] = 1;
                    else
                        if (f[j + 1][j + i - 1])
                            f[j][j + i] = 1;
        int max = 0, st, e;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                if (f[i][j] && max < j - i + 1)
                {
                    max = j - i + 1;
                    st = i;
                    e = j;
                }
        for (;st <= e; st++)
            printf("%c", s[st]);
        printf("\n");
    }
}