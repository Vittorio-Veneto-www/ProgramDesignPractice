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

int k, n, hour;
//constexpr char typeName[HQType][maxNameLen + 1] = {"red", "blue"};

class commonProperties
{
    protected:
        const int type;
        const char *name;
    public:
        commonProperties(const int type, const char name[maxNameLen + 1]):
            type(type),
            name(name)
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

class weapon;
class warrior;
class HQ;



class weapon:public commonProperties
{
    public:
        int timeUsed;
    public:
        weapon(const int type, const char *typeName):
            timeUsed(0),
            commonProperties(type, typeName)
        {}

        virtual ~weapon() {}
        virtual void attack(warrior *attacker, warrior *defender) {}
        virtual int isDestroyed() = 0;
        friend int cmp1(weapon *x, weapon *y);
        friend int cmp2(weapon *x, weapon *y);
};

class sword:public weapon
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "sword";
    public:
        sword();
        void attack(warrior *attacker, warrior *defender);
        int isDestroyed();
};

class bomb:public weapon
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "bomb";
    public:
        bomb();
        void attack(warrior *attacker, warrior *defender);
        int isDestroyed();
};

class arrow:public weapon
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "arrow";
    public:
        arrow();
        void attack(warrior *attacker, warrior *defender);
        int isDestroyed();
};

int cmp1(weapon *x, weapon *y)
{
    return (x->type < y->type) || (x->type == y->type && x->timeUsed > y->timeUsed);
}

int cmp2(weapon *x, weapon *y)
{
    return (x->type < y->type) || (x->type == y->type && x->timeUsed < y->timeUsed);
}

class HQ:public commonProperties
{
    public:
        static constexpr char typeName[HQType][maxNameLen + 1] = {"red", "blue"};
        static constexpr int warriorTypeMap[HQType][warriorType] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
        int stop = 0, element, warriorCount = 0, currentWarriorType = -1, warriorTypeCount[warriorType] = {0};
        warrior *currentWarrior, *warriors[maxWarriors];
    public:
        HQ(int type, int element);
        virtual ~HQ();
        void produce();
        int mapWarriorType(int currentWarriorType);
};

class warrior:public commonProperties
{
    public:
        int location, id, element, force, loyalty = -1, weaponCount = 0;
        char info[100];
        weapon *currentWeapon, *weapons[maxWeapons];
        HQ *belong;
    public:
        static int typeElement[warriorType], typeForce[warriorType];
        warrior(const int type, const int location, const int id, HQ *belong, const char *typeName):
            location(location),
            id(id),
            belong(belong),
            element(typeElement[type]),
            force(typeForce[type]),
            commonProperties(type, typeName)
        {
            sprintf(info, "%s %s %d", belong->getName(), typeName, id);
        }

        virtual ~warrior()
        {
            //printf("%s\n", info);
            for (int i = 0; i < weaponCount; i++)
                delete weapons[i];
        }

        virtual void advance() {}

        void printLocation()
        {
            printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n", hour, belong->getName(), getName(), id, location, element, force);
        }

        void printStatus()
        {
            int cnt[weaponType] = {0};
            for (int i = 0; i < weaponCount; i++)
                cnt[weapons[i]->getType()]++;
            printf("%03d:55 %s %s %d has %d sword %d bomb %d arrow and %d elements\n", hour, belong->getName(), getName(), id, cnt[0], cnt[1], cnt[2], element);
        }

        int getId()
        {
            return id;
        }

        int getElement()
        {
            return element;
        }

        int getForce()
        {
            return force;
        }

        int getLoyalty()
        {
            return loyalty;
        }

        void damage(int damageTaken)
        {
            element -= damageTaken;
        }

        int isDead()
        {
            return element <= 0;
        }

        void newWeapon(int wType)
        {
            switch (wType)
            {
                case 0:weapons[weaponCount] = new sword();break;
                case 1:weapons[weaponCount] = new bomb();break;
                case 2:weapons[weaponCount] = new arrow();break;
            }
            weaponCount++;
        }

