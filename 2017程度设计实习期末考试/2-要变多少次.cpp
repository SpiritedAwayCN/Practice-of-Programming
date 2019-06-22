#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 1005;

char str[MAXN];
int dp[MAXN][2];

int main() {
	int T, len;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str);
		len = strlen(str);
		memset(dp, 0, sizeof(dp));
		dp[0][0] = str[0] == '0' ? 0 : 1;
		dp[0][1] = str[0] == '0' ? 1 : 0;
		for (int i = 1; i < len; i++) {
			if (str[i] == '1') {
				dp[i][0] = dp[i - 1][0] + 1;
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
			}
			else {
				dp[i][0] = dp[i - 1][0];
				dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
			}
		}
		printf("%d\n", min(dp[len - 1][0], dp[len - 1][1]));
	}
	return 0;
}