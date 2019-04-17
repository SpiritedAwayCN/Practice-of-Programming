#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

multiset<int> s;
int a[5000 + 5];

int main() {
	int n, T, k;
	scanf("%d", &T);
	while (T--) {
		s.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", a + i);
			s.insert(a[i]);
		}
		bool flag = false;
		scanf("%d", &k);
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int target = k - a[i] - a[j], min_count = 1;
				// 在此处补充你的代码
				min_count = s.count(target);
				if (!min_count) continue;
				int c1 = s.count(a[i]), c2 = s.count(a[2]);
				if (target == a[i]) {
					if (target == a[j]) {
						if (c1 >= 3) {
							flag = true;
							break;
						}
					}
					else {
						if (c1 >= 2) {
							flag = true;
							break;
						}
					}
				}
				else if(target==a[j]){
					if (c1 >= 2) {
						flag = true;
						break;
					}
				}
				else if (min_count > 0) {
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		puts(flag ? "Yes" : "No");
	}
	return 0;
}