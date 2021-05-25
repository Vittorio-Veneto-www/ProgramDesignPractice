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

std::vector<std::string> battleInfo;

char temp[100];

int k, n, hour, r, HQCaptured;

class CCommonProperties;
class CWarrior;
class CDragon;
class CNinja;
class CIceman;
class CLion;
class CWolf;
class CHQ;
class CCity;
class CKindom;

class CCommonProperties
{
    protected:
        const int type;
        const char *name;
    public:
        CCommonProperties(const int type, const char name[maxNameLen + 1]);
        ~CCommonProperties();
        int getType();
        const char* getName();
};
class CWarrior:public CCommonProperties
{
    public:
        int location, id, element, force, loyalty = -1, weaponCount = 0, lastMove = -1, lastElement, weapons[3] = {0};
        double morale = -1;
        char info[100];
        CHQ *belong;
    public:
        static int typeElement[warriorType], typeForce[warriorType];
        CWarrior(const int type, const int id, CHQ *belong, const char *typeName);
        virtual void advance();
        void printLocation();
        void printStatus();
        void damage(int damageTaken);
        int isDead();
        void newWeapon(int wType);
        void bomb(CWarrior *enemy);
        void arrow(CWarrior *enemy);
        void swordWear();
        void battle(CWarrior *enemy);
        int attack();
        int fightBack();
        virtual int flee();
        virtual void cheer();
        virtual void getWeapon(CWarrior *enemy);
};
class CDragon:public CWarrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "dragon";
    public:
        CDragon(const int id, CHQ *belong);
        void cheer();
};
class CNinja:public CWarrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "ninja";
    public:
        CNinja(const int id, CHQ *belong);
};
class CIceman:public CWarrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "iceman";
        int step = 0;
    public:
        CIceman(const int id, CHQ *belong);
        void advance();
};
class CLion:public CWarrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "lion";
    public:
        CLion(const int id, CHQ *belong);
        int flee();
};
class CWolf:public CWarrior
{
    protected:
        static constexpr char typeName[maxNameLen + 1] = "wolf";
    public:
        CWolf(const int id, CHQ *belong);
        void getWeapon(CWarrior *enemy);
};
class CHQ:public CCommonProperties
{
    public:
        static constexpr char typeName[HQType][maxNameLen + 1] = {"red", "blue"};
        static constexpr int warriorTypeMap[HQType][warriorType] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
        int stop = 0, element, warriorCount = 0, currentWarriorType = -1, collectedElements = 0, warriorTypeCount[warriorType] = {0};
        CWarrior *currentWarrior;
        std::vector<CWarrior*> winningWarriors;
    public:
        CHQ(int type, int element);
        virtual ~CHQ();
        void produce();
        int mapWarriorType(int currentWarriorType);
        CWarrior* locateWarrior(int location);
        void deleteWarrior(int location);
};
class CCity
{
    public:
        int id, element = 0, flag = 0, lastBattleResult = 0;
        CWarrior* warriors[2][2] = {{NULL, NULL}, {NULL, NULL}};
        CCity(int id);

        static std::vector<CCity> cities;
        static void MoveFinished();
};
class CKindom
{
    public:
        static int m, t;
        static CHQ x1, x2;
        static void init();
        static void run();
        static void print();
};

CCommonProperties::CCommonProperties(const int type, const char name[maxNameLen + 1]):
    type(type),
    name(name)
{}

CCommonProperties::~CCommonProperties()
{}

int CCommonProperties::getType()
{
    return type;
}

const char* CCommonProperties::getName()
{
    return name;
}

CWarrior::CWarrior(const int type, const int id, CHQ *belong, const char *typeName):
    id(id),
    belong(belong),
    element(typeElement[type]),
    force(typeForce[type]),
    CCommonProperties(type, typeName)
{
    location = (belong->getType() == 0) ? 0 : n + 1;
    sprintf(info, "%s %s %d", belong->getName(), typeName, id);
}

void CWarrior::advance()
{
    if (lastMove == hour)
        return;
    lastMove = hour;
    location += (belong->getType() == 0) ? 1 : -1;
    CCity::cities[location].warriors[1][belong->getType()] = this;
}

void CWarrior::printLocation()
{
    if (location == 0)
    {
        sprintf(temp, "%03d:10 %s reached red headquarter with %d elements and force %d\n", hour, info, element, force);
        battleInfo.push_back(temp);
        if (CCity::cities[location].warriors[0][belong->getType()] != NULL)
            HQCaptured = 1, sprintf(temp, "%03d:10 red headquarter was taken\n", hour), battleInfo.push_back(temp);
        return;
    }
    if (location == n + 1)
    {
        sprintf(temp, "%03d:10 %s reached blue headquarter with %d elements and force %d\n", hour, info, element, force);
        battleInfo.push_back(temp);
        if (CCity::cities[location].warriors[0][belong->getType()] != NULL)
            HQCaptured = 1, sprintf(temp, "%03d:10 blue headquarter was taken\n", hour), battleInfo.push_back(temp);
        return;
    }
    sprintf(temp, "%03d:10 %s marched to city %d with %d elements and force %d\n", hour, info, location, element, force);
    battleInfo.push_back(temp);
}

