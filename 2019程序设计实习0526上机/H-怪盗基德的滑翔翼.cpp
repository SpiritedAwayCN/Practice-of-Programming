#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 105;
int dp1[MAXN], h[MAXN], dp2[MAXN];
int main() {
	//注意是选定起点后，再找左和右的最大值
	int k, n;
	scanf("%d", &k);
	while (k--) {
		memset(dp1, 0, sizeof(dp1));
		memset(dp2, 0, sizeof(dp2));
		memset(h, 0, sizeof(h));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &h[i]);
		dp1[1] = 1;
		for (int i = 2; i <= n; i++) {
			dp1[i] = 1;
			for (int j = 1; j < i; j++) {
				if (h[i] < h[j])
					dp1[i] = max(dp1[i], dp1[j] + 1);
			}
		}
		dp2[n] = 1;
		for (int i = n - 1; i >= 1; i--) {
			dp2[i] = 1;
			for (int j = n; j > i; j--) {
				if (h[i] < h[j])
					dp2[i] = max(dp2[i], dp2[j] + 1);
			}
		}
		int ans = -1;
		for (int i = 1; i <= n; i++) {
			ans = max(ans, dp1[i]);
			ans = max(ans, dp2[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}