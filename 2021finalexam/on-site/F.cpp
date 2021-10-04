#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int n, m, node[1000], edge[4000][2], next[4000], mark[1000][2], cnt[1000], q[1001];
	scanf("%d%d", &n, &m);
	memset(node, 0xff, sizeof(node));
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x--;
		y--;
		edge[i][0] = y;
		edge[i][1] = z;
		next[i] = node[x];
		node[x] = i;
	}
	int h = -1, t = 0;
	q[0] = 0;
	memset(mark, 0, sizeof(mark));
	mark[0][0] = 1;
	memset(cnt, 0, sizeof(cnt));
	while (h != t)
	{
		h = (h + 1) % 1001;
		int x = q[h], val = node[x];
		mark[x][0] = 0;
		while (val != -1)
		{
			if (mark[x][1] + edge[val][1] > mark[edge[val][0]][1])
			{
				mark[edge[val][0]][1] = mark[x][1] + edge[val][1];
				if (!mark[edge[val][0]][0])
				{
					mark[edge[val][0]][0] = 1;
					t = (t + 1) % 1001;
					q[t] = edge[val][0];
					cnt[edge[val][0]]++;
					if (cnt[edge[val][0]] > n)
					{
						printf("1000000000\n");
						return 0;
					}
				}
			}
			val = next[val];
		}
	}
	int max = 0;
	for (int i = 0; i < n; i++)
		max = std::max(max, mark[i][1]);
	printf("%d\n", max);
}