#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<string>

#define maxNameLen 10
#define maxWarriors 1000
#define maxWeapons 10
#define HQType 2
#define warriorType 5
#define weaponType 3

typedef struct
{
    int hour, minute;
    int type;
    std::string info;
} BattleInfo;

std::vector<std::string> battleInfo;

BattleInfo x;
char temp[100];

int k, n, hour, r, HQCaptured;

class CommonProperties;
class Warrior;
class dragon;
class ninja;
class iceman;
class lion;
class wolf;
class HQ;
class City;

class CommonProperties
{
    protected:
        const int type;
        const char *name;
    public:
        CommonProperties(const int type, const char name[maxNameLen + 1]);
        ~CommonProperties();
        int getType();
        const char* getName();
};
class Warrior:public CommonProperties
{
    public:
        int location, id, element, force, loyalty = -1, weaponCount = 0, lastMove = -1, lastElement, weapons[3] = {0};
        double morale = -1;
        char info[100];
        HQ *belong;
    public:
        static int typeElement[warriorType], typeForce[warriorType];
        Warrior(const int type, const int id, HQ *belong, const char *typeName);
        virtual void advance();
        void printLocation();
        void printStatus();
        void damage(int damageTaken);
        int isDead();
        void newWeapon(int wType);
        void bomb(Warrior *enemy);
        void arrow(Warrior *enemy);
        void swordWear();
        void battle(Warrior *enemy);
        int attack();
        int fightBack();
        virtual int flee();
        virtual void cheer();
        virtual void getWeapon(Warrior *enemy);
};
class dragon:public Warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "dragon";
    public:
        dragon(const int id, HQ *belong);
        void cheer();
};
class ninja:public Warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "ninja";
    public:
        ninja(const int id, HQ *belong);
};
class iceman:public Warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "iceman";
        int step = 0;
    public:
        iceman(const int id, HQ *belong);
        void advance();
};
class lion:public Warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "lion";
    public:
        lion(const int id, HQ *belong);
        int flee();
};
class wolf:public Warrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "wolf";
    public:
        wolf(const int id, HQ *belong);
        void getWeapon(Warrior *enemy);
};
class HQ:public CommonProperties
{
    public:
        static constexpr char typeName[HQType][maxNameLen + 1] = {"red", "blue"};
        static constexpr int warriorTypeMap[HQType][warriorType] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
        int stop = 0, element, warriorCount = 0, currentWarriorType = -1, collectedElements = 0, warriorTypeCount[warriorType] = {0};
        Warrior *currentWarrior;
        std::vector<Warrior*> winningWarriors;
    public:
        HQ(int type, int element);
        virtual ~HQ();
        void produce();
        int mapWarriorType(int currentWarriorType);
        Warrior* locateWarrior(int location);
        void deleteWarrior(int location);
};
class City
{
    public:
        int id, element = 0, flag = 0, lastBattleResult = 0;
        Warrior* warriors[2][2] = {{NULL, NULL}, {NULL, NULL}};
        City(int id);

        static std::vector<City> cities;
        static void MoveFinished();
};

CommonProperties::CommonProperties(const int type, const char name[maxNameLen + 1]):
    type(type),
    name(name)
{}

CommonProperties::~CommonProperties()
{}

int CommonProperties::getType()
{
    return type;
}

const char* CommonProperties::getName()
{
    return name;
}

Warrior::Warrior(const int type, const int id, HQ *belong, const char *typeName):
    id(id),
    belong(belong),
    element(typeElement[type]),
    force(typeForce[type]),
    CommonProperties(type, typeName)
{
    location = (belong->getType() == 0) ? 0 : n + 1;
    sprintf(info, "%s %s %d", belong->getName(), typeName, id);
}

void Warrior::advance()
{
    if (lastMove == hour)
        return;
    lastMove = hour;
    location += (belong->getType() == 0) ? 1 : -1;
    City::cities[location].warriors[1][belong->getType()] = this;
}

void Warrior::printLocation()
{
    if (location == 0)
    {
        printf("%03d:10 %s reached red headquarter with %d elements and force %d\n", hour, info, element, force);
        if (City::cities[location].warriors[0][belong->getType()] != NULL)
            HQCaptured = 1, printf("%03d:10 red headquarter was taken\n", hour);
        return;
    }
    if (location == n + 1)
    {
        printf("%03d:10 %s reached blue headquarter with %d elements and force %d\n", hour, info, element, force);
        if (City::cities[location].warriors[0][belong->getType()] != NULL)
            HQCaptured = 1, printf("%03d:10 blue headquarter was taken\n", hour);
        return;
    }
    printf("%03d:10 %s marched to city %d with %d elements and force %d\n", hour, info, location, element, force);
}

