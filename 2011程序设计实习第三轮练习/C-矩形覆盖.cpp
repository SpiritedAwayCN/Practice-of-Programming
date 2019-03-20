#include <stdio.h>
#include <stdlib.h>
#include <string.h>
constexpr auto MAX_LEN = 15;
int min_area[1 << MAX_LEN];
int occupion/**这个整数的位用来记录点的覆盖情况，1表示未被覆盖，0表示已被覆盖**/;
int point[15][2]/**每个点的信息**/, num/**点的个数**/;
int area(int i, int j)//特殊的函数，这个函数对于同一直线上的两点，返回的面积是距离差，这样在计算最小面积时会自动舍去重复占用的方案
{
	if (point[i][0] == point[j][0]) return abs(point[i][1] - point[j][1]);
	if (point[i][1] == point[j][1]) return abs(point[i][0] - point[j][0]);
	return abs(point[i][1] - point[j][1])*abs(point[i][0] - point[j][0]);
}
int search(int n)/**搜索函数，传入值为正在处理的占用情况,输出值为对应占用情况尚需的最小面积**/
{
	int i, j, k;
	if (min_area[n] >= 0)//如果这种状态对应的问题已经解决
		return min_area[n];
	if (n == 0)
		return min_area[n] = 0;
	min_area[n] = 40000000;
	for (i = 0; i < num; i++)
	{
		if (n&(1 << i))//如果第i+1个点尚未被占用
		{
			for (j = 0; j < num; j++)
			{
				if (i != j)
				{
					int tmp, s;
					tmp = n & (~((1 << i) | (1 << j)));
					for (k = 0; k < num; k++)
						if ((point[i][0] == point[k][0] && point[j][1] == point[k][1]) || (point[i][1] == point[k][1] && point[j][0] == point[k][0]))
							tmp &= (~(1 << k));
					s = area(i, j) + search(tmp);
					if (s < min_area[n])
						min_area[n] = s;
				}
			}
		}
	}
	return min_area[n];
}
int main()
{
	int i;
	scanf("%d", &num);
	while (num)
	{
		for (i = 0; i < num; i++)
			scanf("%d%d", &point[i][0], &point[i][1]);
		memset(min_area, -1, sizeof(min_area));
		occupion = (1 << num) - 1;//覆盖状态初始化，所有的点对应的位都是1
		printf("%d\n", search(occupion));
		scanf("%d", &num);
	}
	return 0;
}