        void getWeapon(warrior *enemy)
        {
            std::sort(enemy->weapons, enemy->weapons + enemy->weaponCount, cmp2);
            int cnt = std::min(maxWeapons - this->weaponCount, enemy->weaponCount);
            for (int i = 0; i < cnt; i++)
                this->weapons[i + this->weaponCount] = enemy->weapons[i];
            for (int i = 0; i < enemy->weaponCount - cnt; i++)
                enemy->weapons[i] = enemy->weapons[i + cnt];
            this->weaponCount += cnt;
            enemy->weaponCount -= cnt;
        }

        static void useWeapon(warrior *self, warrior *enemy, int &mark1, int &currentWeapon1)
        {
            int lastElement1, lastElement2;
            mark1++;
            if (self->weaponCount == 0)
                return;
            currentWeapon1 = (currentWeapon1 + 1) % self->weaponCount;
            lastElement1 = self->element;
            lastElement2 = enemy->element;
            self->weapons[currentWeapon1]->attack(self, enemy);
            //printf("%s %s %s %d %d\n", self->getName(), enemy->getName(), self->weapons[currentWeapon1]->getName(), self->weapons[currentWeapon1]->timeUsed, self->weapons[currentWeapon1]->isDestroyed());
            if (self->weapons[currentWeapon1]->isDestroyed())
            {
                //printf("destroyed\n");
                delete self->weapons[currentWeapon1];
                for (int i = currentWeapon1; i < self->weaponCount - 1; i++)
                    self->weapons[i] = self->weapons[i + 1];
                currentWeapon1--;
                self->weaponCount--;
                mark1 = 0;
            }
            if (lastElement1 != self->element || lastElement2 != enemy->element)
            {
                mark1 = 0;
            }
        }

        void battle(warrior *enemy)
        {
            //printf("%d %s %d %s %d\n", this->belong->getType(), this->getName(), this->weaponCount, enemy->getName(), enemy->weaponCount);
            std::sort(this->weapons, this->weapons + this->weaponCount, cmp1);
            std::sort(enemy->weapons, enemy->weapons + enemy->weaponCount, cmp1);
            int mark1 = 0, mark2 = 0, currentWeapon1 = -1, currentWeapon2 = -1;
            while (mark1 <= this->weaponCount || mark2 <= enemy->weaponCount)
            {
                useWeapon(this, enemy, mark1, currentWeapon1);
                if (this->isDead() and enemy->isDead())
                    return;
                if (this->isDead())
                {
                    enemy->getWeapon(this);
                    return;
                }
                if (enemy->isDead())
                {
                    this->getWeapon(enemy);
                    return;
                }
                useWeapon(enemy, this, mark2, currentWeapon2);
                if (this->isDead() and enemy->isDead())
                    return;
                if (this->isDead())
                {
                    enemy->getWeapon(this);
                    return;
                }
                if (enemy->isDead())
                {
                    this->getWeapon(enemy);
                    return;
                }
            }
        }

        virtual void flee() {}
        virtual void cheer() {}
        virtual void stealWeapon(warrior *enemy) {}
};


HQ::HQ(int type, int element):
    element(element),
    commonProperties(type, typeName[type])
{}

HQ::~HQ()
{
    for (int i = 0; i < warriorCount; i++)
        delete warriors[i];
}

int HQ::mapWarriorType(int currentWarriorType)
{
    return warriorTypeMap[getType()][currentWarriorType];
}

sword::sword():
    weapon(0, typeName)
{}

void sword::attack(warrior *attacker, warrior *defender)
{
    timeUsed++;
    defender->damage(attacker->getForce() * 2 / 10);
}

int sword::isDestroyed()
{
    return 0;
}

bomb::bomb():
    weapon(1, typeName)
{}

void bomb::attack(warrior *attacker, warrior *defender)
{
    timeUsed++;
    defender->damage(attacker->getForce() * 4 / 10);
    if (attacker->getType() != 1)
        attacker->damage(attacker->getForce() * 4 / 10 / 2);
}

int bomb::isDestroyed()
{
    return timeUsed;
}

arrow::arrow():
    weapon(2, typeName)
{}

void arrow::attack(warrior *attacker, warrior *defender)
{
    timeUsed++;
    defender->damage(attacker->getForce() * 3 / 10);
}