void Warrior::printStatus()
{
    std::string weaponInfo = "";
    char temp[20];
    if (weapons[2])
    {
        sprintf(temp, "arrow(%d)", weapons[2]);
        if (weaponInfo.length())
            weaponInfo += ",";
        weaponInfo += temp;
    }
    if (weapons[1])
    {
        sprintf(temp, "bomb");
        if (weaponInfo.length())
            weaponInfo += ",";
        weaponInfo += temp;
    }
    if (weapons[0])
    {
        sprintf(temp, "sword(%d)", weapons[0]);
        if (weaponInfo.length())
            weaponInfo += ",";
        weaponInfo += temp;
    }
    if (!weaponInfo.length())
        weaponInfo = "no weapon";
    printf("%03d:55 %s has %s\n", hour, info, weaponInfo.c_str());
}

void Warrior::damage(int damageTaken)
{
    element -= damageTaken;
    if (element < 0)
        element = 0;
}

int Warrior::isDead()
{
    return element <= 0;
}

void Warrior::newWeapon(int wType)
{
    switch (wType)
    {
        case 0:weapons[0] = force * 2 / 10;break;
        case 1:weapons[1] = 1;break;
        case 2:weapons[2] = 3;break;
    }
}

void Warrior::bomb(Warrior *enemy)
{
    if (this->isDead() || enemy->isDead())
        return;
    if (enemy->element <= this->attack())
    {
        if (enemy->weapons[1])
        {
            enemy->damage(enemy->element);
            this->damage(this->element);
            printf("%03d:38 %s used a bomb and killed %s\n", hour, enemy->info, this->info);
        }
        return;
    }
    if (enemy->getType() != 1)
        if (this->element <= enemy->fightBack())
        {
            if (this->weapons[1])
            {
                this->damage(this->element);
                enemy->damage(enemy->element);
                printf("%03d:38 %s used a bomb and killed %s\n", hour, this->info, enemy->info);
            }
            return;
        }
}

void Warrior::arrow(Warrior *enemy)
{
    if (weapons[2])
    {
        enemy->damage(r);
        weapons[2]--;
        if (enemy->isDead())
            printf("%03d:35 %s shot and killed %s\n", hour, info, enemy->info);
        else
            printf("%03d:35 %s shot\n", hour, info);
    }
}

void Warrior::swordWear()
{
    this->weapons[0] = this->weapons[0] * 8 / 10;
}

int Warrior::attack()
{
    return this->force + this->weapons[0];
}

int Warrior::fightBack()
{
    return this->force / 2 + this->weapons[0];
}

void winning(Warrior* cheems, Warrior* enemy)// r u winning son?
{
    City & city = City::cities[cheems->location];
    if (enemy->getType() == 3)
        cheems->element += enemy->lastElement;
    cheems->getWeapon(enemy);
    cheems->belong->collectedElements += city.element;
    sprintf(temp, "%03d:40 %s earned %d elements for his headquarter\n", hour, cheems->info, city.element);
    battleInfo.push_back(temp);
    city.element = 0;
    cheems->belong->winningWarriors.push_back(cheems);
    if (cheems->belong->getType() == 0)
    {
        if (city.lastBattleResult == 1)
            if (city.flag != 1)
            {
                city.flag = 1;
                sprintf(temp, "%03d:40 red flag raised in city %d\n", hour, cheems->location);
                battleInfo.push_back(temp);
            }
        city.lastBattleResult = 1;
    }
    else
    {
        if (city.lastBattleResult == 2)
            if (city.flag != 2)
            {
                city.flag = 2;
                sprintf(temp, "%03d:40 blue flag raised in city %d\n", hour, cheems->location);
                battleInfo.push_back(temp);
            }
        city.lastBattleResult = 2;
    }
}

void Warrior::battle(Warrior *enemy)
{
    this->lastElement = this->element;
    enemy->lastElement = enemy->element;
    if (this->isDead() && enemy->isDead())
        return;
    if (this->isDead())
    {
        enemy->morale += 0.2;
        winning(enemy, this);
        return;
    }
    if (enemy->isDead())
    {
        this->morale += 0.2;
        this->cheer();
        winning(this, enemy);
        return;
    }
    enemy->damage(this->attack());
    this->swordWear();
    sprintf(temp, "%03d:40 %s attacked %s in city %d with %d elements and force %d\n", hour, this->info, enemy->info, enemy->location, this->element, this->force);
    battleInfo.push_back(temp);
    if (enemy->isDead())
    {
        sprintf(temp, "%03d:40 %s was killed in city %d\n", hour, enemy->info, enemy->location);
        battleInfo.push_back(temp);
        this->morale += 0.2;
        this->cheer();
        winning(this, enemy);
        return;
    }
    if (enemy->getType() != 1)
    {
        this->damage(enemy->fightBack());
        enemy->swordWear();
        sprintf(temp, "%03d:40 %s fought back against %s in city %d\n", hour, enemy->info, this->info, this->location);
        battleInfo.push_back(temp);
        if (this->isDead())
        {
            sprintf(temp, "%03d:40 %s was killed in city %d\n", hour, this->info, this->location);
            battleInfo.push_back(temp);
            enemy->morale += 0.2;
            winning(enemy, this);
            return;
        }
    }
    this->morale -= 0.2;
    enemy->morale -= 0.2;
    this->cheer();
    this->loyalty -= k;
    enemy->loyalty -= k;
    City::cities[this->location].lastBattleResult = 0;
}

