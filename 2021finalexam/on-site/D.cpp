#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n;
char s[21];

void work(int x, int y)
{
	if (x == n && y == n)
	{
		printf("%s\n", s);
		return;
	}
	if (x < n)
	{
		s[x + y] = '(';
		work(x + 1, y);
	}
	if (y < x)
	{
		s[x + y] = ')';
		work(x, y + 1);
	}
}

int main(void)
{
	scanf("%d", &n);
	s[n * 2] = 0;
	work(0, 0);
}