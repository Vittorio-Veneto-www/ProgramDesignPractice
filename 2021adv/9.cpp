#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
template<class T>
class Array{
	public:
	virtual Array* operator [] (int K){};
	virtual operator T(){};
};
template <class T, int n>
class DArray:public Array<T>
{
    T* ptr;
	vector<int> size;
    public:
        DArray(vector<int> &_size, T* _ptr = NULL):size(_size), ptr(_ptr)
        {
			if (ptr)
				size.erase(size.begin());
			else
			{
				int cnt = 1;
				for_each(size.begin(), size.end(), [&](int x){cnt *= x;});
				ptr = new T[cnt];
			}
        }
        ~DArray()
        {
			if (size.size() == n)
				delete [] ptr;
        }
		void init()
		{
			int cnt = 1;
			for_each(size.begin(), size.end(), [&](int x){cnt *= x;});
			for (int i = 0; i < cnt; i++)
				cin >> *(ptr + i);
		}
        DArray* operator[](int index)
        {
			int cnt = index;
			for_each(size.begin() + 1, size.end(), [&](int x){cnt *= x;});
            return new DArray(size, ptr + cnt);
        }
		operator T()
		{
			return *ptr;
		}
};
int main(){
	ios::sync_with_stdio(false); //主要是加快 cin 和 cout的速度 
	int n=5,q; vector<int>size;
	for (int i=1;i<=n;i++){
		int si; 
		cin>>si; size.push_back(si);
		//读入五维数组每一维的大小放入vector si中 
	}
	DArray<int,5> A(size);
	A.init(); cin>>q;
	//对五维数组的访问次数 
	for (int i=1;i<=q;i++){
		Array<int>*K=&A;
		//每一次访问输入 5 个数表示访问位置的下标 
		for (int j=1;j<=n;j++){
			int x; cin>>x; K=(*K)[x];
		}
		cout<<(*K)<<endl;
	}
	
	n=10; size.clear();
	for (int i=1;i<=n;i++){
		int si; cin>>si; size.push_back(si);
		//读入十维数组每一维的大小放入vector si中 
	}
	DArray<double,10> B(size);
	B.init(); cin>>q;
	//对十维数组的访问次数 
	for (int i=1;i<=q;i++){
		Array<double>*K=&B;
		//每一次访问输入 10 个数表示访问位置的下标 
		for (int j=1;j<=n;j++){
			int x; cin>>x; K=(*K)[x];
		}
		cout<<(*K)<<endl;
	}
}