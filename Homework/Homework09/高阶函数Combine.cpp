#include <iostream>
using namespace std;
// 在此处补充你的代码
template<class T1,class T2, class T3>
class combine {
public:
	combine(const T1& _op1, const T2& _op2):
		op1(_op1),
		op2(_op2){}
	T3 operator()(T3 num) {
		T3 value = op1(num) + op2(num);
		return op1(value);
	}
private:
	const T1& op1;
	const T2& op2;
};

int main()
{
	auto Square = [](double a) { return a * a; };
	auto Inc = [](double a) { return a + 1; };
	cout << combine<decltype(Square), decltype(Inc), int>(Square, Inc)(3) << endl;
	cout << combine<decltype(Inc), decltype(Square), double>(Inc, Square)(2.5) << endl;

	return 0;
}