int arrow::isDestroyed()
{
    return timeUsed == 2;
}

class dragon:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "dragon";
    public:
        dragon(const int location, const int id, HQ *belong):
            warrior(0, location, id, belong, typeName)
        {
            newWeapon(id % 3);
        }

        void advance()
        {
            if (belong->getType() == 0)
                location += 1;
            else
                location -= 1;
        }

        void cheer()
        {
            printf("%03d:40 %s dragon %d yelled in city %d\n", hour, belong->getName(), id, location);
        }
};

class ninja:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "ninja";
    public:
        ninja(const int location, const int id, HQ *belong):
            warrior(1, location, id, belong, typeName)
        {
            newWeapon(id % 3);
            newWeapon((id + 1) % 3);
        }

        void advance()
        {
            if (belong->getType() == 0)
                location += 1;
            else
                location -= 1;
        }
};

class iceman:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "iceman";
    public:
        iceman(const int location, const int id, HQ *belong):
            warrior(2, location, id, belong, typeName)
        {
            newWeapon(id % 3);
        }

        void advance()
        {
            if (belong->getType() == 0)
                location += 1;
            else
                location -= 1;
            element -= element / 10;
        }
};

class lion:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "lion";
    public:
        lion(const int location, const int id, HQ *belong):
            warrior(3, location, id, belong, typeName)
        {
            newWeapon(id % 3);
            loyalty = belong->element;
        }

        void flee()
        {
            if (loyalty <= 0)
            {
                if (belong->getType() == 0)
                    printf(" red ");
                else
                    printf(" blue ");
                printf("lion %d ran away\n", id);
            }
        }

        void advance()
        {
            if (belong->getType() == 0)
                location += 1;
            else
                location -= 1;
            loyalty -= k;
        }
};

class wolf:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "wolf";
    public:
        wolf(const int location, const int id, HQ *belong):
            warrior(4, location, id, belong, typeName)
        {}

        void stealWeapon(warrior *enemy)
        {
            if (enemy->getType() == 4)
                return;
            if (enemy->weaponCount == 0)
                return;
            std::sort(enemy->weapons, enemy->weapons + enemy->weaponCount, cmp2);
            int i, cnt;
            for (i = 1; i < enemy->weaponCount; i++)
                if (enemy->weapons[i]->getType() != enemy->weapons[0]->getType())
                    break;
            cnt = std::min(maxWeapons - this->weaponCount, i);
            printf("%03d:35 %s wolf %d took %d %s from %s %s %d in city %d\n",
             hour, belong->getName(), this->id, cnt, enemy->weapons[0]->getName(), enemy->belong->getName(), enemy->getName(), enemy->id, this->location);
            for (int i = 0; i < cnt; i++)
                this->weapons[i + this->weaponCount] = enemy->weapons[i];
            for (int i = 0; i < enemy->weaponCount - cnt; i++)
                enemy->weapons[i] = enemy->weapons[i + cnt];
            this->weaponCount += cnt;
            enemy->weaponCount -= cnt;
            //printf("%d %d\n", this->weaponCount, enemy->weaponCount);
            //printf("%s %s\n", this->weapons[0]->getName(), enemy->weapons[0]->getName());
            return;
        }

        void advance()
        {
            if (belong->getType() == 0)
                location += 1;
            else
                location -= 1;
        }
};

void HQ::produce()
{
    if (stop)
        return;
    currentWarriorType = (currentWarriorType + 1) % 5;
    int mappedWarriorType = mapWarriorType(currentWarriorType);
    if (element < warrior::typeElement[mappedWarriorType])
    {
        stop = 1;
        return;
    }
    element -= warrior::typeElement[mappedWarriorType];
    int location;
    if (getType() == 0)
        location = 0;
    else
        location = n + 1;
    switch (mappedWarriorType)
    {
        case 0:currentWarrior = new dragon(location, warriorCount + 1, this);break;
        case 1:currentWarrior = new ninja(location, warriorCount + 1, this);break;
        case 2:currentWarrior = new iceman(location, warriorCount + 1, this);break;
        case 3:currentWarrior = new lion(location, warriorCount + 1, this);break;
        case 4:currentWarrior = new wolf(location, warriorCount + 1, this);break;
    }
    warriors[warriorCount] = currentWarrior;
    printf("%03d:00 %s %s %d born\n", warriorCount, getName(), currentWarrior->getName(), currentWarrior->getId());
    ++warriorTypeCount[mappedWarriorType];
    if (mappedWarriorType == 3)
        printf("Its loyalty is %d\n", currentWarrior->loyalty);
    warriorCount++;
    return;
}

