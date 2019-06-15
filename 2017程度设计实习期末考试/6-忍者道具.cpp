#include<cstdio>
#include<algorithm>
using namespace std;
int weight[20], n, pack[20],mw, ans = 0x7fffffff;

void dfs(int x, int cnt) {
	if (cnt >= ans) return;
	if (x > n) {
		ans = cnt;
		return;
	}
	for (int i = 1; i <= cnt; i++)
		if (pack[i] + weight[x] <= mw) {
			pack[i] += weight[x];
			dfs(x + 1, cnt);
			pack[i] -= weight[x];
		}
	//开新的背包
	pack[cnt + 1] = weight[x];
	dfs(x + 1, cnt + 1);
	pack[cnt + 1] = 0;
}
bool compare(int a, int b) {
	return a > b;
}

int main() {
	scanf("%d%d", &n, &mw);
	for (int i = 1; i <= n; i++)
		scanf("%d", &weight[i]);
	sort(weight + 1, weight + n + 1, compare);
	//排序更高效
	dfs(1, 0);
	printf("%d", ans);
	return 0;
}