#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iostream>

int main(void)
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::map<std::string, std::set<std::string> > computer;
        std::map<std::string, std::vector<std::string> > backpack;
        while (n--)
        {
            std::string indicator, trainer, pokemon;
            std::cin >> indicator >> trainer >> pokemon;
            if (indicator == "C")
            {
                if (backpack[trainer].size() == 6)
                {
                    computer[trainer].insert(backpack[trainer][0]);
                    backpack[trainer].erase(backpack[trainer].begin());
                }
                backpack[trainer].push_back(pokemon);
            }
            else
            {
                if (computer.find(trainer) == computer.end())
                {
                    printf("Failed\n");
                    continue;
                }
                auto it = computer[trainer].find(pokemon);
                if (it == computer[trainer].end())
                    printf("Failed\n");
                else
                {
                    printf("Success\n");
                    computer[trainer].erase(it);
                    computer[trainer].insert(backpack[trainer][0]);
                    backpack[trainer].erase(backpack[trainer].begin());
                    backpack[trainer].push_back(pokemon);
                }
            }
        }
    }
}