#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        std::map<int, int> map[100];
        std::set<int> v;
        for (int i = 0; i < n; i++)
        {
            int m, x, y;
            std::map<int, int> map1;
            scanf("%d", &m);
            for (int j = 0; j < m; j++)
            {
                scanf("%d%d", &x, &y), v.insert(x);
                if (map1.find(x) != map1.end())
                    map1[x] = std::min(map1[x], y);
                else
                    map1[x] = y;
            }
            int min = (--map1.end())->second;
            for (auto j = map1.end(); j != map1.begin(); j--)
            {
                auto k = j;
                k--;
                min = std::min(min, k->second);
                map[i][k->first] = min;
            }
        }
        double max = 0;
        for (auto i: v)
        {
            int cost = 0;
            for (int j = 0; j < n; j++)
            {
                auto it = map[j].lower_bound(i);
                if (it == map[j].end())
                {
                    cost = -1;
                    break;
                }
                else
                    cost += it->second;
            }
            if (cost == -1)
                break;
            max = std::max(max, (double)i / cost);
        }
        printf("%.3lf\n", max);
    }
}