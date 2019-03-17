#include<cstdio>

int f[35];
int main(){
    int t;
    f[1]=1;f[0]=1;
    for(int i=2;i<=30;i++){
        f[i] = f[i-1] + f[i-2];
    }
    while(scanf("%d",&t)!=EOF){
        printf("%d\n",f[t]);
    }
    return 0;
}
