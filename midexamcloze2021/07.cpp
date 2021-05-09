#include <iostream>
#include <string>
#include <set>
using namespace std;

class Counter{
    int cnt;
public:
    Counter():cnt(0){}
    virtual void push(void*) = 0;
    virtual string name() = 0;
    void inc(){
        ++cnt;
    }
    int number(){
        return cnt;
    }
};

template<class T>
class TCounter: public Counter{
	set<T> s;
	string _name;
	public:
		TCounter(string _name):_name(_name){}
		void push(void* x)
		{
			if (s.find(*((T*)x)) == s.end())
			{
				inc();
				s.insert(*((T*)x));
			}
		}
		string name()
		{
			return _name;
		}
};

Counter* build_counter(string name){
    if (name == "int") return new TCounter<int>("int");
    else return new TCounter<string>("string");
}



int main(){
    int n, m;
    cin >> n >> m;
    Counter *a = build_counter("int"), *b = build_counter("string");
    for (int i = 0; i < n; ++i){
        int x;
        cin >> x;
        a->push(&x);
    }
    for (int i = 0; i < m; ++i){
        string x;
        cin >> x;
        b->push(&x);
    }
    cout << a->name() << ": " << a->number() << endl;
    cout << b->name() << ": " << b->number();
    return 0;
}
