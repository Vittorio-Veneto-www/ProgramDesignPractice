#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int mark;

void work(int n, int* a)
{
    if (n == 1)
    {
        if (a[0] == 42)
            mark = 1;
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
            {
                int b[6], m = 0;
                for (int k = 0; k < n; k++)
                    if (k != i && k != j)
                        b[m++] = a[k];
                if (i < j)
                {
                    b[m] = a[i] + a[j];
                    work(n - 1, b);
                    b[m] = a[i] * a[j];
                    work(n - 1, b);
                }
                b[m] = a[i] - a[j];
                work(n - 1, b);
                if (a[j] != 0)
                {
                    b[m] = a[i] / a[j];
                    work(n - 1, b);
                }
            }
}

int main(void)
{
    int n, a[6];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    mark = 0;
    work(n, a);
    printf("%s", mark ? "YES" : "NO");
}