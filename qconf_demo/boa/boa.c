#include "seahorn/seahorn.h"

extern int nd();

#define N 10

int main(int argc, char**argv) {
    int i;
    int a[N];

    for (i = 0; i < N; i++)  {
        a[i] = i;
    }

#ifndef ERROR
    printf("%d\n", a[i-1]);
#else
    printf("%d\n", a[i]);
#endif
    return 0;
}
