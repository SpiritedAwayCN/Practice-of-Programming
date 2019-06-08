#include<cstdio>
constexpr int MOD = 10000;
int dp[45], n, a[25];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 40; j >= a[i]; j--) {
			dp[j] += dp[j - a[i]];
			//dp[j] %= MOD;
		}
	printf("%d", dp[40]);
	return 0;
}