#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>

int main(void)
{
    int n;
    scanf("%d", &n);
    while (n)
    {
        int a[1000], b[1000];
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &b[i]);
        std::sort(a, a + n);
        std::sort(b, b + n);
        int h = 0, t = n - 1, h1 = 0, t1 = n - 1, sum = 0;
        while (h <= t)
        {
            if (a[h] > b[h1])
            {
                sum += 200;
                h++;
                h1++;
            }
            else
                if (a[h] < b[h1])
                {
                    sum -= 200;
                    h++;
                    t1--;
                }
                else
                    if (a[t] > b[t1])
                    {
                        sum += 200;
                        t--;
                        t1--;
                    }
                    else
                        if (a[h] < b[t1])
                        {
                            sum -= 200;
                            h++;
                            t1--;
                        }
                        else
                            break;
        }
        printf("%d\n", sum);
        scanf("%d", &n);
    }
}