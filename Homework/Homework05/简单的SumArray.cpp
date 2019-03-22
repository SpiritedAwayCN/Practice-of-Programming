#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(
// 在此处补充你的代码
T* d1, T* d2){
    T str = *d1;
    for(T* i = d1 + 1; i!= d2; i++){
        str+=*i;
    }
    return str;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}
