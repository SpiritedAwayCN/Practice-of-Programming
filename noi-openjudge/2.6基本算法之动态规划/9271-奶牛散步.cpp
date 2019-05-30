#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 1005; 
/*
// 高精度版本
class GreatNumber {
private:
	short num[400];
	short bit;
public:
	GreatNumber& operator=(int number){
		bit = 0;
		memset(num, 0, sizeof(num));
		while (number) {
			num[bit++] = number % 10;
			number /= 10;
		}
		return *this;
	}
	GreatNumber operator+(const GreatNumber& B) {
		GreatNumber ans;
		ans.bit = max(bit,B.bit);
		memset(ans.num, 0, sizeof(ans.num));
		int carry = 0;
		for (int i = 0; i < ans.bit; i++) {
			ans.num[i] = num[i] + B.num[i] + carry;
			carry = ans.num[i] / 10;
			ans.num[i] %= 10;
		}
		if (carry) ans.num[ans.bit++] = carry;
		return ans;
	}
	friend ostream& operator<<(ostream& ost, const GreatNumber& B) {
		if (B.bit == 0) {
			ost << 0;
			return ost;
		}
		for (int i = 0; i < B.bit; i++)
			ost << B.num[i];
		return ost;
	}
}dp[MAXN][3];
*/

//取模版本
constexpr int MOD = 12345;
int dp[MAXN][3];
int main() {
	int n;
	scanf("%d", &n);
	dp[1][0] = dp[1][1] = dp[1][2] = 1;
	for (int i = 2; i <= n; i++) {
		dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2])%MOD;
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][1])%MOD;
		dp[i][2] = (dp[i - 1][0] + dp[i - 1][2])%MOD;
	}
	cout << (dp[n][0] + dp[n][1] + dp[n][2])%MOD << endl;
	return 0;
}