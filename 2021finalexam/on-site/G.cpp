#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int n, a[300][300], mark[300][300][2], q[90001][2], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	scanf("%d", &n);
	memset(mark, 0x7f, sizeof(mark));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]), mark[i][j][0] = 0;
	int h = -1, t = 0;
	q[0][0] = 0;
	q[0][1] = 0;
	mark[0][0][0] = 1;
	mark[0][0][1] = a[0][0];
	while (h != t)
	{
		h = (h + 1) % 90001;
		int x = q[h][0], y = q[h][1];
		mark[x][y][0] = 0;
		for (int i = 0; i < 4; i++)
		{
			int x1 = x + delta[i][0], y1 = y + delta[i][1];
			if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n)
				continue;
			if (std::max(mark[x][y][1], a[x1][y1]) < mark[x1][y1][1])
			{
				mark[x1][y1][1] = std::max(mark[x][y][1], a[x1][y1]);
				if (!mark[x1][y1][0])
				{
					mark[x1][y1][0] = 1;
					t = (t + 1) % 90001;
					q[t][0] = x1;
					q[t][1] = y1;
				}
			}
		}
	}
	printf("%d\n", mark[n - 1][n - 1][1]);
}