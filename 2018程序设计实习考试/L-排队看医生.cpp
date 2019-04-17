#include<iostream>
#include<cstdio>
#include<string>
#include<queue>
using namespace std;
struct Patient
{
	Patient(int _p):priority(_p) {
		id = ++Total_Num;
	}
	int id;
	int priority;
	static int Total_Num;
	bool operator < (const Patient& A) const {
		if (priority != A.priority) return priority < A.priority;
		return id > A.id;
	}
};
priority_queue<Patient> doctor[3];
int Patient::Total_Num = 0;
int main() {
	int T,n,arg1,arg2;
	string cmd;
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 3; i++) {
			while (!doctor[i].empty()) doctor[i].pop();
		}
		Patient::Total_Num = 0;
		scanf("%d", &n);
		while (n--) {
			cin >> cmd;
			if (cmd == "IN") {
				scanf("%d%d", &arg1, &arg2);
				doctor[arg1 - 1].push(Patient(arg2));
			}
			else {
				scanf("%d", &arg1);
				arg1--;
				if (doctor[arg1].empty()) {
					printf("EMPTY\n");
				}
				else {
					printf("%d\n", doctor[arg1].top().id);
					doctor[arg1].pop();
				}
			}
		}
	}

	return 0;
}