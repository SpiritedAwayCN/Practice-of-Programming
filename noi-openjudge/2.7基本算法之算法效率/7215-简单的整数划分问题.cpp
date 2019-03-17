#include<cstdio>
#include<cstring>
#define MAXN 55

int dp[MAXN][MAXN],n;
//dp[i][j] 数字i，最小数>=j的种数
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            dp[i][i]=1;
        for(int i=1;i<=n;i++)
            for(int j=i-1;j>=1;j--){
                dp[i][j] = dp[i][j+1]+dp[i-j][j];
            }
        printf("%d\n",dp[n][1]);
    }
	return 0;
}
