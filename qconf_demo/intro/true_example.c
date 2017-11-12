#include "seahorn/seahorn.h"

extern int nd(void);

int main(void) {
    int n, k, j;

    n = nd();
    assume (n>0);

    k = nd();
    assume (k>n);

    j = 0;

#pragma clang loop unroll(disable)
    while( j < n ) {
        j++;
        k--;
    }

    sassert(k>=0);
    return 0;
}
