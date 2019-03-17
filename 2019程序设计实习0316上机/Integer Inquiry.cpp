#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt {
public:
    CHugeInt(const char* ch, bool ninv = false){
        memset(bit,0,sizeof(bit));
        size_n=strlen(ch);
        if(ninv){
            for(int i=0;i<size_n;i++)
                bit[i]=ch[i]-'0';
        }else{
            for(int i=0;i<size_n;i++)
                bit[size_n-i-1]=ch[i]-'0';
        }
        do{
            size_n--;
        }while(!bit[size_n]);
        size_n++;
    }
    CHugeInt(int num)
    : size_n(0)
    {
        memset(bit,0,sizeof(bit));
        for(;num;num/=10){
            bit[size_n++] = num%10;
        }
    }
    friend CHugeInt operator+(const CHugeInt& num1,const CHugeInt& num2){
        int siz = max(num1.size_n,num2.size_n);
        if(siz==0) return CHugeInt(0);
        char num[210];
        memset(num,0,sizeof(num));
        int tag = 0,temp;
        for(int i=0;i<siz;i++){
            temp = num1.bit[i]+num2.bit[i]+tag;
            num[i] = temp%10 + '0';
            tag = temp/10;
        }
        if(tag>0) num[siz] = tag + '0';
        return CHugeInt(num, true);
    }
    friend void operator +=(CHugeInt& numb,const CHugeInt& num2){
        numb = numb + num2;
    }
    friend CHugeInt& operator++(CHugeInt& numb){
        numb = numb + 1;
        return numb;
    }
    friend CHugeInt operator++(CHugeInt& numb,int){
        CHugeInt tmp = numb;
        numb += 1;
        return tmp;
    }
    friend ostream& operator <<(ostream& ost, const CHugeInt& numb){
        if(numb.size_n==0){
            ost<<0;
            return ost;
        }
        for(int i=numb.size_n-1;i>=0;i--)
            ost<<numb.bit[i];
        return ost;
    }
private:
short bit[210];
int size_n;
};
int  main()
{
	char s[210];
	CHugeInt sum(0);

	while (cin >> s) {
        if(strlen(s)==1 && s[0]=='0') break;
		sum+=CHugeInt(s);
	}
	cout<<sum;
	return 0;
}
