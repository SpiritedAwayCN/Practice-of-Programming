#include <iostream>
#include <cmath>
using namespace std;
class Complex {
private:
     double r, i;
public:
    Complex(double x=0,double y=0)
    : r(x)
    , i(y){}
     // YOUR CODE HERE
     friend ostream& operator << (ostream& ost, Complex& A){
        ost<< A.r<<" + "<<A.i<<"i\n";
        return ost;
     }
     Complex operator+(Complex& numb2){
        return Complex(r+numb2.r,i+numb2.i);
     }
     operator double(){
         return r*r+i*i;
     }
};
int main() {
    Complex a(1.2), b(2.0, 1.6), c;
    cout << a << b << c;
    c = a + b;
    float mod = float(c);
    cout << c << mod;  // ¼ÆËãÄ£³¤
    return 0;
}
