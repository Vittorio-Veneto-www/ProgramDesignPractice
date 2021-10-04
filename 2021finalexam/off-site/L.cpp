#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>

char s[13];

int main(void)
{
    int n, m;
	scanf("%d%d", &n, &m);
	memset(s, '0', sizeof(s));
	s[n] = 0;
	for (int i = pow(m, n - 1); i; i--)
	{
		for (int i = 0; i < m - 1; i++)
		{
			printf("%s\n", s);
			s[0] = (s[0] - '0' + 1) % m + '0';
		}
		printf("%s\n", s);
		for (int i = 0; i < n; i++)
			if (s[i] != '0')
			{
				s[i + 1] = (s[i + 1] - '0' + 1) % m + '0';
				break;
			}
	}
}