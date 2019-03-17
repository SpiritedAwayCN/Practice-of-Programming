#include<iostream>
#include<cstring>
#include<queue>
#define MAXN 205
using namespace std;
struct node{
    node(short a,short b,short c=0,int d=0):x(a),y(b),status(c),step(d){}
    short x,y,status;
    int step=0;
};
int wall[MAXN][MAXN]; //-1平地 -2墙 -3传送门
int searched[MAXN][MAXN];//-1没走 0~31二进制
int sx,sy,ex,ey,ans;
queue<node> que;
vector<node> port;
int R,C,T,k;
void initialize(){
    char temp;
    cin>>R>>C>>k;
    memset(wall,-1,sizeof(wall));
    memset(searched,0,sizeof(searched)); //32种状态
    ans=0;
    port.clear();
    while(!que.empty()) que.pop();
    for(int i=1;i<=R;i++){
        cin.get();
        for(int j=1;j<=C;j++){
            temp = cin.get();
            switch(temp){
            case '.':
                break;
            case '#':
                wall[i][j]=-2;
                break;
            case '$':
                wall[i][j]=-3;
                port.push_back(node(i,j));
                break;
            case 'S':
                sx=i;sy=j;
                break;
            case 'E':
                ex=i;ey=j;
                wall[i][j]=-4;//终点
                break;
            default:
                wall[i][j]=temp-'0';
            }
        }
    }
}
bool update_data(int x,int y,node& current){
    if(x<1||y<1||x>R||y>C) return false;
    int stat=current.status;
    if(wall[x][y]==-4){
        int cnt=0;
        for(int i=1;i<32;i<<=1)
            if(stat&i) cnt++;
        if(cnt>=k){
            ans = current.step+1;
            return true;
        }
    }
    if(wall[x][y]==-2) return false;
    if(searched[x][y]&(1<<stat)) return false;

    if(wall[x][y]>=0) stat |= 1<<wall[x][y];//不拿白不拿

    if(wall[x][y]==-3){
        for(node loc: port){
            if(searched[loc.x][loc.y]==(1<<stat)) continue;
            searched[loc.x][loc.y]|=1<<stat;
            que.push(node(loc.x,loc.y,stat,current.step+1));
        }
    }else{
        searched[x][y]|=1<<stat;//0~31
        que.push(node(x,y,stat,current.step+1));
    }
    return false;
}
void BFS(){
    que.push(node(sx,sy));
    searched[sx][sy]=0;
    while(!que.empty()){
        node current = que.front();
        que.pop();
        if(update_data(current.x-1,current.y,current)) return;
        if(update_data(current.x,current.y-1,current)) return;
        if(update_data(current.x+1,current.y,current)) return;
        if(update_data(current.x,current.y+1,current)) return;
    }
}
int main(){
    cin>>T;
    while(T--){
        initialize();
        BFS();
        if(ans>0)
            cout<<ans<<endl;
        else
            cout<<"oop!\n";
    }
    return 0;
}
