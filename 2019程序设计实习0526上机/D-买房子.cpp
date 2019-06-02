#include<cmath>
#include<cstdio>

int main() {
	int n, k, t;
	double rate;
	scanf("%d%d", &n, &k);
	rate = 1 + k * 1.0 / 100;
	for (t = 1; t <= 20; t++) {
		if (t*n >= 200 * pow(rate, t - 1))break;
	}
	if (t <= 20)
		printf("%d", t);
	else
		printf("Impossible");
	return 0;
}