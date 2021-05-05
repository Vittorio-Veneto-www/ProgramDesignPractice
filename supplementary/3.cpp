#include <iostream>

using namespace std;
//#define MySharedPtr shared_ptr

template <class T> 
struct MySharedPtr
{
    MySharedPtr<T> *prev = NULL, *next = NULL;
    T* ptr = NULL;
    MySharedPtr()
    {
    }
    MySharedPtr(T* x)
    {
        ptr = x;
    }
    MySharedPtr(const MySharedPtr<T> &x)
    {
        const MySharedPtr<T>* p = &x;
        MySharedPtr<T>* y = const_cast<MySharedPtr<T>* >(p);
        ptr = y->ptr;
        prev = y;
        next = y->next;
        if (next)
            next->prev = this;
        y->next = this;
    }
    void del()
    {
        if (prev)
            prev->next = next;
        if (next)
            next->prev = prev;
        if (!prev && !next && ptr)
            delete ptr;
        prev = NULL, next = NULL;
    }
    ~MySharedPtr()
    {
        del();
    }
    MySharedPtr& operator=(MySharedPtr<T> &x)
    {
        if (this->ptr == x.ptr)
            return *this;
        del();
        ptr = x.ptr;
        prev = &x;
        next = x.next;
        if (next)
            next->prev = this;
        x.next = this;
        return *this;
    }
    T* operator->()
    {
        return ptr;
    }
    T& operator*()
    {
        return *ptr;
    }
    bool operator!()
    {
        return !ptr;
    }
    T* get()
    {
        return ptr;
    }
    void reset(T* newptr = NULL)
    {
        del();
        ptr = newptr;
    }
};

struct A   {    
 	 int n;
	 A(int v = 0):n(v){ } 
	 ~A() { cout << n << " destructor" << endl; }
};
int main()
{
	MySharedPtr<A> sp1(new A(2)); 
	MySharedPtr<A> sp2(sp1);        
	cout << "1)" << sp1->n  << "," << sp2->n << endl; 
	MySharedPtr<A> sp3;
	A * p = sp1.get();  
	cout << "2)" << p->n << endl;
	sp3 = sp1; 
	cout << "3)" << (*sp3).n << endl;  
	sp1.reset();     
	if( !sp1 )
		cout << "4)sp1 is null" << endl; //会输出 
	A * q = new A(3);
	sp1.reset(q); // 
	cout << "5)" << sp1->n << endl;
	MySharedPtr<A> sp4(sp1); 
	MySharedPtr<A> sp5;
	sp5.reset(new A(8));
	sp1.reset();          
	cout << "before end main" <<endl;
	sp4.reset();          
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}