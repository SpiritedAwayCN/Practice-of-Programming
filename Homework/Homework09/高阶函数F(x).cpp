#include <iostream>
using namespace std;
// 在此处补充你的代码
#include<string>
template<class T1, class T2>
class f {
public:
	T1 value;
	f(T1 _v):value(_v){}
	T2 operator()(const T2& num) const {
		return num + value;
	}
};


int main()
{
	cout << f<int, int>(7)(9) << endl;   //16
	cout << f<string, string>(" hello!")("world") << endl; // world hello!
	cout << f<char, string>('!')("world") << endl;


	return 0;    //world!
}