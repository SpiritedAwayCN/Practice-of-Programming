#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 100005;
long long dp[MAXN];
int n, a[MAXN];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		dp[1] = max(0, a[1]);
		for (int i = 2; i <= n; i++)
			dp[i] = max(dp[i - 1], dp[i - 2] + a[i]);
		printf("%lld\n", dp[n]);
	}

	return 0;
}