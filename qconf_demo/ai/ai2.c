#include "seahorn/seahorn.h"
extern int nd();

#define MAX 100
int main () {
    int n = nd();
    assume (n > 0 && n < MAX);

    int a[MAX];
    int i;

    for (i=0;i<n;i++) {
        a[i]=i;
    }

#ifndef FORALL
    sassert (a[n-1] >= 0);
#else
    int j;
    for (j=0;j<n;j++) {
        sassert (a[j] >= 0);
    }
#endif
    return 0;
}
