#include<cstdio>
#define MAXN 100005
int n,m,a[MAXN];
int judge_ans(int ans){
    int cnt=1,sum=0;
    for(int i=1;i<=n;i++){
        if(a[i]>ans) return -1;
        if(sum+a[i]>ans){
            i--;
            sum = 0;
            cnt++;
        }else
            sum+=a[i];
    }
    return cnt > m ? -1 : 1;
}
int main(){
    int ans=0,lower=1,upper=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        upper+=a[i];
    }
    while(lower < upper){
        ans = (lower + upper) >> 1;
        if(judge_ans(ans)<0) lower = ans + 1;
        else upper = ans;
    }
    ans = upper;
    printf("%d",ans);
    return 0;
}
