#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
class GreatInt {
private:
	short number[50];
	short bit;
public:
	GreatInt():bit(0) {
		memset(number, 0, sizeof(number));
	}
	GreatInt(int _num):bit(0) {
		memset(number, 0, sizeof(number));
		while (_num) {
			number[bit++] = _num % 10;
			_num /= 10;
		}
	}
	//有按位拷贝，不写了
	GreatInt(const char* ch, int s, int t):bit(t-s) {
		memset(number, 0, sizeof(number));
		for (int i = 0; i < bit; i++) {
			number[i] = ch[t - 1 - i] - '0';
		}
	}
	GreatInt operator+(const GreatInt& B) {
		GreatInt ans;
		ans.bit = B.bit > bit ? B.bit : bit;
		int carry = 0;
		for (int i = 0; i < ans.bit; i++) {
			ans.number[i] = (number[i] + B.number[i] + carry) % 10;
			carry = (number[i] + B.number[i] + carry) / 10;
		}
		if (carry > 0) ans.number[ans.bit++] = 1;
		return ans;
	}
	friend ostream& operator<<(ostream& ost, const GreatInt& B) {
		if (B.bit == 0) {
			ost << 0;
			return ost;
		}
		for (int i = B.bit - 1; i >= 0; i--)
			ost << B.number[i];
		return ost;
	}
	bool operator < (const GreatInt& B) const {
		if (bit != B.bit) return bit < B.bit;
		for (int i = bit - 1; i >= 0; i--) {
			if (number[i] != B.number[i])
				return number[i] < B.number[i];
		}
		return false;
	}
};
constexpr int MAXM = 51;
GreatInt dp[MAXM][MAXM];

int main(){
	int m, len;
	char str[55];
	while (cin >> m) {
		cin >> str;
		len = strlen(str);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= len; i++)
			dp[i][0] = GreatInt(str, 0, i);
		for (int i = 1; i <= len; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 1; k < i; k++) {
					if (k == 1)
						dp[i][j] = dp[i - k][j - 1] + GreatInt(str, i - k, i);
					else
						dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + GreatInt(str, i - k, i));
				}
			}
		}
		cout << dp[len][m] << endl;
	}
	return 0;
}