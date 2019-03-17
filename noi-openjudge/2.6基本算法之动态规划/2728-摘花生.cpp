#include<cstdio>
#include<cstring>
#define MAXN 105

int map[MAXN][MAXN],T,R,C;
int dp[MAXN][MAXN];
inline int max(int a,int b){
    return a>b?a:b;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&R,&C);
        memset(map,0,sizeof(map));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=R;i++)
            for(int j=1;j<=C;j++)
                scanf("%d",&map[i][j]);
        for(int i=1;i<=R;i++)
            for(int j=1;j<=C;j++){
                dp[i][j]=max(dp[i-1][j],dp[i][j-1])+map[i][j];
            }
        printf("%d\n",dp[R][C]);
    }
    return 0;
}
