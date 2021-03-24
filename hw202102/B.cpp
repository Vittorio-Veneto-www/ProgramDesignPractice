#include <iostream>
using namespace std;
class Sample {
public:
	int v;
    Sample(int x = 0)
    {
        v = x;
    }
    Sample(const Sample & x)
    {
        if (x.v == 20)
            v = 22;
        else
            v = 9;
    }
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}