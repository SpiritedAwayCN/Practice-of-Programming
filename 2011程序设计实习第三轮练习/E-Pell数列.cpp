#include <stdio.h>

#define MOD 32767
#define N 1000000
int pell[N+1];

void setpell(int n)
{
    int i;

    pell[1] = 1;
    pell[2] = 2;

    for(i=3; i<=n; i++)
        pell[i] = (2 * pell[i - 1] + pell[i - 2]) % MOD;
}

int main(void)
{
    int n, i;

    setpell(N);

    scanf("%d", &n);
    while(n--) {
        scanf("%d", &i);

        printf("%d\n", pell[i]);
    }
    return 0;
}
