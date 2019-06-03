#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int MAXT = 1005, MAXM = 105;
int dp[MAXT], T, m, w[MAXM], v[MAXM];

int main() {
	scanf("%d%d", &T, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &w[i], &v[i]);
	for (int i = 1; i <= m; i++)
		for (int j = T; j >= w[i]; j--)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
	printf("%d", dp[T]);
	return 0;
}