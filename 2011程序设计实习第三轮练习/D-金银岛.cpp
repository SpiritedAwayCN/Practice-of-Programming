#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 105;
struct node{
	int w, v;
}item[MAXN];
bool compare(node& a, node &b) {
	return a.v * b.w > a.w * b.v;
}
int T,n,w;
int main() {
	cin >> T;
	double ans;
	int i;
	while (T--) {
		ans = 0;
		memset(item, 0, sizeof(item));
		cin >> w >> n;
		for (i = 1; i <= n; i++)
			cin >> item[i].w >> item[i].v;
		sort(item + 1, item + n + 1, compare);
		for (i = 1; i <= n && w >= item[i].w; i++) {
			ans += item[i].v;
			w -= item[i].w;
		}
		if (i != n + 1) {
			ans += w * item[i].v * 1.0 / item[i].w;
		}
		cout << fixed << setprecision(2) << ans << endl;
	}

	return 0;
}