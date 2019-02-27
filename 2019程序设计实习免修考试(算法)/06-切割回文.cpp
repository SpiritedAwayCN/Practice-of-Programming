#include<cstdio>
#include<cstring>
#define MAXN 1005

int dp[MAXN];
inline int min(int a,int b){
    return a>b?b:a;
}
bool judge_inverse(char* str,int st,int ed){
    while(st<ed){
        if(str[st]!=str[ed]) return false;
        st++;
        ed--;
    }
    return true;
}

int main(){
    int T;
    scanf("%d",&T);
    char str[MAXN];
    int len;
    getchar();
    while(T--){
        gets(str);
        memset(dp,0,sizeof(dp));
        len=strlen(str);
        dp[0]=0;
        for(int i=1;i<len;i++){
            dp[i] = 0x7fffffff;
            if(judge_inverse(str,0,i)){
                dp[i]=0;
                continue;
            }
            for(int j=0;j<=i;j++)
                if(judge_inverse(str,j+1,i))
                    dp[i]=min(dp[i],dp[j]+1);
        }
        printf("%d\n",dp[len-1]);
    }
    return 0;
}
