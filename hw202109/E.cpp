#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>

int main(void)
{
    std::multimap<int, int> map;
    map.insert(std::make_pair(1000000000, 1));
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int id, strength;
        scanf("%d%d", &id, &strength);
        std::map<int, int>::iterator it = map.lower_bound(strength), _it = map.upper_bound(strength);
        if (it != map.begin())
            it--;
        it = map.lower_bound(it->first);
        if (_it != map.end())
            _it = map.upper_bound(_it->first);
        int id_new = -1, min;
        for (;it != _it; it++)
            if (id_new == -1)
                id_new = it->second, min = abs(strength - it->first);
            else
                if (abs(strength - it->first) < min)
                    id_new = it->second, min = abs(strength - it->first);
        map.insert(std::make_pair(strength, id));
        printf("%d %d\n", id, id_new);
    }
}