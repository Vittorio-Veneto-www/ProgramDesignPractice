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
        int n, a[50][2];
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &a[i][0], &a[i][1]);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (a[i][0] > a[j][0] || (a[i][0] == a[j][0] && a[i][1] > a[j][1]))
                {
                    std::swap(a[i][0], a[j][0]);
                    std::swap(a[i][1], a[j][1]);
                }
        int cur = 1;
        for (int i = 1; i < n; i++)
            if (a[i][0] != a[i - 1][0] || a[i][1] != a[i - 1][1])
            {
                a[cur][0] = a[i][0];
                a[cur][1] = a[i][1];
                cur++;
            }
        n = cur;
        int cnt = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    for (int t = k + 1; t < n; t++)
                        if (a[i][0] == a[j][0] && a[k][0] == a[t][0] && a[i][1] == a[k][1] && a[j][1] == a[t][1])
                            cnt++;
        printf("%d\n", cnt);
    }
}