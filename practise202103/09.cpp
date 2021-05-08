#include <iostream>
using namespace std;
int gcd(int x, int y){
	return x%y==0?y:gcd(y,x%y);
}
class Fraction
{
    int num, den;
public:
    Fraction(int num, int den):num(num), den(den){}
    Fraction(int num):num(num), den(1){}
    void operator*=(Fraction &x)
    {
        num *= x.num;
        den *= x.den;
        int g = gcd(num, den);
        num /= g;
        den /= g;
    }
    void operator/=(Fraction &x)
    {
        int a = x.den, b = x.num;
        num *= a;
        den *= b;
        int g = gcd(num, den);
        num /= g;
        den /= g;
    }
    Fraction& operator=(Fraction x)
    {
        num = x.num;
        den = x.den;
        int g = gcd(num, den);
        num /= g;
        den /= g;
        return *this;
    }
    Fraction operator*(Fraction &x)
    {
        Fraction tmp(1);
        tmp = *this;
        tmp *= x;
        return tmp;
    }
    Fraction operator/(Fraction &x)
    {
        Fraction tmp(1);
        tmp = *this;
        tmp /= x;
        return tmp;
    }
    friend ostream& operator<<(ostream &os, const Fraction &x)
    {
        os << x.num << "/" << x.den;
        return os;
    }
    operator float()
    {
        return (float)num / den;
    }
};
 
int main() {
	int a,b,c;
	cin >> a >> b >> c;
    Fraction f(a, b), g(c);
	f *= g;
	cout << f << endl;
	f /= g;
	cout << f << endl;
	f = f * f;
	cout << f << endl;
	f = f / g;
	cout << f << endl;
	cout << (float) f << endl;
    return 0;
}