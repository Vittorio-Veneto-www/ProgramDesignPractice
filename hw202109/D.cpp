#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

int n;
string strs[21];

void init(string op);
string init();
int init1();

string copy()
{
    int a = init1(), b = init1(), c = init1();
    return strs[a].substr(b, c);
}
string add()
{
    string tmp1 = init(), tmp2 = init();
    int mark1 = tmp1.size() > 0 && tmp1.size() < 6, mark2 = tmp2.size() > 0 && tmp2.size() < 6;
    for (int i = 0; i < tmp1.size(); i++)
        if (tmp1[i] < '0' || tmp1[i] > '9')
            mark1 = 0;
    for (int i = 0; i < tmp2.size(); i++)
        if (tmp2[i] < '0' || tmp2[i] > '9')
            mark2 = 0;
    if (mark1 && mark2)
    {
        char tmp[100];
        sprintf(tmp, "%d", atoi(tmp1.c_str()) + atoi(tmp2.c_str()));
        string str(tmp);
        return str;
    }
    else
        return tmp1 + tmp2;
}
int find()
{
    string tmp = init();
    int a = init1();
    int b = strs[a].find(tmp);
    if (b == string::npos)
        b = strs[a].size();
    return b;
}
int rfind()
{
    string tmp = init();
    int a = init1();
    int b = strs[a].rfind(tmp);
    if (b == string::npos)
        b = strs[a].size();
    return b;
}
void insert()
{
    string tmp = init();
    int a = init1(), b = init1();
    strs[a].insert(b, tmp);
}
void reset()
{
    string tmp = init();
    int a = init1();
    strs[a] = tmp;
}
void print()
{
    int a = init1();
    std::cout << strs[a] << std::endl;
}
void printall()
{
    for (int i = 1; i <= n; i++)
        std::cout << strs[i] << std::endl;
}

void init(string op)
{
    if (op == "copy")
        std::cout << copy() << std::endl;
    else if (op == "add")
        std::cout << add() << std::endl;
    else if (op == "find")
        std::cout << find() << std::endl;
    else if (op == "rfind")
        std::cout << rfind() << std::endl;
    else if (op == "insert")
        insert();
    else if (op == "reset")
        reset();
    else if (op == "print")
        print();
    else if (op == "printall")
        printall();
}
string init()
{
    string op;
    cin >> op;
    if (op == "copy")
        return copy();
    if (op == "add")
        return add();
    return op;
}
int init1()
{
    string op;
    cin >> op;
    if (op == "find")
        return find();
    if (op == "rfind")
        return rfind();
    return atoi(op.c_str());
}

int main(void)
{
    string indicator;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        std::cin >> strs[i];
    while(1)
    {
        std::cin >> indicator;
        if (indicator == "over")
            break;
        init(indicator);
    }
}