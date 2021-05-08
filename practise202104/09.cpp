#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class IntegralImage{
    int H, W, **integral, cur = 0;
    public:
        IntegralImage(int H, int W):H(H), W(W)
        {
            integral = new int*[H];
            for (int i = 0; i < H; i++)
                integral[i] = new int[W];
        }
        void operator()(int* x)
        {
            int* v = new int[W];
            for (int i = 0; i < W; i++)
            {
                v[i] = x[i];
                if (i)
                    v[i] += v[i - 1];
            }
            for (int i = 0; i < W; i++)
            {
                integral[cur][i] = v[i];
                if (cur)
                    integral[cur][i] += integral[cur - 1][i];
            }
            cur++;
        }
        int* operator[](int index)
        {
            return integral[index];
        }
};
int main(){
    int H, W;
    cin >> H >> W;
    int ** image = new int*[H];
    for(int i=0;i<H;++i){
        image[i]=new int[W];
    }
    for(int i=0;i<H;++i)
    for(int j=0;j<W;++j)
        cin >> image[i][j];
    IntegralImage it(H,W);
    for_each(image, image+H, it);
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j)
            cout<<it[i][j]<<" ";
        cout<<endl;
    }
   
}