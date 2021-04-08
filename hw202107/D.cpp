#include <iostream>
using namespace std;
class MyCin
{
    int stop = 1;
    public:
        MyCin &operator>>(int &x)
        {
            if (!stop)
                return *this;
            int temp;
            std::cin >> temp;
            if (temp == -1)
                stop = 0;
            else
                x = temp;
            return *this;
        }
        explicit operator bool()
        {
            return stop;
        }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}