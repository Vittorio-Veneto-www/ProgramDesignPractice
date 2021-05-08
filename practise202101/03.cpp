#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
template <class T, class Pred>
int count_if(T* start, T* end, Pred op)
{
    int x = 0;
    for (;start != end; start++)
        x += op(*start);
    return x;
}
class Pred
{
    int n;
    public:
        Pred(int n): n(n) {}
        int operator()(int x)
        {
            if (x & 1 << n)
                return 1;
            else
                return 0;
        }
};
int main(int argc, char** argv) {	
	int n, x;
	vector<int> intVec;
	cin>>n>>x; 
	while(x) {
		intVec.push_back(x);
		cin>>x;
	}
	cout<<count_if(intVec.begin(), intVec.end(), Pred(n))<<endl;
	return 0;
}