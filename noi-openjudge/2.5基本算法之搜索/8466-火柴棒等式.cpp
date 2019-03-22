#include<iostream>
//×¢Òâ£º¼«¶Ë±©Á¦
const int match[10] = { 6,2,5,5,4,5,6,3,7,6 };
using namespace std;
int count_match(int number) {
	if (number == 0) return match[0];
	int sum = 0;
	while (number) {
		sum += match[number % 10];
		number /= 10;
	}
	return sum;
}
int main() {
	int n;
	cin >> n;
	n -= 4;
	if (n <= 6) {
		cout << 0 << endl;
		return 0;
	}
	int ans = 0;
	for (int i = 0; i <= 999; i++)
		for (int j = i; j <= 999; j++) {
			if (count_match(i) + count_match(j) + count_match(i + j) == n) {
				//cout << i << " + " << j << " = " << i + j << endl;
				ans++;
				if (i != j) ans++;
			}
		}
	cout << ans;
	return 0;
}