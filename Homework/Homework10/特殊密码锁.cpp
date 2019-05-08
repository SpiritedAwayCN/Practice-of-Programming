#include<stdio.h>
#include<cstring>
constexpr int MAXN = 35;
char password[MAXN], init[MAXN],temp[MAXN];
int len;
inline void do_change(int index) {
	if (index < 0 || index>=len) return;
	if (temp[index] == '0') temp[index] = '1';
	else temp[index] = '0';
}
inline void set_change(int index) {
	do_change(index);
	do_change(index - 1);
	do_change(index + 1);
}

int main() {
	scanf("%s %s", init, password);
	len = strlen(init);
	int ans = 500, cnt = 0;
	for (int sta = 0; sta < 2; sta++) {
		strcpy(temp, init);
		cnt = 0;

		if (sta) set_change(0), cnt++;
		for (int i = 1; i < len; i++) {
			if (temp[i - 1] != password[i - 1])
				set_change(i), cnt++;
		}
		if (password[len - 1] == temp[len - 1] && ans > cnt)
			ans = cnt;
	}
	if (ans >= 500)
		printf("impossible");
	else
		printf("%d", ans);
	return 0;
}