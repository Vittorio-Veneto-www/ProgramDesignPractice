#include <iostream>
#include <string>
using namespace std;
template <class T> 
class container{
    T content;
    public:
        container(T content):content(content){}
        container operator+(const container &x)
        {
            return container(content + x.content + x.content);
        }
        container operator+(const T &x)
        {
            return container(content + x);
        }
        friend ostream& operator<<(ostream &os, const container &x)
        {
            os << x.content;
            return os;
        }
};
int main(){
	int n,m;
	cin >> n >> m;
	string s1,s2;
	cin >> s1 >> s2;
    container <int> a = n;
    container <int> b = m;
    cout<<a+b<<endl;
    cout<<a+m<<endl;
    container <string> sa = string(s1);
    container <string> sb = string(s2);
    cout<<sa+sb<<endl;
    cout<< sa + s2<<endl;
}