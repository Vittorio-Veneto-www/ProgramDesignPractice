#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
class A
{
    public:
        A()
        {
            printf("New A\n");
        }
        virtual ~A()
        {
            printf("Delete A\n");
        }
};
class B:public A
{
    public:
        B():A()
        {
            printf("New B\n");
        }
        ~B()
        {
            printf("Delete B\n");
        }
};
int main(){
	int n;
	cin >> n;
	for (int i = 1; i<=n; i++) {
		int x;
		cin >> x;
		if (x == 0) {
			A *a = new A();
			delete a;
		}else {
			A *a = new B();
			delete a;
		}
	}
	return 0;	
}