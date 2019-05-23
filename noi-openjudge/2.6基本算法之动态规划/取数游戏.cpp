#include<cstdio>
#include<algorithm>
using namespace std;
constexpr int MAXN = 55;
int n;
long long dp[MAXN];  //取走前i个的方法
//注：用矩阵快速幂可提升至O(log n)
int main() {
	scanf("%d", &n);
	dp[1] = 2; dp[0] = 1;
	for (int i = 2; i <= n; i++)
		dp[i] = dp[i - 1] + dp[i - 2];
	printf("%lld", dp[n]);
	return 0;
}