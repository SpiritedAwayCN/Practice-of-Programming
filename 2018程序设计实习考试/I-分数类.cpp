#include <iostream>
using namespace std;
int gcd(int x, int y) {
	return x % y == 0 ? y : gcd(y, x%y);
}
class Fraction
{
	int num, den;
public:
	// 在此处补充你的代码
	Fraction(int _x, int _y = 1):num(_x),den(_y){
		if (num*den < 0 && den < 0) {
			num *= -1;
			den *= -1;
		}
		else if (num*den > 0 && num < 0) {
			num *= -1;
			den *= -1;
		}
		int fac = gcd((num < 0 ? -num : num), den);
		num /= fac;
		den /= fac;
	}
	friend ostream& operator<<(ostream& ost, const Fraction& A) {
		ost << A.num;
		if(A.den != 1)
			ost << '/' << A.den;
		return ost;
	}
	Fraction& operator*=(const Fraction& A) {
		*this = Fraction(num*A.num, den*A.den);
		return *this;
	}
	Fraction& operator/=(const Fraction& A) {
		*this = Fraction(num*A.den, den*A.num);
		return *this;
	}
	Fraction operator * (const Fraction& A) {
		return Fraction(num*A.num, den*A.den);
	}
	Fraction operator / (const Fraction& A) {
		return Fraction(num*A.den, den*A.num);
	}
	operator float() {
		return num * 1.0 / den;
	}
};

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	Fraction f(a, b), g(c);
	f *= g;
	cout << f << endl;
	f /= g;
	cout << f << endl;
	f = f * f;
	cout << f << endl;
	f = f / g;
	cout << f << endl;
	cout << (float)f << endl;
	return 0;
}