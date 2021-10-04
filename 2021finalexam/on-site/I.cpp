#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

char s[9][10];
int a[9][9], mark[9][9];

int work(int x, int y)
{
	if (x == 8 && y == 9)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				printf("%d", a[i][j]);
			printf("\n");
		}
		return 1;
	}
	if (y == 9)
	{
		x++;
		y = 0;
	}
	if (!a[x][y])
	{
		int mark[10];
		memset(mark, 0, sizeof(mark));
		for (int i = 0; i < 9; i++)
			mark[a[x][i]] = 1, mark[a[i][y]] = 1;
		int c1 = x / 3, c2 = y / 3;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mark[a[c1 * 3 + i][c2 * 3 + j]] = 1;
		for (int i = 1; i <= 9; i++)
			if (!mark[i])
			{
				a[x][y] = i;
				if (work(x, y + 1))
					return 1;
			}
		a[x][y] = 0;
		return 0;
	}
	work(x, y + 1);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		for (int i = 0; i < 9; i++)
			scanf("%s", s[i]);
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				a[i][j] = s[i][j] - '0';
		work(0, 0);
	}
}