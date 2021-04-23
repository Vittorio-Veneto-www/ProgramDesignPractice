#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

int primeFactor(int x)
{
    int factor, cnt = 0, sq = sqrt(x);
    for (factor = 2; x != 1 && factor <= sq; factor++)
        if (!(x % factor))
        {
            cnt ++;
            while (!(x % factor))
                x /= factor;
        }
    if (x != 1 && cnt)
        cnt++;
    return cnt;
}

typedef struct{
    int operator()(const int &a, const int &b)
    {
        int x = primeFactor(a), y = primeFactor(b);
        return (x < y) || (x == y && a < b);
    }
} comp1;

typedef struct{
    int operator()(const int &a, const int &b)
    {
        int x = primeFactor(a), y = primeFactor(b);
        return (x > y) || (x == y && a > b);
    }
} comp2;

int main(void)
{
    std::priority_queue<int, std::vector<int>, comp1> queueMax;
    std::priority_queue<int, std::vector<int>, comp2> queueMin;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x;
        for (int i = 0; i < 10; i++)
        {
            scanf("%d", &x);
            queueMax.push(x);
            queueMin.push(x);
        }
        printf("%d %d\n", queueMax.top(), queueMin.top());
        queueMax.pop();
        queueMin.pop();
    }
}