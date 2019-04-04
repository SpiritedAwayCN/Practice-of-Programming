#include<cstdio>
#include<queue>
using namespace std;
inline int count_prime(int num) {
	bool flag = true;
	int d = 2, cnt = 0;
	while (d <= num / d) {
		if (num%d) {
			d++;
			flag = true;
		}
		else {
			num /= d;
			if (flag) cnt++;
			flag = false;
		}
	}
	if (cnt && num != d) cnt++;
	return cnt;
}
struct my_int {
	int num;
	my_int(int _num) :num(_num) {}
	operator int() {
		return num;
	}
	bool operator<(const my_int b) const {
		int num1 = count_prime(num);
		int num2 = count_prime(b.num);
		if (num1 != num2) return num1 < num2;
		return num < b.num;
	}
	bool operator>(const my_int b) const {
		int num1 = count_prime(num);
		int num2 = count_prime(b.num);
		if (num1 != num2) return num1 > num2;
		return num > b.num;
	}
};

priority_queue<my_int, vector<my_int>, greater<my_int>> number_gra;
priority_queue<my_int, vector<my_int>, less<my_int>> number_les;

int main() {
	int n, temp;
	scanf("%d", &n);
	while (n--) {
		for (int i = 1; i <= 10; i++) {
			scanf("%d", &temp);
			number_gra.push(my_int(temp));
			number_les.push(my_int(temp));
		}
		printf("%d %d\n", number_les.top(), number_gra.top());
		number_les.pop();
		number_gra.pop();
	}
	return 0;
}