#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 50005;
int a[MAXN],dpf[MAXN],dpr[MAXN];
int main(){
	int T, n, ans;
	scanf("%d", &T);
	while (T--) {
		memset(dpf, 0, sizeof(dpf));
		memset(dpr, 0, sizeof(dpr));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		dpf[1] = a[1]; //1~i项 以i结尾的最大和
		dpr[n] = a[n];
		for (int i = 1; i <= n; i++) {
			if (i != 1) dpf[i] = max(a[i], dpf[i - 1] + a[i]);
			if (i != n) dpr[n - i] = max(a[n - i], dpr[n - i + 1] + a[n -i]);
		}
		//↓更新为：1~i项 最大和
		for (int i = 1; i <= n; i++) {
			if (i != 1) dpf[i] = max(dpf[i], dpf[i - 1]);
			if (i != n) dpr[n - i] = max(dpr[n - i], dpr[n - i + 1]);
		}
		ans = 0x80000000;
		for (int i = 1; i <= n - 1; i++) {
			ans = max(ans, dpf[i] + dpr[i + 1]);
		}
		printf("%d\n", ans);
	}
}