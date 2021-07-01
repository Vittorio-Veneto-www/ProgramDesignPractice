#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<int> a[10001];
std::priority_queue<int, std::vector<int>, std::less<int> > q;

int main(void)
{
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &x, &y), a[y].push_back(x);
    int score = 0;
    for (int i = 10000; i; i--)
    {
        for (int score: a[i])
            q.push(score);
        if (!q.empty())
        {
            score += q.top();
            q.pop();
        }
    }
    printf("%d\n", score);
}