#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


char str1[105], str2[105];
int cont1[30], cont2[30];
int main() {
	bool flag = false;
	scanf("%s", str1);
	scanf("%s", str2);
	int l1 = strlen(str1), l2 = strlen(str2);
	if (l1 == l2) {
		for (int i = 0; i < l1; i++) {
			cont1[str1[i] - 'A']++;
			cont2[str2[i] - 'A']++;
		}
		sort(cont1, cont1 + 26);
		sort(cont2, cont2 + 26);
		flag = true;
		for (int i = 0; i < 26; i++)
			if (cont1[i] != cont2[i]) flag = false;
	}
	if (flag)
		printf("YES");
	else
		printf("NO");
	return 0;
}