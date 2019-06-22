#include<cstdio>
#include<algorithm>
using namespace std;

int three[8], n;

inline void print_space(int num) {
	while (num--) putchar(' ');
}

int draw_line(int dep, int l) {
	//返回这一行的字符数
	if (dep == 1) {
		putchar('X');
		return 1;
	}

	if (l <= three[dep - 2]) {
		print_space(2 * three[dep - 2] - draw_line(dep - 1, l));
		return 2 * three[dep - 2] + draw_line(dep - 1, l);
	}
	else if (l <= 2 * three[dep - 2]) {
		print_space(three[dep - 2]);
		return three[dep - 2] + draw_line(dep - 1, l - three[dep - 2]);
	}
	else {
		l -= 2 * three[dep - 2];
		print_space(2 * three[dep - 2] - draw_line(dep - 1, l));
		return 2 * three[dep - 2] + draw_line(dep - 1, l);
	}
}

int main() {
	three[0] = 1;
	//freopen("分形盒_out.txt", "w", stdout);
	for (int i = 1; i <= 7; i++)
		three[i] = three[i - 1] * 3;
	while (scanf("%d", &n) != EOF) {
		if (n < 0) break;
		for (int i = 1; i <= three[n - 1]; i++) {
			draw_line(n, i);
			putchar('\n');
		}
		printf("-\n");
	}

	return 0;
}