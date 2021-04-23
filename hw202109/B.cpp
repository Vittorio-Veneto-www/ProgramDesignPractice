#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <stack>
#include <iostream>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
    multiset<double> a;
    stack<double> expr;
    double tmp;
    string buffer;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        a.insert(tmp);
    }
    while (cin >> buffer)
    {
        if (buffer == "+" || buffer == "-" || buffer == "*" || buffer == "/" || buffer == "^")
        {
            double x, y;
            x = expr.top();
            expr.pop();
            y = expr.top();
            expr.pop();
            switch(buffer[0])
            {
                case '+':expr.push(y + x);break;
                case '-':expr.push(y - x);break;
                case '*':expr.push(y * x);break;
                case '/':expr.push(y / x);break;
                case '^':expr.push(pow(y, x));break;
            }
        }
        else
            if (buffer[0] == '=')
            {
                tmp = expr.top();
                expr.pop();
                printf("%e\n", tmp);
                a.erase(a.begin());
                a.insert(tmp);
            }
            else
            {
                expr.push(atof(buffer.c_str()));
            }
    }
    printf("\n");
    int cnt = 0;
    for (multiset<double>::iterator i = a.begin(); i != a.end(); i++)
    {
        cnt++;
        if (cnt % 10)
            printf("%e ", *i);
        else
            printf("%e\n", *i);
    }
}