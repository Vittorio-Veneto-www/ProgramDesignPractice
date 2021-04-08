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

int k, n, hour, flag;

class commonProperties;
class weapon;
class sword;
class bomb;
class arrow;
class warrior;
class dragon;
class ninja;
class iceman;
class lion;
class wolf;
class HQ;

class commonProperties
{
    protected:
        const int type;
        const char *name;
    public:
        commonProperties(const int type, const char name[maxNameLen + 1]);
        ~commonProperties();
        int getType();
        const char* getName();
};
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
        virtual void attack(warrior *attacker, warrior *defender) = 0;
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
class warrior:public commonProperties
{
    public:
        int location, id, element, force, loyalty = -1, weaponCount = 0, lastMove = -1;
        char info[100];
        weapon *currentWeapon, *weapons[maxWeapons];
        HQ *belong;
    public:
        static int typeElement[warriorType], typeForce[warriorType];
        warrior(const int type, const int id, HQ *belong, const char *typeName);
        virtual ~warrior();
        virtual void advance();
        void printLocation();
        void printStatus();
        void damage(int damageTaken);
        int isDead();
        void newWeapon(int wType);
        void getWeapon(warrior *enemy);
        void battle(warrior *enemy);
        virtual int flee();
        virtual void cheer();
        virtual void stealWeapon(warrior *enemy);
};
class dragon:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "dragon";
    public:
        dragon(const int id, HQ *belong);
        void cheer();
};
class ninja:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "ninja";
    public:
        ninja(const int id, HQ *belong);
};
class iceman:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "iceman";
    public:
        iceman(const int id, HQ *belong);
        void advance();
};
class lion:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "lion";
    public:
        lion(const int id, HQ *belong);
        int flee();
        void advance();
};
class wolf:public warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "wolf";
    public:
        wolf(const int id, HQ *belong);
        void stealWeapon(warrior *enemy);
};
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
        warrior* locateWarrior(int location);
        void deleteWarrior(int location);
};

commonProperties::commonProperties(const int type, const char name[maxNameLen + 1]):
    type(type),
    name(name)
{}

commonProperties::~commonProperties()
{}

int commonProperties::getType()
{
    return type;
}

const char* commonProperties::getName()
{
    return name;
}

int cmp1(weapon *x, weapon *y)
{
    return (x->type < y->type) || (x->type == y->type && x->timeUsed > y->timeUsed);
}

int cmp2(weapon *x, weapon *y)
{
    return (x->type < y->type) || (x->type == y->type && x->timeUsed < y->timeUsed);
}

sword::sword():
    weapon(0, typeName)
{}

void sword::attack(warrior *attacker, warrior *defender)
{
    timeUsed++;
    defender->damage(attacker->force * 2 / 10);
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
    defender->damage(attacker->force * 4 / 10);
    if (attacker->getType() != 1)
        attacker->damage(attacker->force * 4 / 10 / 2);
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
    defender->damage(attacker->force * 3 / 10);
}

int arrow::isDestroyed()
{
    return timeUsed == 2;
}

warrior::warrior(const int type, const int id, HQ *belong, const char *typeName):
    id(id),
    belong(belong),
    element(typeElement[type]),
    force(typeForce[type]),
    commonProperties(type, typeName)
{
    location = (belong->getType() == 0) ? 0 : n + 1;
    sprintf(info, "%s %s %d", belong->getName(), typeName, id);
}

warrior::~warrior()
{
    for (int i = 0; i < weaponCount; i++)
        delete weapons[i];
}

void warrior::advance()
{
    if (lastMove == hour)
        return;
    lastMove = hour;
    location += (belong->getType() == 0) ? 1 : -1;
}

void warrior::printLocation()
{
    if (location == 0)
    {
        printf("%03d:10 %s reached red headquarter with %d elements and force %d\n", hour, info, element, force),
            flag = 1, printf("%03d:10 red headquarter was taken\n", hour);
        return;
    }
    if (location == n + 1)
    {
        printf("%03d:10 %s reached blue headquarter with %d elements and force %d\n", hour, info, element, force),
            flag = 1, printf("%03d:10 blue headquarter was taken\n", hour);
        return;
    }
    printf("%03d:10 %s marched to city %d with %d elements and force %d\n", hour, info, location, element, force);
}

