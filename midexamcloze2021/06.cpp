#include<iostream>
using namespace std;

class Midterm {
private:
  int val; 
public:
	Midterm(int x = 0)
	{
		val = x;
	}
	int operator+(int x)
	{
		return val + x;
	}
	int operator++(int x)
	{
		return ++val;
	}
	Midterm& operator-=(int x)
	{
		val -= x;
		return *this;
	}
	operator int()
	{
		return val;
	}
	friend ostream& operator<<(ostream &os, const Midterm &x)
	{
		os << x.val;
		return os;
	}
};

int Min(int a,int b) {
  if(a < b)
    return a;
  else
    return b;
}
int main(){
  Midterm a; 
  cout << a << endl;
  cout << a + 2021 << endl;
  Midterm b(1000);
  cout << b ++ << endl; 
  ((b-=10)-=20)-=30;
  cout << b ++ << endl; 
  cout << Min(255,b) <<endl;
  return 0;
}
