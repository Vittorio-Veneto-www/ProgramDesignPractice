#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int f[1001][1001];

int main(void)
{
    int t;
    scanf("%d", &t);
    char *a = new char[1010], *b = new char[1010];
    while (t--)
    {
        scanf("%s%s", a, b);
        if (strlen(a) > strlen(b))
            std::swap(a, b);
        int n = strlen(a), m = strlen(b);
        for (int j = 0; j <= m; j++)
            f[0][j] = j;
        for (int i = 0; i <= n; i++)
            f[i][0] = i;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i] == b[j])
                    f[i + 1][j + 1] = f[i][j];
                else
                    f[i + 1][j + 1] = std::min(f[i][j], std::min(f[i + 1][j], f[i][j + 1])) + 1;
        printf("%d\n", f[n][m]);
    }
}