void warrior::printStatus()
{
    int cnt[weaponType] = {0};
    for (int i = 0; i < weaponCount; i++)
        cnt[weapons[i]->getType()]++;
    printf("%03d:55 %s has %d sword %d bomb %d arrow and %d elements\n", hour, info, cnt[0], cnt[1], cnt[2], element);
}

void warrior::damage(int damageTaken)
{
    element -= damageTaken;
}

int warrior::isDead()
{
    return element <= 0;
}

void warrior::newWeapon(int wType)
{
    switch (wType)
    {
        case 0:weapons[weaponCount] = new sword();break;
        case 1:weapons[weaponCount] = new bomb();break;
        case 2:weapons[weaponCount] = new arrow();break;
    }
    weaponCount++;
}

void warrior::getWeapon(warrior *enemy)
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

void useWeapon(warrior *self, warrior *enemy, int &mark1, int &currentWeapon1)
{
    int lastElement1, lastElement2;
    mark1++;
    if (self->weaponCount == 0)
        return;
    currentWeapon1 = (currentWeapon1 + 1) % self->weaponCount;
    lastElement1 = self->element;
    lastElement2 = enemy->element;
    self->weapons[currentWeapon1]->attack(self, enemy);
    if (self->weapons[currentWeapon1]->isDestroyed())
    {
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

void warrior::battle(warrior *enemy)
{
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

int warrior::flee()
{
    return 0;
}
void warrior::cheer() {}
void warrior::stealWeapon(warrior *enemy) {}

dragon::dragon(const int id, HQ *belong):
    warrior(0, id, belong, typeName)
{
    newWeapon(id % 3);
}

void dragon::cheer()
{
    printf("%03d:40 %s yelled in city %d\n", hour, info, location);
}

ninja::ninja(const int id, HQ *belong):
    warrior(1, id, belong, typeName)
{
    newWeapon(id % 3);
    newWeapon((id + 1) % 3);
}

iceman::iceman(const int id, HQ *belong):
    warrior(2, id, belong, typeName)
{
    newWeapon(id % 3);
}

void iceman::advance()
{
    warrior::advance();
    element -= element / 10;
}

lion::lion(const int id, HQ *belong):
    warrior(3, id, belong, typeName)
{
    newWeapon(id % 3);
    loyalty = belong->element;
}

int lion::flee()
{
    if (loyalty <= 0)
        printf("%03d:05 %s ran away\n", hour, info);
    return loyalty <= 0;
}

void lion::advance()
{
    warrior::advance();
    loyalty -= k;
}

wolf::wolf(const int id, HQ *belong):
    warrior(4, id, belong, typeName)
{}

void wolf::stealWeapon(warrior *enemy)
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
    printf("%03d:35 %s took %d %s from %s in city %d\n",
        hour, this->info, cnt, enemy->weapons[0]->getName(), enemy->info, this->location);
    for (int i = 0; i < cnt; i++)
        this->weapons[i + this->weaponCount] = enemy->weapons[i];
    for (int i = 0; i < enemy->weaponCount - cnt; i++)
        enemy->weapons[i] = enemy->weapons[i + cnt];
    this->weaponCount += cnt;
    enemy->weaponCount -= cnt;
    return;
}

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
    switch (mappedWarriorType)
    {
        case 0:currentWarrior = new dragon(warriorCount + 1, this);break;
        case 1:currentWarrior = new ninja(warriorCount + 1, this);break;
        case 2:currentWarrior = new iceman(warriorCount + 1, this);break;
        case 3:currentWarrior = new lion(warriorCount + 1, this);break;
        case 4:currentWarrior = new wolf(warriorCount + 1, this);break;
    }
    warriors[warriorCount] = currentWarrior;
    printf("%03d:00 %s %s %d born\n", hour, getName(), currentWarrior->getName(), currentWarrior->id);
    ++warriorTypeCount[mappedWarriorType];
    if (mappedWarriorType == 3)
        printf("Its loyalty is %d\n", currentWarrior->loyalty);
    warriorCount++;
    return;
}

warrior* HQ::locateWarrior(int location)
{
    if (type == 0)
    {
        for (int i = 0; i < warriorCount; i++)
            if (warriors[i] && warriors[i]->location == location)
                return warriors[i];
    }
    else
    {
        for (int i = warriorCount - 1; i >= 0; i--)
            if (warriors[i] && warriors[i]->location == location)
                return warriors[i];
    }
    return NULL;
}

void HQ::deleteWarrior(int location)
{
    for (int i = 0; i < warriorCount; i++)
        if (warriors[i] && warriors[i]->location == location)
        {
            delete warriors[i];
            warriors[i] = NULL;
        }
}

constexpr char dragon::typeName[maxNameLen + 1], ninja::typeName[maxNameLen + 1], iceman::typeName[maxNameLen + 1], lion::typeName[maxNameLen + 1], wolf::typeName[maxNameLen + 1];
constexpr char sword::typeName[maxNameLen + 1], bomb::typeName[maxNameLen + 1], arrow::typeName[maxNameLen + 1], HQ::typeName[HQType][maxNameLen + 1];
constexpr int HQ::warriorTypeMap[HQType][warriorType];
int warrior::typeElement[warriorType], warrior::typeForce[warriorType];

int main()
{
	int caseCnt, m, t;
    warrior *w1, *w2;
    freopen("x.in", "r", stdin);
    freopen("x.out", "w", stdout);
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
                w1 = x1.locateWarrior(i);
                if (w1 && w1->flee())
                    x1.deleteWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w2 && w2->flee())
                    x2.deleteWarrior(i);
            }
            if (hour * 60 + 10 > t)
                break;
            flag = 0;
            w2 = x2.locateWarrior(1);
            if (w2 && w2->lastMove != hour)
                w2->advance(), w2->printLocation();
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i - 1);
                if (w1 && w1->lastMove != hour)
                    w1->advance(), w1->printLocation();
                w2 = x2.locateWarrior(i + 1);
                if (w2 && w2->lastMove != hour)
                    w2->advance(), w2->printLocation();
            }
            w1 = x1.locateWarrior(n);
            if (w1 && w1->lastMove != hour)
                w1->advance(), w1->printLocation();
            if (flag)
                break;
            if (hour * 60 + 35 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w1 && w2)
                {
                    if (w1->getType() == 4)
                        w1->stealWeapon(w2);
                    if (w2->getType() == 4)
                        w2->stealWeapon(w1);
                }
            }
            if (hour * 60 + 40 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w1 && w2)
                {
                    if (i & 1)
                        w1->battle(w2);
                    else
                        w2->battle(w1);
                    switch (w1->isDead() << 1 | w2->isDead())
                    {
                        case 0:printf("%03d:40 both %s and %s were alive in city %d\n", hour, w1->info, w2->info, i);break;
                        case 1:printf("%03d:40 %s killed %s in city %d remaining %d elements\n", hour, w1->info, w2->info, i, w1->element);break;
                        case 2:printf("%03d:40 %s killed %s in city %d remaining %d elements\n", hour, w2->info, w1->info, i, w2->element);break;
                        case 3:printf("%03d:40 both %s and %s died in city %d\n", hour, w1->info, w2->info, i);break;
                    }
                    if (w1->isDead())
                        x1.deleteWarrior(i);
                    else
                        w1->cheer();
                    if (w2->isDead())
                        x2.deleteWarrior(i);
                    else
                        w2->cheer();
                }
            }
            if (hour * 60 + 50 > t)
                break;
            printf("%03d:50 %d elements in red headquarter\n", hour, x1.element);
            printf("%03d:50 %d elements in blue headquarter\n", hour, x2.element);
            if (hour * 60 + 55 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w1)
                    w1->printStatus();
                if (w2)
                    w2->printStatus();
            }
            hour++;
        }
    }
    fclose(stdin);
    fclose(stdout);
}