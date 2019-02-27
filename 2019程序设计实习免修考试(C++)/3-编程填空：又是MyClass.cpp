#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
// 在此处补充你的代码
template<class T>
class CMyClass{
public:
    CMyClass(T* loc, int len)
    : first(loc)
    , max_len(len)
    {
    }
    T operator[](int index){
        return *(first + index);
    }
private:
    T* first;
    int max_len;
};
int  a[40];
int main(int argc, char** argv) {
	int t;
	scanf("%d",&t);
	while ( t -- ) {
		int m;
		scanf("%d",&m);
		for (int i = 0;i < m; ++i)
			scanf("%d",a+i);
		char s[100];
		scanf("%s",s);
		CMyClass<int> b(a, m);
		CMyClass<char> c(s, strlen(s));
		printf("%d %c\n", b[5], c[7]);
	}
	return 0;
}
