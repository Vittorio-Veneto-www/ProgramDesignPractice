#include <iostream>
using namespace std;
class Complex
{
    int real, img;
    public:
        Complex()
        {
            real = 0;
            img = 0;
        }
        Complex(const char* str)
        {
            real = str[0] - '0';
            img = str[2] - '0';
        }
        Complex(const Complex &x)
        {
            real = x.real;
            img = x.img;
        }
        Complex(const int x)
        {
            real = x;
            img = 0;
        }
        Complex& operator+=(const Complex &x)
        {
            real += x.real;
            img += x.img;
            return *this;
        }
        Complex& operator-=(const Complex &x)
        {
            real -= x.real;
            img -= x.img;
            return *this;
        }
        Complex& operator*=(const Complex &x)
        {
            Complex tmp(x);
            int a = real, b = img;
            real = a * tmp.real - b * tmp.img;
            img = a * tmp.img + b * tmp.real;
            return *this;
        }
        Complex operator+(const Complex &x)
        {
            Complex tmp = *this;
            tmp += x;
            return tmp;
        }
        Complex operator-(const Complex &x)
        {
            Complex tmp = *this;
            tmp -= x;
            return tmp;
        }
        Complex operator*(const Complex &x)
        {
            Complex tmp = *this;
            tmp *= x;
            return tmp;
        }
        friend ostream& operator<<(ostream &os, const Complex &x)
        {
            if (x.img)
                if (x.real)
                    if (x.img > 0)
                        os << x.real << "+" << x.img << "i";
                    else
                        os << x.real << "-" << x.img << "i";
                else
                    os << x.img << "i";
            else
                os << x.real;
            return os;
        }
};
int main() {
	Complex c1;
	Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}