#include "seahorn/seahorn.h"
#include <stdint.h>

extern int nd();

#define N 10

int main(int argc, char**argv) {

    int8_t a[N];
    int8_t b[N];

    int i;
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    int j;
    for (j = 0; j < N; j++) {
        b[j] = j;
    }

#ifndef ERROR
    printf("%d\n", a[i-1]);
    printf("%d\n", b[i-1]);
#else
    printf("%d\n", b[i]);
#endif

    return 0;
}
