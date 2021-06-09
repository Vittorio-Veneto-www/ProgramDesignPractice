#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int s, n;
int a[11], mark[40][40];

int judge(int x, int y, int z)
{
    if (x + z - 1 >= s || y + z - 1 >= s)
        return 0;
    for (int i = 0; i < z; i++)
        for (int j = 0; j < z; j++)
            if (mark[x + i][y + j])
                return 0;
    return 1;
}

int work()
{
    int x, y;
    auto f = [&](){
        for (x = 0; x < s; x++)
            for (y = 0; y < s; y++)
                if (!mark[x][y])
                    return;
    };
    f();
    if (x == s && y == s)
        return 1;
    for (int i = 1; i <= 10; i++)
        if (a[i] && judge(x, y, i))
        {
            a[i]--;
            auto f = [&](int l, int v){
                for (int i = 0; i < l; i++)
                    for (int j = 0; j < l; j++)
                        mark[x + i][y + j] = v;
            };
            f(i, 1);
            if (work())
                return 1;
            f(i, 0);
            a[i]++;
        }
    return 0;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &s, &n);
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++)
        {
            int x;
            scanf("%d", &x);
            a[x]++;
        }
        memset(mark, 0, sizeof(mark));
        if (work())
            printf("YES\n");
        else
            printf("NO\n");
    }
}