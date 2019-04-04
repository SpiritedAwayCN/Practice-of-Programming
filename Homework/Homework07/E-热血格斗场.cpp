#include<cstdio>
#include<map>

using namespace std;
map<int, int> member;

int main() {
	int n;
	int id, force;
	map<int, int>::iterator iter,iter2;
	member.insert(pair<int, int>(1e9, 1));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &id, &force);
		iter = member.insert(pair<int, int>(force, id)).first;
 		int num = iter->first;
		if (iter == member.begin()) {
			iter++;
			printf("%d %d\n", id, iter->second);
		}
		else if(iter== --member.end()){
			iter--;
			printf("%d %d\n", id, iter->second);
		}
		else {
			iter2 = iter;
			iter++;
			iter2--;
			if (iter->first - num < num - iter2->first) {
				printf("%d %d\n", id, iter->second);
			}
			else {
				printf("%d %d\n", id, iter2->second);
			}
		}
	}
	return 0;
}