#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <list>
#include <set>
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
    set<int> a;
    multiset<int> b;
    int n;
    string indicator;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> indicator;
        if (indicator == "add")
        {
            int num;
            scanf("%d", &num);
            a.insert(num);
            b.insert(num);
            printf("%d\n", b.count(num));
            continue;
        }
        if (indicator == "del")
        {
            int num;
            scanf("%d", &num);
            printf("%d\n", b.count(num));
            b.erase(num);
            continue;
        }
        if (indicator == "ask")
        {
            int num;
            scanf("%d", &num);
            printf("%d %d\n", a.count(num), b.count(num));
            continue;
        }
    }
}