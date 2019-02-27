#include<cstdio>
#define MAXN 50005
int a[MAXN],n,m;
int judge_ans(int ans){
    int last = 0, cnt = 0;
    for(int i = 1; i<= n+1 ;i++){
        if(a[i]-last>=ans){
            last = a[i];
        }else{
            cnt++;
        }
    }
    if(cnt>m) return -1;
    else return 1;
}
int main(){
    int l;
    scanf("%d%d%d",&l,&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    a[n+1] = l;
    int lower = 0, upper = l, ans = 0;
    while(lower < upper){
        ans = (lower + upper + 1) >> 1;
        if(judge_ans(ans)<0) upper = ans - 1;
        else lower = ans;
    }
    ans = lower;
    printf("%d",ans);
    return 0;
}
