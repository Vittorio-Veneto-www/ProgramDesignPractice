#include<iostream>
#include<vector>
using namespace std;
class A{
	public:
		int x;
		static int presum;
		A(int x1)
		{
			presum += x1;
			x = presum;
		}
		void output()
		{
			cout << x << endl;
		}
};
int A::presum=0;
int main(){
  int n;cin>>n;
  vector<A*> p;
  for(int i=0;i<n;i++){
    int x;cin>>x;
    p.push_back(new A(x));
  }
  for(int i=0;i<n;i++){
    p[i]->output();
  }
  return 0;
}