int Warrior::flee()
{
    return 0;
}
void Warrior::cheer(){}
void Warrior::getWeapon(Warrior *enemy){}

dragon::dragon(const int id, HQ *belong):
    Warrior(0, id, belong, typeName)
{
    newWeapon(id % 3);
    morale = (double)belong->element / typeElement[getType()];
}

void dragon::cheer()
{
    if (morale > 0.8)
    {
        sprintf(temp, "%03d:40 %s yelled in city %d\n", hour, info, location);
        battleInfo.push_back(temp);
    }
}

ninja::ninja(const int id, HQ *belong):
    Warrior(1, id, belong, typeName)
{
    newWeapon(id % 3);
    newWeapon((id + 1) % 3);
}

iceman::iceman(const int id, HQ *belong):
    Warrior(2, id, belong, typeName)
{
    newWeapon(id % 3);
}

void iceman::advance()
{
    step++;
    if (step == 2)
    {
        if (element > 9)
            element -= 9;
        else
            element = 1;
        force += 20;
        step = 0;
    }
    Warrior::advance();
}

lion::lion(const int id, HQ *belong):
    Warrior(3, id, belong, typeName)
{
    loyalty = belong->element;
}

int lion::flee()
{
    if (loyalty <= 0)
        printf("%03d:05 %s ran away\n", hour, info);
    return loyalty <= 0;
}

wolf::wolf(const int id, HQ *belong):
    Warrior(4, id, belong, typeName)
{}

void wolf::getWeapon(Warrior *enemy)
{
    if (!isDead())
        for (int i = 0; i < 3; i++)
            if (!weapons[i] && enemy->weapons[i])
                weapons[i] = enemy->weapons[i];
}

HQ::HQ(int type, int element):
    element(element),
    CommonProperties(type, typeName[type])
{}

HQ::~HQ()
{
    for (int i = 0; i <= n + 1; i++)
        if (City::cities[i].warriors[0][type])
            delete City::cities[i].warriors[0][type];
}

int HQ::mapWarriorType(int currentWarriorType)
{
    return warriorTypeMap[getType()][currentWarriorType];
}

void HQ::produce()
{
    int mappedWarriorType = mapWarriorType(currentWarriorType);
    if (stop)
        if (element < Warrior::typeElement[mappedWarriorType])
            return;
        else
            stop = 0;
    else
    {
        currentWarriorType = (currentWarriorType + 1) % 5;
        mappedWarriorType = mapWarriorType(currentWarriorType);
    }
    if (element < Warrior::typeElement[mappedWarriorType])
    {
        stop = 1;
        return;
    }
    element -= Warrior::typeElement[mappedWarriorType];
    switch (mappedWarriorType)
    {
        case 0:currentWarrior = new dragon(warriorCount + 1, this);break;
        case 1:currentWarrior = new ninja(warriorCount + 1, this);break;
        case 2:currentWarrior = new iceman(warriorCount + 1, this);break;
        case 3:currentWarrior = new lion(warriorCount + 1, this);break;
        case 4:currentWarrior = new wolf(warriorCount + 1, this);break;
    }
    City::cities[currentWarrior->location].warriors[0][type] = currentWarrior;
    printf("%03d:00 %s %s %d born\n", hour, getName(), currentWarrior->getName(), currentWarrior->id);
    ++warriorTypeCount[mappedWarriorType];
    if (mappedWarriorType == 0)
        printf("Its morale is %.2lf\n", currentWarrior->morale);
    if (mappedWarriorType == 3)
        printf("Its loyalty is %d\n", currentWarrior->loyalty);
    warriorCount++;
    return;
}

Warrior* HQ::locateWarrior(int location)
{
    return City::cities[location].warriors[0][type];
}

void HQ::deleteWarrior(int location)
{
    delete City::cities[location].warriors[0][type];
    City::cities[location].warriors[0][type] = NULL;
}

City::City(int id):
    id(id)
{}

void City::MoveFinished()
{
    for (auto &&i: cities)
    {
        memcpy(i.warriors[0], i.warriors[1], sizeof(i.warriors[1]));
        if (i.id != 0 && i.id != n + 1)
            memset(i.warriors[1], 0 ,sizeof(i.warriors[0]));
    }
}

