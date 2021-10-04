#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int main(void)
{
	int n, k;
	double a[10000];
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%lf", &a[i]);
	int l = 1, r = 10000001;
	double max = 0;
	while (r - l > 1)
	{
		double mid = ((l + r) >> 1) / 100.0;
		int cnt = 0;
		for (int i = 0; i < n; i++)
			cnt += a[i] / mid;
		if (cnt == k)
			max = std::max(max, mid);
		if (cnt < k)
			r = ((l + r) >> 1);
		else
			l = ((l + r) >> 1);
	}
	double mid = l / 100.0;
	int cnt = 0;
	for (int i = 0; i < n; i++)
		cnt += a[i] / mid;
	if (cnt < k)
		printf("%.2lf", max);
	else
		printf("%.2lf", std::max(l / 100.0, max));
}