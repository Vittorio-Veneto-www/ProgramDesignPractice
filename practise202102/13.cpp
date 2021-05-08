#include<iostream>
#include<cstring>
#include<list>
#include<algorithm>
using namespace std;

class TV_Drama{
	public:
	char name[100];
	int actor;
	int story;
	int acting_skill;
    TV_Drama(char* _name, int actor, int story, int acting_skill):
        actor(actor), story(story), acting_skill(acting_skill)
    {
        strcpy(name, _name);
    }
    int operator<(const TV_Drama &a) const
    {
        return actor > a.actor;
    }
};
class Printer_class{
    public:
        void operator()(const TV_Drama &a)
        {
            std::cout << a.name << ";";
        }
};
Printer_class Printer;
int comparator_1(const TV_Drama &a, const TV_Drama &b)
{
    return a.story > b.story;
}
class comparator_2{
    public:
        int operator()(const TV_Drama &a, const TV_Drama &b)
        {
            return a.acting_skill > b.acting_skill;
        }
};
int main(){
	list<TV_Drama> lst;
	int n;
	
	cin>>n;
	char  _name[100];
	int _actor, _story, _acting_skill;
	for (int i=0; i<n; i++){
        cin.ignore();
        cin.getline(_name,100);
        cin>>_actor>>_story>>_acting_skill;
		lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
	}

	lst.sort();
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_1);
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	lst.sort(comparator_2());
	for_each(lst.begin(), lst.end(), Printer);	
	cout<<endl;

	return 0;
}