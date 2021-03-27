#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class MyString:public string
{
    //正确方法
    /*
    public:
        MyString(const char *x)
        {
            this->assign(x);
        }
        MyString()
        {
        }
        MyString & operator= (const char *x)
        {
            this->assign(x);
            return *this;
        }
        MyString & operator= (const string &x)
        {
            if (this == &x)
                return *this;
            this->assign(x);
            return *this;
        }
        string operator() (int x, int y)
        {
            return this->substr(x, y);
        }
    */
    //未曾设想的方法（其实是没看提示直接做了）
    int strlen(const char * s) 
    {	int i = 0;
        for(; s[i]; ++i);
        return i;
    }
    void strcpy(char * d,const char * s)
    {
        int i = 0;
        for( i = 0; s[i]; ++i)
            d[i] = s[i];
        d[i] = 0;
            
    }
    void strcpy(char * d,string s)
    {
        int i = 0;
        for( i = 0; s[i]; ++i)
            d[i] = s[i];
        d[i] = 0;
            
    }
    int strcmp(const char * s1,const char * s2)
    {
        for(int i = 0; s1[i] && s2[i] ; ++i) {
            if( s1[i] < s2[i] )
                return -1;
            else if( s1[i] > s2[i])
                return 1;
        }
        return 0;
    }
    void strcat(char * d,const char * s)
    {
        int len = strlen(d);
        strcpy(d+len,s);
    }
    char *s = NULL;
    public:
        MyString(const char *x)
        {
            s = new char[strlen(x) + 1];
            strcpy(s, x);
        }
        MyString(string x)
        {
            s = new char[x.length() + 1];
            strcpy(s, x);
        }
        MyString()
        {
            s = new char[1];
            strcpy(s, "");
        }
        ~MyString()
        {
            delete [] s;
        }
        MyString(const MyString &x)
        {
            if (s)
                delete [] s;
            s = new char[strlen(x.s) + 1];
            strcpy(s, x.s);
        }
        friend ostream & operator<< (ostream & os, const MyString &x)
        {
            os << x.s;
            return os;
        }
        MyString & operator= (const MyString &x)
        {
            if (this == &x)
                return *this;
            delete [] s;
            s = new char[strlen(x.s) + 1];
            strcpy(s, x.s);
            return *this;
        }
        void operator+= (const MyString &x)
        {
            char *tmp;
            tmp = new char[strlen(s) + strlen(x.s) + 1];
            strcpy(tmp, s);
            strcat(tmp, x.s);
            delete [] s;
            s = new char[strlen(tmp) + 1];
            strcpy(s, tmp);
            delete [] tmp;
        }
        MyString operator+ (const MyString &x)
        {
            MyString tmp(s);
            tmp += x;
            return tmp;
        }
        MyString operator+ (const char *ch)
        {
            MyString tmp(*this), tmp1(ch);
            tmp += tmp1;
            return tmp;
        }
        friend MyString operator+ (const char *ch, const MyString &x)
        {
            MyString tmp(ch);
            tmp += x;
            return tmp;
        }
        int operator> (const MyString &x)
        {
            return strcmp(s, x.s) == 1;
        }
        int operator== (const MyString &x)
        {
            return strcmp(s, x.s) == 0;
        }
        int operator< (const MyString &x)
        {
            return strcmp(s, x.s) == -1;
        }
        char & operator[] (int x)
        {
            return s[x];
        }
        MyString operator() (int x, int y)
        {
            char *ch;
            ch = new char[y + 1];
            for (int i = 0; i < y; i++)
                ch[i] = s[x + i];
            ch[y] = '\0';
            MyString tmp(ch);
            delete [] ch;
            return tmp;
        }
};


int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
    sort(SArray,SArray+4);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}