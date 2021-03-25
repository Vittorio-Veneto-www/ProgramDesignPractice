#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
    friend istream & operator>> (istream & is, Point &x)
    {
        is >> x.x >> x.y;
        return is;
    }
    friend ostream & operator<< (ostream & os, const Point &x)
    {
        os << x.x << "," << x.y;
        return os;
    }
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}