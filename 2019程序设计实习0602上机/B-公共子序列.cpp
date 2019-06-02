#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 205;
char s1[MAXN], s2[MAXN];
int dp[MAXN][MAXN];
int main() {
	int l1, l2;
	while (scanf("%s%s", s1, s2) != EOF) {
		l1 = strlen(s1);
		l2 = strlen(s2);
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i <= l1; i++)
			for (int j = 1; j <= l2; j++) {
				if (s1[i - 1] == s2[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		printf("%d\n", dp[l1][l2]);
	}
	return 0;
}