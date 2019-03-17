#include<cstdio>
#include<cmath>

int main(){
    double n,C,L,LL;
    scanf("%lf%lf%lf",&L,&n,&C);
    double inf = 0;
    LL=(1+n*C)*L;
    double sup = L/2,x,temp;
    while(sup-inf>=1e-4){
        x = (sup+inf)/2;
        temp = x+L*L/(4*x);
        temp = temp * asin(L/temp);
        if(temp < LL) inf = x;
        else sup = x;
    }
    printf("%.3lf",sup);
    return 0;
}
