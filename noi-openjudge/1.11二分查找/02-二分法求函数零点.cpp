#include<cstdio>

int coefficient[]={1,-15,85,-225,274,-121};
double f(double x){
    double value=coefficient[0];
    for(int i=1;i<=5;i++)
        value = value * x + coefficient[i];
    return value;
}
inline double abs(double a){
    return a>0?a:-a;
}
int main(){
    double s=1.5,e=2.4,m;
    while(abs(e-s)>=1e-7){
        m=(s+e)/2;
        if(f(s)*f(m)<0) e=m;
        else s=m;
    }
    printf("%.6lf",e);
    return 0;
}