constexpr char dragon::typeName[maxNameLen + 1], ninja::typeName[maxNameLen + 1], iceman::typeName[maxNameLen + 1], lion::typeName[maxNameLen + 1], wolf::typeName[maxNameLen + 1];
constexpr char sword::typeName[maxNameLen + 1], bomb::typeName[maxNameLen + 1], arrow::typeName[maxNameLen + 1], HQ::typeName[HQType][maxNameLen + 1];
constexpr int HQ::warriorTypeMap[HQType][warriorType];
int warrior::typeElement[warriorType], warrior::typeForce[warriorType];

int main()
{
	int caseCnt, m, t;
    //freopen("x.in", "r", stdin);
    //freopen("x.out", "w", stdout);
    scanf("%d", &caseCnt);
    for (int i = 0; i < caseCnt; i++)
    {
        printf("Case %d:\n", i + 1);
        scanf("%d%d%d%d", &m, &n, &k, &t);
        for (int i = 0; i < 5; i++)
            scanf("%d", &warrior::typeElement[i]);
        for (int i = 0; i < 5; i++)
            scanf("%d", &warrior::typeForce[i]);
        HQ x1(0, m), x2(1, m);
        hour = 0;
        while (1)
        {
            if (hour * 60 > t)
                break;
            x1.produce();
            x2.produce();
            if (hour * 60 + 5 > t)
                break;
            for (int i = 0; i <= n + 1; i++)
            {
                for (int j = 0; j < x1.warriorCount; j++)
                    if (x1.warriors[j] && x1.warriors[j]->location == i && x1.warriors[j]->getType() == 3 && x1.warriors[j]->loyalty <= 0)
                    {
                        printf("%03d:05 red lion %d ran away\n", hour, x1.warriors[j]->id);
                        delete x1.warriors[j];
                        x1.warriors[j] = NULL;
                    }
                for (int j = 0; j < x2.warriorCount; j++)
                    if (x2.warriors[j] && x2.warriors[j]->location == i && x2.warriors[j]->getType() == 3 && x2.warriors[j]->loyalty <= 0)
                    {
                        printf("%03d:05 blue lion %d ran away\n", hour, x2.warriors[j]->id);
                        delete x2.warriors[j];
                        x2.warriors[j] = NULL;
                    }
            }
            if (hour * 60 + 10 > t)
                break;
            int flag = 0, mark1[100000] = {0}, mark2[100000] = {0};
            for (int j = 0; j < x2.warriorCount; j++)
                if (x2.warriors[j] && x2.warriors[j]->location == 1 && !mark2[j])
                    x2.warriors[j]->advance(), printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
                     hour, x2.warriors[j]->getName(), x2.warriors[j]->id, x2.warriors[j]->element, x2.warriors[j]->force), flag = 1,
                     printf("%03d:10 red headquarter was taken\n", hour), mark2[j] = 1;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j < x1.warriorCount; j++)
                    if (x1.warriors[j] && x1.warriors[j]->location == i - 1 && !mark1[j])
                        x1.warriors[j]->advance(), printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
                         hour, x1.warriors[j]->getName(), x1.warriors[j]->id, i, x1.warriors[j]->element, x1.warriors[j]->force), mark1[j] = 1;
                for (int j = 0; j < x2.warriorCount; j++)
                    if (x2.warriors[j] && x2.warriors[j]->location == i + 1 && !mark2[j])
                        x2.warriors[j]->advance(), printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
                         hour, x2.warriors[j]->getName(), x2.warriors[j]->id, i, x2.warriors[j]->element, x2.warriors[j]->force), mark2[j] = 1;
            }
            for (int j = 0; j < x1.warriorCount; j++)
                if (x1.warriors[j] && x1.warriors[j]->location == n && !mark1[j])
                    x1.warriors[j]->advance(), printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
                     hour, x1.warriors[j]->getName(), x1.warriors[j]->id, x1.warriors[j]->element, x1.warriors[j]->force), flag = 1,
                     printf("%03d:10 blue headquarter was taken\n", hour), mark1[j] = 1;
            if (flag)
                break;
            if (hour * 60 + 35 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                int j1 = -1, j2 = -1;
                for (int j = 0; j < x1.warriorCount; j++)
                    if (x1.warriors[j] && x1.warriors[j]->location == i)
                        j1 = j;
                for (int j = 0; j < x2.warriorCount; j++)
                    if (x2.warriors[j] && x2.warriors[j]->location == i)
                        j2 = j;
                if (j1 != -1 && j2 != -1)
                {
                    if (x1.warriors[j1]->getType() == 4 && x2.warriors[j2]->getType() != 4)
                        x1.warriors[j1]->stealWeapon(x2.warriors[j2]);
                    if (x1.warriors[j1]->getType() != 4 && x2.warriors[j2]->getType() == 4)
                        x2.warriors[j2]->stealWeapon(x1.warriors[j1]);
                }
            }
            if (hour * 60 + 40 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                int j1 = -1, j2 = -1;
                for (int j = 0; j < x1.warriorCount; j++)
                    if (x1.warriors[j] && x1.warriors[j]->location == i)
                        j1 = j;
                for (int j = 0; j < x2.warriorCount; j++)
                    if (x2.warriors[j] && x2.warriors[j]->location == i)
                        j2 = j;
                if (j1 != -1 && j2 != -1)
                {
                    if (i & 1)
                        x1.warriors[j1]->battle(x2.warriors[j2]);
                    else
                        x2.warriors[j2]->battle(x1.warriors[j1]);
                    switch (x1.warriors[j1]->isDead() << 1 | x2.warriors[j2]->isDead())
                    {
                        case 0:printf("%03d:40 both %s and %s were alive in city %d\n", hour, x1.warriors[j1]->info, x2.warriors[j2]->info, i);break;
                        case 1:printf("%03d:40 %s killed %s in city %d remaining %d elements\n", hour, x1.warriors[j1]->info, x2.warriors[j2]->info, i, x1.warriors[j1]->element);break;
                        case 2:printf("%03d:40 %s killed %s in city %d remaining %d elements\n", hour, x2.warriors[j2]->info, x1.warriors[j1]->info, i, x2.warriors[j2]->element);break;
                        case 3:printf("%03d:40 both %s and %s died in city %d\n", hour, x1.warriors[j1]->info, x2.warriors[j2]->info, i);break;
                    }
                    if (x1.warriors[j1]->getType() == 0 && !x1.warriors[j1]->isDead())
                        x1.warriors[j1]->cheer();
                    if (x2.warriors[j2]->getType() == 0 && !x2.warriors[j2]->isDead())
                        x2.warriors[j2]->cheer();
                }
            }
            for (int j = 0; j < x1.warriorCount; j++)
                if (x1.warriors[j] && x1.warriors[j]->isDead())
                {
                    delete x1.warriors[j];
                    x1.warriors[j] = NULL;
                }
            for (int j = 0; j < x2.warriorCount; j++)
                if (x2.warriors[j] && x2.warriors[j]->isDead())
                {
                    delete x2.warriors[j];
                    x2.warriors[j] = NULL;
                }
            if (hour * 60 + 50 > t)
                break;
            printf("%03d:50 %d elements in red headquarter\n", hour, x1.element);
            printf("%03d:50 %d elements in blue headquarter\n", hour, x2.element);
            if (hour * 60 + 55 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j < x1.warriorCount; j++)
                    if (x1.warriors[j] && x1.warriors[j]->location == i)
                        x1.warriors[j]->printStatus();
                for (int j = 0; j < x2.warriorCount; j++)
                    if (x2.warriors[j] && x2.warriors[j]->location == i)
                        x2.warriors[j]->printStatus();
            }
            hour += 1;
        }
    }
    //fclose(stdin);
    //fclose(stdout);
}