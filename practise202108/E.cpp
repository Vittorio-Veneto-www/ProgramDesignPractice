#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int main(void)
{
    char str[101];
    while (scanf("%s", str) != EOF)
    {
        int a[100], s[100], t = 0, n = strlen(str), cnt = 0;
        for (int i = 0; i < n; i++)
            switch (str[i])
            {
                case '(':
                    s[t++] = i;break;
                case ')':
                    if (t)
                        t--;
                    else
                        a[cnt++] = i;
            }
        while (t)
            a[cnt++] = s[--t];
        char result[101] = {0};
        memset(result, ' ', n);
        for (int i = 0; i < cnt; i++)
            if (str[a[i]] == '(')
                result[a[i]] = '$';
            else
                result[a[i]] = '?';
        printf("%s\n%s\n", str, result);
    }
}