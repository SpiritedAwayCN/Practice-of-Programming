#include<cstdio>
void solve(int num){
    if(num==0){
        putchar('0');
        return;
    }
    int last;
    for(last=0;(num&(1<<last)) == 0;last++);
    //printf("\nlast=%d\n",last);
    for(int i=31;i>=last;i--){
        if(num & (1<<i)){
            putchar('2');
            if(i!=1){
                putchar('(');
                solve(i);
                putchar(')');
            }
            if(i!=last) putchar('+');
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    solve(n);
    return 0;
}
