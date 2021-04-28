#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}
    class manipulator
    {
        int i;
        MyBitset* s;
        public:
            manipulator(int i, MyBitset* s):i(i), s(s){}
            int toint() const
            {
                return s->a[i/8] & 1 << i % 8 ? 1 : 0;
            }
            void operator=(int v)
            {
                s->Set(i, v);
            }
            const manipulator& operator=(const manipulator &x) const
            {
                s->Set(i, x.toint());
                return *this;
            }
            friend ostream& operator<<(ostream &os, const manipulator &x)
            {
                os << x.toint();
                return os;
            }
    };
    manipulator operator[](int index)
    {
        return manipulator(index, this);
    }
void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}