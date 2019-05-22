#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
//#define scanf scanf_s
constexpr int MAXM = 25;
int n, m, min_s[MAXM], min_v[MAXM], min_S = 0x7ffffff0;
void dfs(int N, int M, int last_R, int last_H, int sum_S) {
	if (N == 0 || M == 0) {
		if ((N == 0) + (M == 0) == 2) {
			if (min_S > sum_S) {
				min_S = sum_S;
			}
		}
		return;
	}
	//剪枝准备
	if (sum_S + min_s[M] > min_S) { return; }
	if (N < min_v[M]) return;
	if (m > M && (2 * N)/ (last_R - 1) > (min_S - sum_S)) { return; }

	for (int r = last_R - 1; r >= M; r--) {
		if (M == m) sum_S = r * r;
		int max_h = (N - min_v[M - 1]) / (r*r);
		for (int h = min(last_H - 1,max_h); h >= M; h--) {
			dfs(N - r * r * h, M - 1, r, h, sum_S + 2 * r * h);
		}
	}
}
inline void initialize() {
	min_v[0] = min_s[0] = 0;
	for (int i = 1; i <= m; i++) {
		min_v[i] = min_v[i - 1] + i * i * i;//剩下i层的最小体积
		min_s[i] = min_s[i - 1] + 2 * i * i;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	initialize();
	dfs(n, m, (int)sqrt(n) + 1, n + 1, 0);
	printf("%d", (min_S == 0x7ffffff0 ? 0 : min_S));
	return 0;
}