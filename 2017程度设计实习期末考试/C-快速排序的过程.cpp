#include<cstdio>
const int MAXN = 1005;
int arr[MAXN], n;

inline int Partition(int low, int high) {
	int i = low;
	int j = high + 1;
	int key = arr[low];
	while (true){
		/*从左向右找比key大的值*/
		while (arr[++i] < key)
		{
			if (i == high) {
				break;
			}
		}
		/*从右向左找比key小的值*/
		while (arr[--j] > key)
		{
			if (j == low) {
				break;
			}
		}
		if (i >= j) break;
		/*交换i,j对应的值*/
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	/*中枢值与j对应值交换*/
	int temp = arr[low];
	arr[low] = arr[j];
	arr[j] = temp;
	return j;
}
inline void printA() {
	for (int i = 1; i <= n; i++)
		printf("%d ", arr[i]);
	putchar('\n');
}

void Qsort(int low, int high) {
	if (low < high) {
		int m = Partition(low, high);//分
		printA();
		Qsort(low, m - 1);//解
		Qsort(m + 1, high);
		//不用合
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	Qsort(1, n);
	printA();
	return 0;
}