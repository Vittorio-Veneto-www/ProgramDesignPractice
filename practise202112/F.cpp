#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef struct{
    int v, w;
} item;

int cmp(const item &a, const item &b)
{
    return a.v > b.v;
}

item a[10000];
int f[3][10001];

int main(void)
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &a[i].v, &a[i].w);
    std::sort(a, a + n, cmp);
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; i++)
    {
        for (int j = m; j >= a[i].w; j--)
            f[i % 3][j] = std::max(f[(i + 2) % 3][j], f[(i + 1) % 3][j - a[i].w] + a[i].v);
        for (int j = a[i].w - 1; j >= 0; j--)
            f[i % 3][j] = f[(i + 2) % 3][j];
    }
    printf("%d\n", f[(n - 1) % 3][m]);
}