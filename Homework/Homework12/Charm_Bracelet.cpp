#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int MAXN = 3405;
constexpr int MAXM = 12885;
int dp[MAXM], n, m, d[MAXN], w[MAXN];

int main() {
	//0-1背包模板题
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &w[i], &d[i]);
	for (int i = 1; i <= n; i++)
		for (int j = m; j >=w[i]; j--) {
			dp[j] = max(dp[j], dp[j - w[i]] + d[i]);
		}
	printf("%d", dp[m]);
	return 0;
}