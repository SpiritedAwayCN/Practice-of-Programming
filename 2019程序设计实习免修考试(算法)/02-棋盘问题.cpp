#include<cstdio>
#include<cstring>
#define MAXN 10
bool vis_line[MAXN],vis_column[MAXN];
bool map[MAXN][MAXN];
int n,k,cont=0;
void dfs(int num,int x,int y=1){
    if(num==k){
        cont++;
        return;
    }
    for(int i=x;i<=n && n-i+1>=k-num ;i++){
        for(int j=1;j<=n;j++){
            if(map[i][j] && (!vis_line[i]) && (!vis_column[j])){
                vis_line[i] = true;
                vis_column[j] = true;
                //ÐÐµÝÔö°Ú
                //printf("%d %d\n",i,j);
                dfs(num+1,x+1,1);
                vis_line[i] = false;
                vis_column[j] = false;
            }
        }
    }
}

int main(){

    while(true){
        scanf("%d%d",&n,&k);
        if(n==-1&&k==-1) break;
        cont = 0;
        memset(vis_line,0,sizeof(vis_line));
        memset(vis_column,0,sizeof(vis_column));
        memset(map,0,sizeof(map));
        char temp;
        for(int i=1;i<=n;i++){
            getchar();
            for(int j=1;j<=n;j++){
                temp = getchar();
                map[i][j] = temp=='#'?true:false;
            }
            //getchar();
        }
        dfs(0,1,1);
        printf("%d\n",cont);
    }
    return 0;
}
