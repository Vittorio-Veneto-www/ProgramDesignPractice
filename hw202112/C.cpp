#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int min = 1000000;
    char str1[40], str2[40];
    scanf("%s%s", str1, str2);
    int n = strlen(str1);
    int *init = new int[n], *target = new int[n], *mark = new int[n];
    for (int i = 0; i < n; i++)
        init[i] = str1[i] - '0', target[i] = str2[i] - '0';
    for (int i = 0; i < 2; i++)
    {
        int cnt = 0;
        memcpy(mark, init, sizeof(int) * n);
        if (i)
        {
            cnt++;
            mark[0] = !mark[0];
            mark[1] = !mark[1];
        }
        for (int j = 1; j < n; j++)
            if (mark[j - 1] != target[j - 1])
            {
                cnt++;
                mark[j - 1] = !mark[j - 1];
                mark[j] = !mark[j];
                if (j != n - 1)
                    mark[j + 1] = !mark[j + 1];
            }
        if (mark[n - 1] == target[n - 1])
            min = std::min(min, cnt);
    }
    if (min != 1000000)
        printf("%d\n", min);
    else
        printf("impossible\n");
}