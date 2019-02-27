#include<cstdio>
#define MAXN 10005
#define INF 0x8fffffff
int dp[MAXN][2][2],n,a[MAXN],b[MAXN],c[MAXN];
inline int max(int a,int b){
    return a>b?a:b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    dp[1][1][0]=INF;
    dp[1][0][1]=b[1];
    dp[1][0][0]=a[1];
    dp[1][1][1]=INF;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=max(dp[i-1][1][1],dp[i-1][0][1])+a[i];
        dp[i][1][0]=max(dp[i-1][1][0],dp[i-1][0][0])+b[i];
        dp[i][0][1]=max(dp[i-1][1][1],dp[i-1][0][1])+b[i];
        dp[i][1][1]=max(dp[i-1][1][0],dp[i-1][0][0])+c[i];
    }
    int ans = max(dp[n][1][0],dp[n][0][0]);
    printf("%d",ans);
}
