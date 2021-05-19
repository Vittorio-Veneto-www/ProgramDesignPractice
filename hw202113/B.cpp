#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <string>

typedef std::multiset<std::string> folderfile;
typedef std::vector<int> subfolder;

std::vector<std::multiset<std::string> > folderfiles;
std::vector<std::string> foldernames;
std::vector<int> parentfolders;
std::vector<std::vector<int> > subfolders;

void levelprint(std::string &str, int level)
{
    for (int i = 0; i < level; i++)
        std::cout << "|     ";
    std::cout << str << std::endl;
}

void print(int x, int level)
{
    levelprint(foldernames[x], level);
    for (auto i: subfolders[x])
        print(i, level + 1);
    for (auto i: folderfiles[x])
        levelprint(i, level);
}

int main(void)
{
    std::string str;
    for (int t = 1;;t++)
    {
        std::cin >> str;
        if (str == "#")
            break;
        folderfiles.clear();
        foldernames.clear();
        parentfolders.clear();
        subfolders.clear();
        folderfiles.push_back(folderfile());
        foldernames.push_back("ROOT");
        parentfolders.push_back(-1);
        subfolders.push_back(subfolder());
        int currentfolder = 0;
        while (str != "*")
        {
            switch (str[0])
            {
                case 'f':
                    folderfiles[currentfolder].insert(str);
                    break;
                case 'd':
                    folderfiles.push_back(folderfile());
                    foldernames.push_back(str);
                    parentfolders.push_back(currentfolder);
                    subfolders.push_back(subfolder());
                    subfolders[currentfolder].push_back(folderfiles.size() - 1);
                    currentfolder = folderfiles.size() - 1;
                    break;
                case ']':
                    currentfolder = parentfolders[currentfolder];
                    break;
            }
            std::cin >> str;
        }
        std::cout << "DATA SET " << t << ":" << std::endl;
        print(0, 0);
        std::cout << std::endl;
    }
}