void CWarrior::printStatus()
{
    std::string weaponInfo = "";
    char temp[20], temp1[100];
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
    sprintf(temp1, "%03d:55 %s has %s\n", hour, info, weaponInfo.c_str());
    battleInfo.push_back(temp1);
}

void CWarrior::damage(int damageTaken)
{
    element -= damageTaken;
    if (element < 0)
        element = 0;
}

int CWarrior::isDead()
{
    return element <= 0;
}

void CWarrior::newWeapon(int wType)
{
    switch (wType)
    {
        case 0:weapons[0] = force * 2 / 10;break;
        case 1:weapons[1] = 1;break;
        case 2:weapons[2] = 3;break;
    }
}

void CWarrior::bomb(CWarrior *enemy)
{
    if (this->isDead() || enemy->isDead())
        return;
    if (enemy->element <= this->attack())
    {
        if (enemy->weapons[1])
        {
            enemy->damage(enemy->element);
            this->damage(this->element);
            sprintf(temp, "%03d:38 %s used a bomb and killed %s\n", hour, enemy->info, this->info);
            battleInfo.push_back(temp);
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
                sprintf(temp, "%03d:38 %s used a bomb and killed %s\n", hour, this->info, enemy->info);
                battleInfo.push_back(temp);
            }
            return;
        }
}

void CWarrior::arrow(CWarrior *enemy)
{
    if (weapons[2])
    {
        enemy->damage(r);
        weapons[2]--;
        if (enemy->isDead())
            sprintf(temp, "%03d:35 %s shot and killed %s\n", hour, info, enemy->info);
        else
            sprintf(temp, "%03d:35 %s shot\n", hour, info);
        battleInfo.push_back(temp);
    }
}

void CWarrior::swordWear()
{
    this->weapons[0] = this->weapons[0] * 8 / 10;
}

int CWarrior::attack()
{
    return this->force + this->weapons[0];
}

int CWarrior::fightBack()
{
    return this->force / 2 + this->weapons[0];
}

void winning(CWarrior* cheems, CWarrior* enemy)// r u winning son?
{
    CCity & city = CCity::cities[cheems->location];
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

void CWarrior::battle(CWarrior *enemy)
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
    CCity::cities[this->location].lastBattleResult = 0;
}

int CWarrior::flee()
{
    return 0;
}
void CWarrior::cheer(){}
void CWarrior::getWeapon(CWarrior *enemy){}

CDragon::CDragon(const int id, CHQ *belong):
    CWarrior(0, id, belong, typeName)
{
    newWeapon(id % 3);
    morale = (double)belong->element / typeElement[getType()];
}

void CDragon::cheer()
{
    if (morale > 0.8)
    {
        sprintf(temp, "%03d:40 %s yelled in city %d\n", hour, info, location);
        battleInfo.push_back(temp);
    }
}

CNinja::CNinja(const int id, CHQ *belong):
    CWarrior(1, id, belong, typeName)
{
    newWeapon(id % 3);
    newWeapon((id + 1) % 3);
}

CIceman::CIceman(const int id, CHQ *belong):
    CWarrior(2, id, belong, typeName)
{
    newWeapon(id % 3);
}

void CIceman::advance()
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
    CWarrior::advance();
}

CLion::CLion(const int id, CHQ *belong):
    CWarrior(3, id, belong, typeName)
{
    loyalty = belong->element;
}

int CLion::flee()
{
    if (loyalty <= 0)
        sprintf(temp, "%03d:05 %s ran away\n", hour, info), battleInfo.push_back(temp);
    return loyalty <= 0;
}

CWolf::CWolf(const int id, CHQ *belong):
    CWarrior(4, id, belong, typeName)
{}

void CWolf::getWeapon(CWarrior *enemy)
{
    if (!isDead())
        for (int i = 0; i < 3; i++)
            if (!weapons[i] && enemy->weapons[i])
                weapons[i] = enemy->weapons[i];
}

CHQ::CHQ(int type, int element):
    element(element),
    CCommonProperties(type, typeName[type])
{}

CHQ::~CHQ()
{
    for (int i = 0; i <= n + 1; i++)
        if (CCity::cities[i].warriors[0][type])
            delete CCity::cities[i].warriors[0][type];
}

int CHQ::mapWarriorType(int currentWarriorType)
{
    return warriorTypeMap[getType()][currentWarriorType];
}

