#include<cstdio>
long long dp1[55], dp2[55];

int main() {
	dp1[1] = dp1[2] = 1;
	dp2[2] = 1;
	for (int i = 3; i < 50; i++) {
		dp1[i] = dp1[i - 1] + dp1[i - 2];
		dp2[i] = dp2[i - 1] + dp2[i - 2];
	}
	int T, s ,t, ss, tt;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &s, &t);
		ss = s % 2;
		if (ss == 0) ss = 2;
		tt = t - (s - ss);
		if (ss == 1) {
			printf("%lld\n", dp1[tt]);
		}
		else
			printf("%lld\n", dp2[tt]);
	}
	return 0;
}