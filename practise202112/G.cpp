#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
    int n, m, node[1000], edge[4000], next[4000];
    while (scanf("%d%d", &n, &m) != EOF)
    {
        memset(node, 0xff, sizeof(node));
        int x, y;
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            edge[i] = y;
            next[i] = node[x];
            node[x] = i;
        }
        int q[1000], mark[1000], mark1 = 1;
        for (int i = 0; i < n; i++)
        {
            memset(mark, 0, sizeof(mark));
            q[0] = i;
            mark[i] = 0;
            int h = -1, t = 0;
            while (h < t)
            {
                h++;
                int x = q[h], val = node[x];
                while (val != -1)
                {
                    if (!mark[edge[val]])
                    {
                        mark[edge[val]] = 1;
                        t++;
                        q[t] = edge[val];
                    }
                    val = next[val];
                }
            }
            if (mark[i])
            {
                mark1 = 0;
                break;
            }
        }
        if (mark1)
            printf("True\n");
        else
            printf("False\n");
    }
}