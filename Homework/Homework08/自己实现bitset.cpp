#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset
{
	char a[bitNum / 8 + 1];
	MyBitset() { memset(a, 0, sizeof(a)); };
	void Set(int i, int v) {
		char & c = a[i / 8];
		int bp = i % 8;
		if (v)
			c |= (1 << bp);
		else
			c &= ~(1 << bp);
	}
	// 在此处补充你的代码
	class A {
	public:
		A(char *_loc, int _bit) :loc(_loc), bit(_bit) {}
		bool& operator=(bool v) {
			if (v)
				(*loc) |= 1 << bit;
			else
				(*loc) &= ~(1 << bit);
			return v;
		}
		operator bool() const {
			return 1 & ((*loc) >> bit);
		}
		A& operator=(const A& obj) {
			if (this == &obj) return *this;
			*this = bool(obj);
			return *this;
		}
	private:
		char *loc;
		int bit;
	};
	A operator[](int index) {
		return A(a + index / 8, index % 8);
	}
	void Print() {
		for (int i = 0; i < bitNum; ++i)
			cout << (*this)[i];
		cout << endl;
	}
};

int main()
{
	int n;
	int i, j, k, v;
	while (cin >> n) {
		MyBitset<20> bs;
		for (int i = 0; i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t, 1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}