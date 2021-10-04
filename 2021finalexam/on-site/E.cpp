#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int n;
	long long a[18][11], f[18][3];
	scanf("%d", &n);
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &a[i][0]);
		for (int j = 1; j <= a[i][0]; j++)
			scanf("%lld", &a[i][j]);
	}
	for (int j = 1; j <= a[0][0]; j++)
		f[0][a[0][j] % 3]++;
	for (int i = 1; i < n; i++)
		for (int j = 1; j <= a[i][0]; j++)
			for (int k = 0; k < 3; k++)
				f[i][(a[i][j] + k) % 3] += f[i - 1][k];
	printf("%lld\n", f[n - 1][0]);
}