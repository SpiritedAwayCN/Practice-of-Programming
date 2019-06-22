#include<cstdio>
#include<algorithm>
using namespace std;
int matrix[6][6], lmax[6], cmin[6];

int main() {
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= 5; j++)
			scanf("%d", &matrix[i][j]);

	for (int i = 1; i <= 5; i++) {
		lmax[i] = matrix[i][1];
		for (int j = 2; j <= 5; j++)
			lmax[i] = max(lmax[i], matrix[i][j]);
	}
	for (int j = 1; j <= 5; j++) {
		cmin[j] = matrix[1][j];
		for (int i = 2; i <= 5; i++)
			cmin[j] = min(cmin[j], matrix[i][j]);
	}
	bool flag = false;
	for (int i = 1; i <= 5; i++)
		for (int j = 1; j <= 5; j++)
			if (lmax[i] == cmin[j]) {
				flag = true;
				printf("%d %d %d\n", i, j, lmax[i]);
			}
	if (!flag) {
		printf("not found\n");
	}
	return 0;
}