void CHQ::produce()
{
    int mappedWarriorType = mapWarriorType(currentWarriorType);
    if (stop)
        if (element < CWarrior::typeElement[mappedWarriorType])
            return;
        else
            stop = 0;
    else
    {
        currentWarriorType = (currentWarriorType + 1) % 5;
        mappedWarriorType = mapWarriorType(currentWarriorType);
    }
    if (element < CWarrior::typeElement[mappedWarriorType])
    {
        stop = 1;
        return;
    }
    element -= CWarrior::typeElement[mappedWarriorType];
    switch (mappedWarriorType)
    {
        case 0:currentWarrior = new CDragon(warriorCount + 1, this);break;
        case 1:currentWarrior = new CNinja(warriorCount + 1, this);break;
        case 2:currentWarrior = new CIceman(warriorCount + 1, this);break;
        case 3:currentWarrior = new CLion(warriorCount + 1, this);break;
        case 4:currentWarrior = new CWolf(warriorCount + 1, this);break;
    }
    CCity::cities[currentWarrior->location].warriors[0][type] = currentWarrior;
    sprintf(temp, "%03d:00 %s %s %d born\n", hour, getName(), currentWarrior->getName(), currentWarrior->id);
    battleInfo.push_back(temp);
    ++warriorTypeCount[mappedWarriorType];
    if (mappedWarriorType == 0)
        sprintf(temp, "Its morale is %.2lf\n", currentWarrior->morale), battleInfo.push_back(temp);
    if (mappedWarriorType == 3)
        sprintf(temp, "Its loyalty is %d\n", currentWarrior->loyalty), battleInfo.push_back(temp);
    warriorCount++;
    return;
}

CWarrior* CHQ::locateWarrior(int location)
{
    return CCity::cities[location].warriors[0][type];
}

void CHQ::deleteWarrior(int location)
{
    delete CCity::cities[location].warriors[0][type];
    CCity::cities[location].warriors[0][type] = NULL;
}

CCity::CCity(int id):
    id(id)
{}

void CCity::MoveFinished()
{
    for (auto &&i: cities)
    {
        memcpy(i.warriors[0], i.warriors[1], sizeof(i.warriors[1]));
        if (i.id != 0 && i.id != n + 1)
            memset(i.warriors[1], 0 ,sizeof(i.warriors[0]));
    }
}

void CKindom::init()
{
    scanf("%d%d%d%d%d", &m, &n, &r, &k, &t);
    for (int i = 0; i < 5; i++)
        scanf("%d", &CWarrior::typeElement[i]);
    for (int i = 0; i < 5; i++)
        scanf("%d", &CWarrior::typeForce[i]);
    HQCaptured = 0;
    hour = 0;
    CCity::cities.clear();
    for (int i = 0; i <= n + 1; i++)
        CCity::cities.push_back(CCity(i));
    battleInfo.clear();
}

void CKindom::run()
{
    CWarrior *w1, *w2;
    CHQ x1(0, m), x2(1, m);
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
        CCity::MoveFinished();
        if (HQCaptured)
            break;
        if (hour * 60 + 20 > t)
            break;
        for (int i = 1; i <= n; i++)
            CCity::cities[i].element += 10;
        if (hour * 60 + 30 > t)
            break;
        for (int i = 1; i <= n; i++)
        {
            w1 = x1.locateWarrior(i);
            w2 = x2.locateWarrior(i);
            if (w1 && !w2)
                x1.element += CCity::cities[i].element, sprintf(temp, "%03d:30 %s earned %d elements for his headquarter\n", hour, w1->info, CCity::cities[i].element),
                    CCity::cities[i].element = 0, battleInfo.push_back(temp);
            if (!w1 && w2)
                x2.element += CCity::cities[i].element, sprintf(temp, "%03d:30 %s earned %d elements for his headquarter\n", hour, w2->info, CCity::cities[i].element),
                    CCity::cities[i].element = 0, battleInfo.push_back(temp);
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
                if (CCity::cities[i].flag)
                    if (CCity::cities[i].flag == 1)
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
                if (CCity::cities[i].flag)
                    if (CCity::cities[i].flag == 1)
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
        if (hour * 60 + 50 > t)
            break;
        sprintf(temp, "%03d:50 %d elements in red headquarter\n", hour, x1.element);
        battleInfo.push_back(temp);
        sprintf(temp, "%03d:50 %d elements in blue headquarter\n", hour, x2.element);
        battleInfo.push_back(temp);
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

void CKindom::print()
{
    for (auto i: battleInfo)
        printf("%s", i.c_str());
}

constexpr char CDragon::typeName[maxNameLen + 1], CNinja::typeName[maxNameLen + 1], CIceman::typeName[maxNameLen + 1], CLion::typeName[maxNameLen + 1], CWolf::typeName[maxNameLen + 1];
constexpr char CHQ::typeName[HQType][maxNameLen + 1];
constexpr int CHQ::warriorTypeMap[HQType][warriorType];
int CWarrior::typeElement[warriorType], CWarrior::typeForce[warriorType], CKindom::m, CKindom::t;
std::vector<CCity> CCity::cities;

int main()
{
	int caseCnt, m, t;
    scanf("%d", &caseCnt);
    for (int i = 0; i < caseCnt; i++)
    {
        printf("Case %d:\n", i + 1);
        CKindom::init();
        CKindom::run();
        CKindom::print();
    }
}