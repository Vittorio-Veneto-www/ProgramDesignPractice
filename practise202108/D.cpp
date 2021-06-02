#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

double work(void)
{
    char str[100];
    scanf("%s", str);
    if (strlen(str) == 1)
        switch (str[0])
        {
            case '+': return work() + work();
            case '-': return work() - work();
            case '*': return work() * work();
            case '/': return work() / work();
            default: return 0;
        }
    else
        return atof(str);
}

int main(void)
{
    printf("%lf", work());
}