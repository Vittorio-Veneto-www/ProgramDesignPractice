#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Mat{
	int h,w;
public:
	Mat(int height,int width):h(height),w(width)
    {}
    vector<vector<int> > mat;
    int createTime;
    static int matCount;
    friend istream& operator>>(istream &is, Mat &x)
    {
        int x1;
        for (int i = 0; i < x.h; i++)
        {
            x.mat.push_back(vector<int>());
            for (int j = 0; j <x. w; j++)
            {
                cin >> x1;
                x.mat[i].push_back(x1);
            }
        }
        x.createTime = matCount;
        matCount++;
        return is;
    }
    friend ostream& operator<<(ostream &os, const Mat &x)
    {
        for (int i = 0; i < x.h; i++)
        {
            for (int j = 0; j < x.w; j++)
                os << x.mat[i][j] << " ";
            os << endl;
        }
        return os;
    }
    int operator<(const Mat &x) const
    {
        return (h * w < x.h * x.w) || (h * w == x.h * x.w && createTime > x.createTime);
    }
    int H() const
    {
        return h;
    }
    int W() const
    {
        return w;
    }
};
int Mat::matCount = 0;
int comparator_1(const Mat &x, const Mat &y)
{
    int x1 = 0;
    for (int i = 0; i < x.H(); i++)
        for (int j = 0; j < x.W(); j++)
            x1 += x.mat[i][j];
    int y1 = 0;
    for (int i = 0; i < y.H(); i++)
        for (int j = 0; j < y.W(); j++)
            y1 += y.mat[i][j];
    return (x1 < y1) || (x1 == y1 && x.createTime > y.createTime);
}
class comparator_2
{
    public:
        int operator()(const Mat &x, const Mat &y)
        {
            return x.createTime < y.createTime;
        }
};
int main()
{
	vector<Mat> m;
	m.push_back(Mat(2,2));
	m.push_back(Mat(3,4));
	m.push_back(Mat(2,2));
	cin >> m[0] >> m[1] >> m[2];
	sort(m.begin(),m.end());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_1);
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	cout<<"*************"<<endl;
	sort(m.begin(),m.end(),comparator_2());
	cout<< m[0] << endl << m[1] << endl << m[2] <<endl;
	return 0;
}