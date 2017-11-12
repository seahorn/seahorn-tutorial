#include "seahorn/seahorn.h"

extern int nd(void);

int main(void) {
    int n, k, j;

    n = nd();
    k = nd();
    assume(k >= 2);

    j = 0;

#pragma nounroll
    while( j < n ) {
        j++;
        k--;
    }

    sassert(k>=0);

    return 0;
}
