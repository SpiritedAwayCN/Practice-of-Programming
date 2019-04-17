#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
template<class T>
class Print {
public:
	Print(int _size):size_tot(_size){}
	T operator + (const T& A){
		cout << A;
		size_tot--;
		if (!size_tot)
			cout << endl;
		return temp;
	}
	T& operator=(const T& A) {
		temp = A;
		return temp;
	}
private:
	T temp;
	int size_tot;
};

int main() {
	string s[20];
	int num[20];
	int m, n;

	while (cin >> m >> n) {
		for (int i = 0; i<m; i++) {
			cin >> s[i];
		}
		accumulate(s, s + m, Print<string>(m));
		for (int i = 0; i<n; i++) {
			cin >> num[i];
		}
		accumulate(num, num + n, Print<int>(n));
	}
}