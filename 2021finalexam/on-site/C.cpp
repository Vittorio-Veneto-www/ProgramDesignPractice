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
		int n, k, a[100][2], f[100];
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i][0]);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i][1]);
		memset(f, 0, sizeof(f));
		int max = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
				if (a[i][0] - a[j][0] > k)
					f[i] = std::max(f[i], f[j]);
			f[i] += a[i][1];
			max = std::max(max, f[i]);
		}
		printf("%d\n", max);
	}
}