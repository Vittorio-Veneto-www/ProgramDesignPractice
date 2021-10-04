#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int n, m, a[15][100];
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &a[i][j]);
		int max = 0;
		for (int i = 0; i < 1 << n; i++)
		{
			int cnt = 0;
			for (int j = 0; j < m; j++)
			{
				int x[2];
				x[0] = 0, x[1] = 0;
				for (int k = 0; k < n; k++)
					x[a[k][j] ^ (i >> k & 1)]++;
				cnt += std::max(x[0], x[1]);
			}
			max = std::max(max, cnt);
		}
		printf("%d\n", max);
	}
}