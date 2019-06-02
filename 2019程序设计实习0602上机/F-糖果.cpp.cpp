#include<cstdio>
#include<cstring>
int n, k, dp[105][105], candy[105];
//dp[i][m]前i个物品使得value%k==m的最大数量
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &candy[i]);
	memset(dp, -20, sizeof(dp));
	for (int i = 0; i <= n; i++)
		dp[i][0] = 0;
	return 0;
}