#include <iostream>
#include <cmath>
using namespace std;

class Vector {
    int dim, *components;
    public:
        Vector(int dim):dim(dim)
        {
            components = new int[dim];
            for (int i = 0; i < dim; i++)
                components[i] = 0;
        }
        Vector(const Vector &x):dim(x.dim)
        {
            components = new int[dim];
            for (int i = 0; i < dim; i++)
                components[i] = x.components[i];
        }
        ~Vector()
        {
            delete [] components;
        }
        friend istream& operator>>(istream &is, Vector &x)
        {
            for (int i = 0; i < x.dim; i++)
                is >> x.components[i];
            return is;
        }
        friend ostream& operator<<(ostream &os, const Vector &x)
        {
            os << x.components[0];
            for (int i = 1; i < x.dim; i++)
                os << "," << x.components[i];
            return os;
        }
        friend ostream& operator<<(ostream &&os, const Vector &x)
        {
            os << x.components[0];
            for (int i = 1; i < x.dim; i++)
                os << x.components[i];
            return os;
        }
        Vector& operator+=(const Vector &x)
        {
            for (int i = 0; i < dim; i++)
                components[i] += x.components[i];
            return *this;
        }
        Vector operator+(const Vector &x)
        {
            Vector tmp(*this);
            tmp += x;
            return tmp;
        }
        Vector operator*(const int &x)
        {
            Vector tmp(dim);
            for (int i = 0; i < dim; i++)
                tmp.components[i] = components[i] * x;
            return tmp;
        }
        double mo()
        {
            double x = 0;
            for (int i = 0; i < dim; i++)
                x += components[i] * components[i];
            return sqrt(x);
        }
        int operator[](int index)
        {
            return components[index];
        }
};

int main() {
    int n, m, c;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        Vector a(m), b(m);
        cin >> a >> b >> c;
        a += b;
        Vector d(b * c);
        cout << a + d << endl;
        cout << d * c << endl;
        cout << b.mo() << endl;
        cout << a[0] << endl;
        cout << endl;
    } return 0;
}