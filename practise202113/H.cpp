#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>

int n, m, a[1000][1000], q[1000000][2], mark[1000][1000], delta[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
char s[1000][1001];

int main(void)
{
    int T, T1 = 0;
    scanf("%d", &T);
    while (T1 < T)
    {
        T1++;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", s[i]);
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                a[i][j] = s[i][j] - '0';
                if (a[i][j])
                    mark[i][j] = 1;
            }
        int max = 0;
        auto func = [&](int x, int y){
            q[0][0] = x;
            q[0][1] = y;
            mark[x][y] = 1;
            int h = -1, t = 0;
            while (h < t)
            {
                h++;
                int x = q[h][0], y = q[h][1];
                for (int i = 0; i < 8; i++)
                {
                    int x1 = x + delta[i][0], y1 = y + delta[i][1];
                    if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= m || mark[x1][y1] || a[x1][y1])
                        continue;
                    mark[x1][y1] = 1;
                    t++;
                    q[t][0] = x1;
                    q[t][1] = y1;
                }
            }
            std::set<std::pair<int, int> > points;
            for (int i = 0; i <= t; i++)
            {
                if (q[i][0] == 0 || q[i][1] == 0 || q[i][0] == n - 1 || q[i][1] == m - 1)
                    return;
                for (int j = 0; j < 8; j++)
                {
                    int x1 = q[i][0] + delta[j][0], y1 = q[i][1] + delta[j][1];
                    if (a[x1][y1])
                        points.insert(std::make_pair(x1, y1));
                }
            }
            for (auto &&i: points)
            {
                int cnt = 0;
                cnt += points.find(std::make_pair(i.first + 1, i.second)) != points.end();
                cnt += points.find(std::make_pair(i.first - 1, i.second)) != points.end();
                cnt += points.find(std::make_pair(i.first, i.second + 1)) != points.end();
                cnt += points.find(std::make_pair(i.first, i.second - 1)) != points.end();
                if (cnt != 2)
                    return;
            }
            int length = points.size();
            auto i = points.begin(), j = points.begin();
            while (1)
            {
                j = points.find(std::make_pair(i->first + 1, i->second));
                if (j != points.end())
                {
                    points.erase(i);
                    i = j;
                    continue;
                }
                j = points.find(std::make_pair(i->first - 1, i->second));
                if (j != points.end())
                {
                    points.erase(i);
                    i = j;
                    continue;
                }
                j = points.find(std::make_pair(i->first, i->second + 1));
                if (j != points.end())
                {
                    points.erase(i);
                    i = j;
                    continue;
                }
                j = points.find(std::make_pair(i->first, i->second - 1));
                if (j != points.end())
                {
                    points.erase(i);
                    i = j;
                    continue;
                }
                if (points.size() == 1)
                    max = std::max(max, length);
                break;
            }
        };
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!mark[i][j])
                    func(i, j);
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < m - 1; j++)
                if (a[i][j] && a[i + 1][j] && a[i][j + 1] && a[i + 1][j + 1])
                    max = std::max(max, 4);
        printf("%d\n", max);
    }
}