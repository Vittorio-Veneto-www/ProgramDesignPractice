#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

#define maxNameLen 10
#define maxWarriors 1000
#define maxWeapons 10
#define HQType 2
#define warriorType 5
#define weaponType 3

class commonProperties
{
    protected:
        int type;
        const char *name;
    public:
        commonProperties(const int type, const char name[][maxNameLen + 1]):
            type(type),
            name(name[type])
        {}

        ~commonProperties() {}

        int getType()
        {
            return type;
        }

        const char * getName()
        {
            return name;
        }
};

class weapon:public commonProperties
{
    protected:
        static constexpr char typeName[weaponType][maxNameLen + 1] = {"sword", "bomb", "arrow"};
        int attack;
    public:
        weapon(const int type, const int attack = 0):
            attack(attack),
            commonProperties(type, typeName)
        {}

        virtual ~weapon() {}
};

class warrior:public commonProperties
{
    protected:
        static constexpr char typeName[warriorType][maxNameLen + 1] = {"dragon", "ninja", "iceman", "lion", "wolf"};
        int id, strength, loyalty = -1, weaponCount = 0;
        double morale = -1;
        weapon *currentWeapon, *weapons[maxWeapons];
    public:
        warrior(const int type, const int id, const int strength, const int HQStrength):
            id(id),
            strength(strength),
            commonProperties(type, typeName)
        {
            switch (getType())
            {
                case 0:
                    currentWeapon = new weapon(id % 3);
                    weapons[weaponCount++] = currentWeapon;
                    morale = (double)HQStrength / strength;
                    break;
                case 1:
                    currentWeapon = new weapon(id % 3);
                    weapons[weaponCount++] = currentWeapon;
                    currentWeapon = new weapon((id + 1) % 3);
                    weapons[weaponCount++] = currentWeapon;
                    break;
                case 2:
                    currentWeapon = new weapon(id % 3);
                    weapons[weaponCount++] = currentWeapon;
                    break;
                case 3:
                    loyalty = HQStrength;
                    break;
                case 4:
                    break;
            }
        }

        virtual void printStatus()
        {
            int mark = 0;
            if (weaponCount)
            {
                if (mark)
                    printf(",and it");
                else
                    printf("It"), mark = 1;
                printf(" has a %s", weapons[0]->getName());
                for (int i = 1; i < weaponCount; i++)
                    printf(" and a %s", weapons[i]->getName());
            }
            if (morale != -1)
            {
                if (mark)
                    printf(",and it");
                else
                    printf("It"), mark = 1;
                printf("'s morale is %.2lf", morale);
            }
            if (loyalty != -1)
            {
                if (mark)
                    printf(",and it");
                else
                    printf("It"), mark = 1;
                printf("'s loyalty is %d", loyalty);
            }
            if (mark)
                printf("\n");
        }

        virtual ~warrior()
        {
            for (int i = 0; i < weaponCount; i++)
                delete weapons[i];
        }

        int getId()
        {
            return id;
        }

        int getStrength()
        {
            return strength;
        }

        int getLoyalty()
        {
            return loyalty;
        }

        double getMorale()
        {
            return morale;
        }
};

class HQ:public commonProperties
{
    protected:
        static constexpr char typeName[HQType][maxNameLen + 1] = {"red", "blue"};
        static constexpr int warriorTypeMap[HQType][warriorType] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
        int stop = 0, strength, warriorCount = 0, currentWarriorType = 0, warriorTypeCount[warriorType] = {0};
        warrior *currentWarrior, *warriors[maxWarriors];
    public:
        static int typeStrength[warriorType];
        HQ(int type, int strength):
            strength(strength),
            commonProperties(type, typeName)
        {}

        virtual ~HQ()
        {
            for (int i = 0; i < warriorCount; i++)
                delete warriors[i];
        }

        int produce()
        {
            if (stop)
                return 0;
            for (int i = 0; i < warriorType; i++)
                if (strength >= typeStrength[mapWarriorType((currentWarriorType + i) % 5)])
                {
                    currentWarriorType = (currentWarriorType + i) % 5;
                    int mappedWarriorType = mapWarriorType(currentWarriorType);
                    strength -= typeStrength[mappedWarriorType];
                    currentWarrior = new warrior(mappedWarriorType, warriorCount + 1, typeStrength[mappedWarriorType], strength);
                    warriors[warriorCount] = currentWarrior;
                    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", warriorCount, getName(), currentWarrior->getName(), currentWarrior->getId(), currentWarrior->getStrength(), ++warriorTypeCount[mappedWarriorType], currentWarrior->getName(), getName());
                    currentWarrior->printStatus();
                    currentWarriorType = (currentWarriorType + 1) % 5;
                    warriorCount++;
                    return 1;
                }
            printf("%03d %s headquarter stops making warriors\n", warriorCount, getName());
            stop = 1;
            return 0;
        }

        int mapWarriorType(int currentWarriorType)
        {
            return warriorTypeMap[getType()][currentWarriorType];
        }
};

constexpr char weapon::typeName[weaponType][maxNameLen + 1];
constexpr char warrior::typeName[warriorType][maxNameLen + 1];
constexpr char HQ::typeName[HQType][maxNameLen + 1];
constexpr int HQ::warriorTypeMap[HQType][warriorType];
int HQ::typeStrength[warriorType];

int main()
{
	int n, x, a[5];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Case:%d\n", i + 1);
        scanf("%d", &x);
        for (int j = 0; j < 5; j++)
            scanf("%d", &HQ::typeStrength[j]);
        HQ x1(0, x), x2(1, x);
        while (x1.produce() + x2.produce());
    }
}