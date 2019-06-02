#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 505;
int a1[MAXN], a2[MAXN], anss[MAXN];
int dp[MAXN][MAXN],solution[MAXN][MAXN];
//注：a1的前i个与a2第j个结尾的最长
int main() {
	memset(solution, -1, sizeof(solution));
	int n1, n2;
	scanf("%d", &n1);
	for (int i = 1; i <= n1; i++)
		scanf("%d", &a1[i]);
	scanf("%d", &n2);
	for (int i = 1; i <= n2; i++)
		scanf("%d", &a2[i]);
	for (int i = 1; i <= n1; i++) {
		int v = 0, k = 0;
		for (int j = 1; j <= n2; j++) {
			dp[i][j] = dp[i - 1][j];
			if (a1[i] > a2[j] && v < dp[i - 1][j]) {
				v = dp[i - 1][j];
				k = j;
			}
			if (a1[i] == a2[j]){
				dp[i][j] = v + 1;
				solution[i][j] = k;
			}
		}
	}
	int ans = 0, cnt = 0;
	for (int i = 1; i <= n2; i++)
		if (dp[n1][i] > dp[n1][ans]) ans = i;
	printf("%d\n", dp[n1][ans]);
	for (int i = n1; i >= 1; i--)
		if (solution[i][ans] != -1)
			anss[++cnt] = a1[i], ans = solution[i][ans];
	for (int i = cnt; i >= 1; i--)
		printf("%d ", anss[i]);
	return 0;
}