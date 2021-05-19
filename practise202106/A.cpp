#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

int judge(int x)
{
    for (int i = 2; i * i <= x; i++)
        if (!(x % i))
            return 0;
    std::vector<int> v;
    while (x)
    {
        v.push_back(x % 10);
        x /= 10;
    }
    for (auto i: v)
        x = x * 10 + i;
    for (int i = 2; i * i <= x; i++)
        if (!(x % i))
            return 0;
    return 1;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> v;
    for (int i = n; i <= m; i++)
    {
        if (judge(i))
            v.push_back(i);
    }
    if (v.size())
    {
        int mark = 0;
        for (auto i: v)
        {
            if (mark)
                printf(",");
            mark = 1;
            printf("%d", i);
        }
    }
    else
        printf("No\n");
}