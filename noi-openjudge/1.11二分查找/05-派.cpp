#include<cstdio>
#include<algorithm>
#define MAXN 10005
using namespace std;
const double pai = 3.1415926535898;
double V[MAXN];
int n,f;

bool judge(double num){
    int sum=0;
    for(int i=n;i>=1;i--){
        sum+=int(V[i]/num);
    }
    return sum>=f;
}
int main(){
    scanf("%d%d",&n,&f);
    f++;
    int temp;
    double st=0,ed=0,mid;
    for(int i=1;i<=n;i++){
        scanf("%d",&temp);
        V[i] = pai*temp*temp;
        ed+=V[i];
    }
    sort(V+1,V+n+1);
    while(ed-st>=1e-4){
        mid = (st+ed)/2;
        if(judge(mid)) st=mid;
        else ed=mid;
    }

    printf("%.3f",st);
    return 0;
}