constexpr char dragon::typeName[maxNameLen + 1], ninja::typeName[maxNameLen + 1], iceman::typeName[maxNameLen + 1], lion::typeName[maxNameLen + 1], wolf::typeName[maxNameLen + 1];
constexpr char HQ::typeName[HQType][maxNameLen + 1];
constexpr int HQ::warriorTypeMap[HQType][warriorType];
int Warrior::typeElement[warriorType], Warrior::typeForce[warriorType];
std::vector<City> City::cities;

int main()
{
    //freopen("x.in", "r", stdin);
    //freopen("x.out", "w", stdout);
	int caseCnt, m, t;
    Warrior *w1, *w2;
    scanf("%d", &caseCnt);
    for (int i = 0; i < caseCnt; i++)
    {
        printf("Case %d:\n", i + 1);
        scanf("%d%d%d%d%d", &m, &n, &r, &k, &t);
        for (int i = 0; i < 5; i++)
            scanf("%d", &Warrior::typeElement[i]);
        for (int i = 0; i < 5; i++)
            scanf("%d", &Warrior::typeForce[i]);
        HQ x1(0, m), x2(1, m);
        HQCaptured = 0;
        hour = 0;
        City::cities.clear();
        for (int i = 0; i <= n + 1; i++)
            City::cities.push_back(City(i));
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
            City::MoveFinished();
            if (HQCaptured)
                break;
            if (hour * 60 + 20 > t)
                break;
            for (int i = 1; i <= n; i++)
                City::cities[i].element += 10;
            if (hour * 60 + 30 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w1 && !w2)
                    x1.element += City::cities[i].element, printf("%03d:30 %s earned %d elements for his headquarter\n", hour, w1->info, City::cities[i].element), City::cities[i].element = 0;
                if (!w1 && w2)
                    x2.element += City::cities[i].element, printf("%03d:30 %s earned %d elements for his headquarter\n", hour, w2->info, City::cities[i].element), City::cities[i].element = 0;
            }
            if (hour * 60 + 35 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i), w2 = x2.locateWarrior(i + 1);
                if (w1 && w2)
                    w1->arrow(w2);
                w2 = x2.locateWarrior(i), w1 = x1.locateWarrior(i - 1);
                if (w2 && w1)
                    w2->arrow(w1);
            }
            if (hour * 60 + 38 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i), w2 = x2.locateWarrior(i);
                if (w1 && w2)
                    if (City::cities[i].flag)
                        if (City::cities[i].flag == 1)
                            w1->bomb(w2);
                        else
                            w2->bomb(w1);
                    else
                        if (i & 1)
                            w1->bomb(w2);
                        else
                            w2->bomb(w1);
            }
            if (hour * 60 + 40 > t)
                break;
            for (int i = 1; i <= n; i++)
            {
                w1 = x1.locateWarrior(i);
                w2 = x2.locateWarrior(i);
                if (w1 && w2)
                {
                    if (City::cities[i].flag)
                        if (City::cities[i].flag == 1)
                            w1->battle(w2);
                        else
                            w2->battle(w1);
                    else
                        if (i & 1)
                            w1->battle(w2);
                        else
                            w2->battle(w1);
                }
                if (w1 && w1->isDead())
                    x1.deleteWarrior(i);
                if (w2 && w2->isDead())
                    x2.deleteWarrior(i);
            }
            for (auto x = x1.winningWarriors.end(); x != x1.winningWarriors.begin(); x--)
                if (x1.element >= 8)
                    (*(x - 1))->element += 8, x1.element -= 8;
            for (auto x: x2.winningWarriors)
                if (x2.element >= 8)
                    x->element += 8, x2.element -= 8;
            x1.winningWarriors.clear();
            x2.winningWarriors.clear();
            x1.element += x1.collectedElements;
            x2.element += x2.collectedElements;
            x1.collectedElements = 0;
            x2.collectedElements = 0;
            for (auto i: battleInfo)
                printf("%s", i.c_str());
            battleInfo.clear();
            if (hour * 60 + 50 > t)
                break;
            printf("%03d:50 %d elements in red headquarter\n", hour, x1.element);
            printf("%03d:50 %d elements in blue headquarter\n", hour, x2.element);
            if (hour * 60 + 55 > t)
                break;
            for (int i = 0; i <= n + 1; i++)
            {
                w1 = x1.locateWarrior(i);
                if (w1)
                    w1->printStatus();
            }
            for (int i = 0; i <= n + 1; i++)
            {
                w2 = x2.locateWarrior(i);
                if (w2)
                    w2->printStatus();
            }
            hour++;
        }
    }
    //fclose(stdin);
    //fclose(stdout);
}