#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 105, MAXM = 1000005;
int m[MAXN], p[MAXN], dp[MAXM], n, k;
//明显有O(T*n^2)的算法我偏偏用了O(T*n*m),我太菜了
//#define scanf scanf_s
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", &m[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &p[i]);
		memset(dp, 0, sizeof(dp));
		int index = 1, i;
		for (i = 1; m[i] <= k && i <= n; i++) {
			while (index < m[i]) {
				dp[index + 1] = dp[index];
				index++;
			}
			dp[index] = max(dp[index - 1], p[i]);
		}

		for (; i <= n; i++) {
			while (index < m[i]) {
				dp[index + 1] = dp[index];
				index++;
			}
			dp[index] = max(dp[index - k - 1] + p[i], dp[index - 1]);
		}
		printf("%d\n", dp[m[n]]);
	}

	return 0;
}