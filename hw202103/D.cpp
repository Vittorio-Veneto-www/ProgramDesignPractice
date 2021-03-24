#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

class HQ
{
    int stop = 0, soliderCount = 0, currentType = 0, currentHP, typeHP[5], typeCount[5], typeMap[5];
    char typeName[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"}, selfName[10];
    public:
        HQ(int type, int HP, int *a)
        {
            if (type == 0)
            {
                typeMap[0] = 2;
                typeMap[1] = 3;
                typeMap[2] = 4;
                typeMap[3] = 1;
                typeMap[4] = 0;
                strcpy(selfName, "red");
            }
            else
            {
                typeMap[0] = 3;
                typeMap[1] = 0;
                typeMap[2] = 1;
                typeMap[3] = 2;
                typeMap[4] = 4;
                strcpy(selfName, "blue");
            }
            for (int i = 0; i < 5; i++)
                typeHP[i] = a[typeMap[i]], typeCount[i] = 0;
            currentHP = HP;
        }

        int produce()
        {
            if (stop)
                return 0;
            for (int i = 0; i < 5; i++)
                if (currentHP >= typeHP[(currentType + i) % 5])
                {
                    currentHP -= typeHP[(currentType + i) % 5];
                    soliderCount++;
                    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", soliderCount - 1, selfName, typeName[typeMap[(currentType + i) % 5]], soliderCount, typeHP[(currentType + i) % 5], ++typeCount[(currentType + i) % 5], typeName[typeMap[(currentType + i) % 5]], selfName);
                    currentType = (currentType + i + 1) % 5;
                    return 1;
                }
            printf("%03d %s headquarter stops making warriors\n", soliderCount++, selfName);
            stop = 1;
            return 0;
        }
};

int main()
{
	int i, n, x, a[5];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Case:%d\n", i + 1);
        scanf("%d%d%d%d%d%d", &x, &a[0], &a[1], &a[2], &a[3], &a[4]);
        HQ x1(0, x, a), x2(1, x, a);
        while (x1.produce() + x2.produce());
    }
}