#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int n, a[1000][2];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &a[i][0], &a[i][1]);
	int max = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			int x = i, y = j;
			if (a[i][0] > a[j][0])
				std::swap(x, y);
			if (a[x][1] > a[y][1])
				max = std::max(max, a[y][1] - a[y][0] + 1);
			else
				max = std::max(max, a[x][1] - a[y][0] + 1);
		}
	printf("%d\n", max);
}