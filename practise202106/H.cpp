#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

typedef struct point
{
    int x, y;
    int operator<(const point &a) const
    {
        return (x < a.x) || (x == a.x && y < a.y);
    }
} point;

point points[5000];
int n, m, cnt, max, mark[5000];

int find(int x, int y)
{
    point p;
    p.x = x;
    p.y = y;
    int l = 0, r = cnt, mid = (l + r) >> 1;
    while (l != mid)
    {
        if (p < points[mid])
            r = mid;
        else
            l = mid;
        mid = (l + r) >> 1;
    }
    if (points[l].x == x && points[l].y == y)
        return l;
    else
        return -1;
}

int work(int a, int b)
{
    if (mark[b])
        return 0;
    int dx = points[b].x - points[a].x, dy = points[b].y - points[a].y;
    int x = dx * std::max(max, 1) + points[b].x, y = dy * std::max(max, 1) + points[b].y;
    if (x <= 0 || x > n || y <= 0 || y > m)
        return 0;
    int step = 0;
    x = dx + points[b].x, y = dy + points[b].y;
    int ord = find(x, y);
    while (ord != -1)
    {
        step++;
        mark[ord] = 1;
        x += dx, y += dy;
        ord = find(x, y);
    }
    int x1 = points[a].x - dx, y1 = points[a].y - dy;
    if ((x <= 0 || x > n || y <= 0 || y > m) && (x1 <= 0 || x1 > n || y1 <= 0 || y1 > m))//路径起始点的上一跳与终点的下一跳必须在稻田外
        return step;
    else
        return 0;
}

int main()
{
    scanf("%d%d%d", &n, &m, &cnt);
    for (int i = 0; i < cnt; i++)
        scanf("%d%d", &points[i].x, &points[i].y);
    std::sort(points, points + cnt);
    max = 0;
    for (int i = 0; i < cnt; i++)
    {
        memset(mark, 0, sizeof(mark));
        for (int j = i + 1; j < cnt; j++)
            max = std::max(max, work(i, j));
    }
    if (max)
        printf("%d\n", max + 2);
    else
        printf("0\n");
}