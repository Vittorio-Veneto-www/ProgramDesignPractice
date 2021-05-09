#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

int main(void)
{
	int n, m;
	scanf("%d%d", &n, &m);
	std::map<std::string, int> price, num;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		std::string name;
		std::cin >> name;
		scanf("%d%d", &x, &y);
		price.insert(std::make_pair(name, x));
		num.insert(std::make_pair(name, y));
	}
	int cash = 0;
	for (int i = 0; i < n; i++)
	{
		std::string name[3];
		std::cin >> name[0] >> name[1] >> name[2];
		for (int i = 0; i < 3; i++)
			if (num[name[i]])
			{
				cash += price[name[i]];
				num[name[i]]--;
			}
	}
	printf("%d", cash);
}
