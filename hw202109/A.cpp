#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
    typedef map<int, list<int>> MyMap;
    MyMap a;
    int n;
    string indicator;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> indicator;
        if (indicator == "new")
        {
            int id;
            scanf("%d", &id);
            a.insert(MyMap::value_type(id, list<int>()));
            continue;
        }
        if (indicator == "add")
        {
            int id, num;
            scanf("%d%d", &id, &num);
            a[id].push_back(num);
            continue;
        }
        if (indicator == "merge")
        {
            int id1, id2;
            scanf("%d%d", &id1, &id2);
            a[id1].merge(a[id2]);
            continue;
        }
        if (indicator == "unique")
        {
            int id;
            scanf("%d", &id);
            a[id].sort();
            a[id].unique();
            continue;
        }
        if (indicator == "out")
        {
            int id;
            scanf("%d", &id);
            a[id].sort();
            list<int>::iterator i;
            for (i = a[id].begin(); i != a[id].end(); i++)
                printf("%d ", *i);
            printf("\n");
            continue;
        }
    }
}