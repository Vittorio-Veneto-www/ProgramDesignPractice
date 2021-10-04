#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, m, cnt, trap[7][2], q[10000 * 10 * 128][5], delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char mark[100][100][10][128];
char s[100][101];

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", s[i]);
	cnt = 0;
	int x0, y0, maxn = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (s[i][j] >= '1' && s[i][j] <= '9')
				maxn = std::max(maxn, s[i][j] - '0');
			switch (s[i][j])
			{
				case 'G': trap[cnt][0] = i;trap[cnt][1] = j;cnt++;break;
				case 'S': q[0][0] = i;q[0][1] = j;break;
				case 'T': x0 = i;y0 = j;break;
			}
		}
	int h = -1, t = 0;
	q[0][2] = 0;
	q[0][3] = 0;
	q[0][4] = 0;
	mark[q[0][0]][q[0][1]][0][0] = 1;
	while (h < t)
	{
		h++;
		int x = q[h][0], y = q[h][1];
		if (s[x][y] == 'G')
		{
			int ord;
			for (ord = 0; ord < cnt; ord++)
				if (trap[ord][0] == x && trap[ord][1] == y)
					break;
			if (!(q[h][3] & 1 << ord))
			{
				t++;
				q[t][0] = x;
				q[t][1] = y;
				q[t][2] = q[h][2];
				q[t][3] = q[h][3] | 1 << ord;
				q[t][4] = q[h][4] + 1;
				mark[x][y][q[t][2]][q[t][3]] = 1;
				continue;
			}
		}
		int breakmark = 0;
		for (int i = 0; i < 4; i++)
		{
			int x1 = x + delta[i][0], y1 = y + delta[i][1], z = q[h][2];
			if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n || s[x1][y1] == 'X')
				continue;
			if (s[x1][y1] >= '1' && s[x1][y1] <= '9' && z == s[x1][y1] - '0' - 1)
				z = s[x1][y1] - '0';
			if (mark[x1][y1][z][q[h][3]])
				continue;
			t++;
			q[t][0] = x1;
			q[t][1] = y1;
			q[t][2] = z;
			q[t][3] = q[h][3];
			q[t][4] = q[h][4] + 1;
			mark[x1][y1][z][q[h][3]] = 1;
			if (x1 == x0 && y1 == y0 && q[t][2] == maxn)
			{
				breakmark = 1;
				break;
			}
		}
		if (breakmark)
			break;
	}
	printf("%d\n", q[t][4]);
}