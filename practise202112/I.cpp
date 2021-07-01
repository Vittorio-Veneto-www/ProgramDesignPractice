#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, node[100], edge[100][2], next[1000];
    scanf("%d", &n);
    memset(node, 0xff, sizeof(node));
    int x, y, z;
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        edge[i][0] = y - 1;
        edge[i][1] = z;
        next[i] = node[x - 1];
        node[x - 1] = i;
    }
    int q[100], mark[100], cnt[100];
    for (int i = 0; i < 100; i++)
    {
        memset(mark, 0, sizeof(mark));
        memset(cnt, 0, sizeof(cnt));
        q[0] = i;
        mark[i] = 1;
        int h = -1, t = 0;
        while (h < t)
        {
            h++;
            int x = q[h], val = node[x];
            while (val != -1)
            {
                if (!mark[edge[val][0]])
                {
                    cnt[edge[val][0]] += edge[val][1];
                    if (cnt[edge[val][0]] > 50)
                    {
                        mark[edge[val][0]] = 1;
                        t++;
                        q[t] = edge[val][0];
                    }
                }
                val = next[val];
            }
        }
        for (int j = 0; j < 100; j++)
            if (mark[j] && i != j)
                printf("%d %d\n", i + 1, j + 1);
    }
}