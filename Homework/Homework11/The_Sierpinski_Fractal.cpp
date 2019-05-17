#include<iostream>

using namespace std;
inline void print_space(int num) {
	for (int i = 0; i < num; i++)
		printf(" ");
}


void dfs(int n, int i) {
	//第n个三角形的第i行
	if (n == 1) {
		if (i == 1) printf(" /\\");
		else printf("/__\\");
		return;
	}
	if (i <= 1 << (n - 1)) { 
		print_space(1 << (n - 1));
		dfs(n - 1, i); 
		return; 
	}
	int d = i - (1 << (n - 1));
	dfs(n - 1, d);
	print_space((1 << n) - i);
	dfs(n - 1, d);
}

int main() {
	int n;
	while (cin >> n) {
		if (n == 0)break;
		for (int i = 1; i <= 1 << n; i++) {
			dfs(n, i);
			putchar('\n');
		}
		putchar('\n');
	}
	return 0;
}