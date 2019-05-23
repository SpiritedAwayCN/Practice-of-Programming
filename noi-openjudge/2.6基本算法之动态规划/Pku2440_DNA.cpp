#include<cstdio>
constexpr int MOD = 2005;
constexpr int MAXN = 1000005;
int dp[MAXN][4], pw[200];
//辣鸡版本 dp[l][i] l-长度 i-最后两位的二进制
//最好的递推公式找与i-1的关系，这里找的与的i-2关系
int main() {
	pw[0] = 1;
	for (int i = 1; i < 200; i++) {
		//200是打表结果
		pw[i] = pw[i - 1] << 1;
		pw[i] %= MOD;
	}
	dp[3][1] = dp[3][3] = 1;
	for (int i = 4; i <= 1000000; i++) {
		dp[i][0] = dp[i - 2][0] + dp[i - 2][1] + dp[i - 2][2] + dp[i - 2][3];
		dp[i][0] %= MOD;
		dp[i][1] = dp[i - 2][0] + dp[i - 2][2] + pw[(i - 3) % 200];
		dp[i][1] %= MOD;
		dp[i][2] = dp[i - 2][0] + dp[i - 2][1] + 2 * pw[(i - 4) % 200];
		dp[i][2] %= MOD;
		dp[i][3] = dp[i - 2][0] + 3 * pw[(i - 4) % 200];
		dp[i][3] %= MOD;
	}
	for (int i = 3; i <= 1000000; i++) {
		for (int j = 1; j < 4; j++)
			dp[i][0] += dp[i][j];
		dp[i][0] = pw[i % 200] - dp[i][0];
		dp[i][0] %= MOD;
		if (dp[i][0] < 0)dp[i][0] += MOD;
	}
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%d\n", dp[n][0]);
	}
	return 0;
}