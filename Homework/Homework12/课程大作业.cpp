#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
constexpr int MAXN = 15;
constexpr int INF = 0x7fffffff;
int dp[1 << MAXN], n, ddl[MAXN], ltime[MAXN], ans[1 << MAXN];
string hname[MAXN];
vector<int> path;

inline int score(int status, int k) {
	//当前状态下最后完成的作业是k时，因为k造成的扣分
	int tot_time = 0;
	for (int i = 0; i < n; i++)
		if (status & (1 << i)) {
			tot_time += ltime[i];
		}
	return max(0, tot_time - ddl[k]);
}

int main() {
	int T, temp, best, num;
	scanf("%d", &T);
	while (T--) {
		memset(dp, 0, sizeof(dp));
		memset(ans, -1, sizeof(ans));
		path.clear();

		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			cin >> hname[i] >> ddl[i] >> ltime[i];
		for (int i = 1; i < 1 << n; i++) {
			dp[i] = INF;
			best = -1;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					temp = dp[i - (1 << j)] + score(i, j);
					if (dp[i] > temp) dp[i] = temp, best = j;
					else if (dp[i] == temp) {
						//看看谁的字典序更小
						vector<int> p1, p2;
						p1.push_back(j);
						num = i - (1 << j);
						while (num) {
							p1.push_back(ans[num]);
							num -= 1 << ans[num];
						}
						p2.push_back(best);
						num = i - (1 << best);
						while (num) {
							p2.push_back(ans[num]);
							num -= 1 << ans[num];
						}
						reverse(p1.begin(), p1.end());
						reverse(p2.begin(), p2.end());
						if (p1 < p2) best = j;
					}
				}
			}
			ans[i] = best;
		}
		num = (1 << n) - 1;
		printf("%d\n", dp[num]);
		while (num) {
			path.push_back(ans[num]);
			num -= 1 << ans[num];
		}
		for (auto iter = path.rbegin(); iter != path.rend(); iter++) {
			cout << hname[*iter] << endl;
		}
	}
	return 0;
}