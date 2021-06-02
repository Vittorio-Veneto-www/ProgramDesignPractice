#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

int T, n, a, b, f[1000001], p[1000001], q[1000001], mark[1000001];

int main(void)
{
    scanf("%d%d%d%d", &T, &n, &a, &b);
    memset(mark, 0, sizeof(mark));
    for (int i = 0; i < T; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        for (;x < y - 1; x++)
            mark[x + 1] = 1;
    }
    memset(f, 0xff, sizeof(f));
    f[0] = 0;
    int h = 0, t = 0, head = 0, tail = 0;
    p[t++] = 0;
    for (int i = 2; i <= n; i += 2)
    {
        if (mark[i])
            continue;
        while (h < t && i - p[h] >= a * 2)
        {
            while (head < tail && f[q[tail - 1]] >= f[p[h]])
                tail--;
            q[tail++] = p[h];
            h++;
        }
        while (head < tail && i - q[head] > b * 2)
            head++;
        if (head < tail)
        {
            
            f[i] = f[q[head]] + 1;
            p[t++] = i;
        }
    }
    printf("%d\n", f[n]);
}