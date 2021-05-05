#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;
class MyClass {	
public:
  int n;
  MyClass(int m):n(m) { }
	void f() { cout << n << " func." << endl; }
};
class MyAny
{
    public:
        int type;
        void* src;
        MyAny(const int &x)
        {
            type = 0;
            src = new int;
            *(int*)src = x;
        }
        MyAny(const string &x)
        {
            type = 1;
            src = new string;
            *(string*)src = x;
        }
        MyAny(const MyClass &x)
        {
            type = 2;
            src = new MyClass(x.n);
        }
        MyAny(const MyAny &x)
        {
            type = x.type;
            switch (type)
            {
                case 0: src = new int;*(int*)src = *(int*)(x.src);break;
                case 1: src = new string;*(string*)src = *(string*)(x.src);break;
                case 2: src = new MyClass(((MyClass*)(x.src))->n);break;
            }
        }
        void del()
        {
            switch (type)
            {
                case 0: delete (int*)src;break;
                case 1: delete (string*)src;break;
                case 2: delete (MyClass*)src;break;
            }
        }
        ~MyAny()
        {
            del();
        }
        MyAny& operator=(const int &x)
        {
            del();
            type = 0;
            src = new int;
            *(int*)src = x;
            return *this;
        }
        MyAny& operator=(const string &x)
        {
            del();
            type = 1;
            src = new string;
            *(string*)src = x;
            return *this;
        }
        MyAny& operator=(const MyClass &x)
        {
            del();
            type = 2;
            src = new MyClass(x.n);
            return *this;
        }
        MyAny& operator=(const MyAny &x)
        {
            del();
            type = x.type;
            switch (type)
            {
                case 0: src = new int;*(int*)src = *(int*)(x.src);break;
                case 1: src = new string;*(string*)src = *(string*)(x.src);break;
                case 2: src = new MyClass(((MyClass*)(x.src))->n);break;
            }
            return *this;
        }
};
template <class T>
T MyAny_cast(MyAny &x)
{
    return *(T*)(x.src);
}
template <class T>
T* MyAny_cast(MyAny* x)
{
    if (typeid(T).name()[0] == 'i' && x->type != 0)
        return NULL;
    if (typeid(T).name()[0] == 's' && x->type != 1)
        return NULL;
    return (T*)(x->src);
}
int main() 
{
	while(true) {
		int n;
		string s;
		cin >>  n >> s;
		if ( n == 0)
			break;
		MyAny a = n;
	 	cout << MyAny_cast<int>(a) << endl;
		a = s;
		cout << MyAny_cast<string>(a) << endl;
		a = MyClass(n+1);
		MyAny b = n + 2;
		MyAny * p = new MyAny(MyClass(n+3));
		MyAny c = MyClass(n+4);
	 	c = * p;
	  	b = * p;
		delete p;
		MyAny d = b;
		MyAny_cast<MyClass>(&a)->f();
		MyAny_cast<MyClass>(&b)->f();	
		MyAny_cast<MyClass>(&c)->f();	
		MyAny_cast<MyClass>(&d)->f();		
		c = s + "OK";
		cout << MyAny_cast<string>(c) << endl;	
		int * pi = MyAny_cast<int> ( & c);
		if( pi == NULL)
			cout << "not a int" << endl;
		else
			cout << "the int is " << * pi << endl;
		string * ps = MyAny_cast<string> ( & c);
		if( ps == NULL)
			cout << "not a string" << endl;
		else
			cout << "the string is " << * ps << endl;
	}
}