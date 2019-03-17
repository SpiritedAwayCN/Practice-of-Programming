#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXN 17
int n;
bool map[MAXN][MAXN],temp[MAXN][MAXN];
void change_switch(int x,int y){
    temp[x][y] = !temp[x][y];
    temp[x-1][y] = !temp[x-1][y];
    temp[x+1][y] = !temp[x+1][y];
    temp[x][y-1] = !temp[x][y-1];
    temp[x][y+1] = !temp[x][y+1];
}

int main(){
    scanf("%d",&n);
    char c;
    for(int i=1;i<=n;i++){
        getchar();
        for(int j=1;j<=n;j++){
            c=getchar();
            map[i][j] = c=='y';
        }
    }
    // 枚举第一行检测下一行
    int cnt=0,ans = 0x7fffffff;
    bool tag ;
    for(int tex=0;tex<(1<<n);tex++){
        cnt=0;
        tag = false;
        memcpy(temp,map,sizeof(map));
        for(int i=0;i<n;i++){
             if(tex&(1<<i)){
                change_switch(1,i+1);
                cnt++;
             }
        }
        for(int i=2;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!temp[i-1][j]){
                    //需要换
                    change_switch(i,j);
                    cnt++;
                }
            }
        }
        for(int j=1;j<=n;j++)
            if(!temp[n][j]) tag = true;
        if(tag) continue;
        if(cnt<ans) ans = cnt;
    }
    if(ans<0x7fffffff)
        printf("%d",ans);
    else
        printf("inf");
    return 0;
}
