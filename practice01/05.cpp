#include <iostream>
#include <string>
using namespace std;
template <class T, int n>
class A
{
    T* arr;
    public:
        A(T* x)
        {
            arr = new T[n];
            for (int i = 0; i < n; i++)
                arr[i] = x[i];
        }
        T& operator[](int index)
        {
            return arr[index];
        }
        T sum()
        {
            T tmp = arr[0];
            for (int i = 1; i < n; i++)
                tmp += arr[i];
            return tmp;
        }
};
int main() {
	
	int t;
	cin >> t;
	while( t -- ) { 
	    int b1[10];
	    for(int i = 0;i < 10; ++i) 	
	
	    	cin >> b1[i];
	    A<int, 10> a1 = b1;
	    cout << a1[2] << endl;
	    
	
	    double b2[5] ;
	    for(int i = 0;i < 5; ++i) 	
	    	cin >> b2[i];
	    
	    A<double, 5> a2 = b2;
	    cout << a2.sum() << endl;
	
		
	    string b3[4] ;
	    for(int i = 0;i < 4; ++i) 	
	    	cin >> b3[i];
	    
	    A<string, 4> a3 = b3;
	    cout << a3.sum() << endl;
	}
	return 0;
}