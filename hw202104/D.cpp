#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
    public:
        int n, m, **value, val;
        Array2(int x1 = 0, int x2 = 0)
        {
            n = x1, m = x2;
            value = NULL;
            if (x1)
            {
                value = new int*[n];
                for (int i = 0; i < n; i++)
                    if (x2)
                        value[i] = new int[m];
                    else
                        value[i] = NULL;
            }
        }
        ~Array2()
        {
            if (value)
            {
                for (int i = 0; i < n; i++)
                    delete [] value[i];
                delete [] value;
            }
        }
        int a(int x1, int x2)
        {
            val = value[x1][x2];
            return val;
        }
        Array2 & operator= (const Array2 &x)
        {
            if (&x == this)
                return *this;
            if (value)
            {
                for (int i = 0; i < n; i++)
                    delete [] value[i];
                delete [] value;
            }
            n = x.n, m = x.m;
            value = new int*[n];
            for (int i = 0; i < n; i++)
            {
                value[i] = new int[m];
                for (int j = 0; j < m; j++)
                    value[i][j] = x.value[i][j];
            }
            return *this;
        }
        int* operator[] (int x)
        {
            return value[x];
        }
        int operator() (int x, int y)
        {
            return value[x][y];
        }
        friend ostream & operator<< (ostream & os, const Array2 &x)
        {
            os << x.val;
            return os;
        }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}