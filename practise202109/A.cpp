#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, a[16][2], score[4], min;

int cmp(int x, int y)
{
    return x > y;
}

void work(int t)
{
    if (t == n)
    {
        int x[4];
        memcpy(x, score, sizeof(score));
        std::sort(x, x + 4, cmp);
        int i;
        for (i = 0; score[0] != x[i]; i++);
        min = std::min(min, i);
        return;
    }
    score[a[t][0]]++;
    work(t + 1);
    score[a[t][0]]--;
    score[a[t][1]]++;
    work(t + 1);
    score[a[t][1]]--;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        char s[10];
        memset(score, 0, sizeof(score));
        n = 0;
        for (int i = 0; i < 4; i++)
        {
            scanf("%s", s);
            for (int j = 0; j < 4; j++)
                switch (s[j])
                {
                    case 'W': score[i]++;break;
                    case '?':
                        if (i < j)
                        {
                            a[n][0] = i;
                            a[n][1] = j;
                            n++;
                        }
                }
        }
        min = 4;
        work(0);
        printf("%d\n", min + 1);
    }
}