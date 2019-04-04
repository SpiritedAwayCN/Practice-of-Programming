#include<cstdio>
#include<algorithm>
#include<set>

using namespace std;
struct node {
	node(int _id, int _force) :id(_id), force(_force) {}
	int id;
	int force;
	bool operator< (const node& b) const {
		if (force != b.force) return force < b.force;
		return id < b.id;
	}
};
set<node> member;
int main() {
	int n;
	int id, force;
	set<node>::iterator iter, next, last;
	member.insert(node(1, 1e9));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &id, &force);
		iter = member.insert(node(id, force)).first;
		if (iter == member.begin()) {
			iter++;
			printf("%d %d\n", id, iter->id);
		}
		else if(iter== --member.end()){
			iter--;
			printf("%d %d\n", id, iter->id);
		}
		else {
			last = iter; --last;
			next = iter; ++next;
			int temp = last->force;
			while (last->force == temp && last != member.begin()){
				--last;
			}
			if (last->force != temp) last++;
			
			if (next->force - force < force - last->force) {
				printf("%d %d\n", id, next->id);
			}
			else if(next->force - force > force - last->force){
				printf("%d %d\n", id, last->id);
			}
			else {
				printf("%d %d\n", id, min(last->id, next->id));
			}
		}
	}
	return 0;
}