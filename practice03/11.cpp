#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

class Patient
{
    public:
        int rank, id;
        static int cnt;
        Patient(int rank):rank(rank), id(++cnt){}
        int operator<(const Patient &x) const
        {
            return (rank < x.rank) || (rank == x.rank && id > x.id);
        }
};

int Patient::cnt;

int main(void)
{
    int cnt;
    scanf("%d", &cnt);
    while (cnt--)
    {
        int cnt;
        scanf("%d", &cnt);
        std::priority_queue<Patient> q[3];
        Patient::cnt = 0;
        char tmp[10];
        while (cnt--)
        {
            scanf("%s", tmp);
            if (tmp[0] == 'I')
            {
                int x, y;
                scanf("%d%d", &x, &y);
                q[x - 1].push(y);
            }
            else
            {
                int x;
                scanf("%d", &x);
                if (q[x - 1].size())
                {
                    printf("%d\n", q[x - 1].top().id);
                    q[x - 1].pop();
                }
                else
                    printf("EMPTY\n");
            }
        }
    }
}