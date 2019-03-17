#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int init = 123):val(init){}
    A& GetObj(){
        return *this;
    }
    void operator=(const A& a){
        val = a.val;
    }
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}
