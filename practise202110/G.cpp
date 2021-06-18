#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, a[18], cnt, b[18], min;

void work(int t)
{
    if (cnt >= min)
        return;
    if (t == n)
    {
        min = cnt;
        return;
    }
    for (int i = 0; i < cnt; i++)
        if (m - b[i] >= a[t])
        {
            b[i] += a[t];
            work(t + 1);
            b[i] -= a[t];
        }
    b[cnt++] = a[t];
    work(t + 1);
    cnt--;
}

int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    cnt = 0;
    min = 100;
    memset(b, 0, sizeof(b));
    work(0);
    printf("%d\n", min);
}