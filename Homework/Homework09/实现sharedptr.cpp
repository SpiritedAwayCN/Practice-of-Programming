#include <iostream>
#include<memory>
using namespace std;
//#define MySharedPtr shared_ptr

template <class T>
struct MySharedPtr
{
	// 在此处补充你的代码
public:
	MySharedPtr():cnt(NULL),obj(NULL){}
	MySharedPtr(T* _obj):cnt(new int(1)),obj(_obj){}
	MySharedPtr(const MySharedPtr& _sp) {
		cnt = _sp.cnt;
		(*cnt)++;
		obj = _sp.obj;
	}
	~MySharedPtr() {
		dec();
	}
	T* operator->() const {
		return obj;
	}
	T& operator*() const {
		return *obj;
	}
	operator bool() {
		return obj != NULL;
	}
	T* get() const {
		return obj;
	}
	void reset() {
		dec();
		cnt = NULL;
		obj = NULL;
	}
	void reset(T* ptr) {
		dec();
		obj = ptr;
		cnt = new int(1);
	}
	MySharedPtr& operator=(const MySharedPtr& _sp) {
		dec();
		obj = _sp.obj;
		cnt = _sp.cnt;
		(*cnt)++;
		return *this;
	}
private:
	int *cnt;
	T* obj;
	void dec() {
		if (!cnt) return;
		(*cnt)--;
		if (*cnt <= 0) {
			delete obj;
			delete cnt;
		}
	}
};

struct A {
	int n;
	A(int v = 0) :n(v) { }
	~A() { cout << n << " destructor" << endl; }
};
int main()
{
	
	MySharedPtr<A> sp1(new A(2));
	MySharedPtr<A> sp2(sp1);
	cout << "1)" << sp1->n << "," << sp2->n << endl;
	MySharedPtr<A> sp3;
	A * p = sp1.get();
	cout << "2)" << p->n << endl;
	sp3 = sp1;
	cout << "3)" << (*sp3).n << endl;
	sp1.reset();
	if (!sp1)
		cout << "4)sp1 is null" << endl; //会输出 
	A * q = new A(3);
	sp1.reset(q); // 
	cout << "5)" << sp1->n << endl;
	MySharedPtr<A> sp4(sp1);
	MySharedPtr<A> sp5;
	sp5.reset(new A(8));
	sp1.reset();
	cout << "before end main" << endl;
	sp4.reset();
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}