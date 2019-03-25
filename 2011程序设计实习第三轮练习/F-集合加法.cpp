#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
constexpr int MAXN = 10005;

int A[MAXN], B[MAXN], n1, n2, m;
int main() {
	int T, id1, id2, ans, cnt;
	cin >> T;
	while (T--) {
		cin >> m;
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		ans = 0;
		cin >> n1;
		for (int i = 1; i <= n1; i++)
			cin >> A[i];
		cin >> n2;
		for (int i = 1; i <= n2; i++)
			cin >> B[i];
		sort(A + 1, A + n1 + 1);
		sort(B + 1, B + n2 + 1);
		id2 = n2;
		for (id1 = 1; id1 <= n1; id1++) {
			if (A[id1] != A[id1 - 1] || id1 == 1) cnt = 0;
			if (!cnt && !id2) break;
			while (A[id1] + B[id2] > m && id2) id2--;
			while (A[id1] + B[id2] == m && id2) { id2--; cnt++; }
			ans += cnt;
		}
		cout << ans << endl;
	}
	return 0;
}