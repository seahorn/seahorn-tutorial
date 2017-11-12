#include "seahorn/seahorn.h"
extern int nd();

#define N 10

int main(int argc, char**argv)
{
    int i;
    int a[N];

    // ghost variables
    int offset;
    unsigned int size;

    // initialization of the ghost variables
    offset = 0;
    size = sizeof(a);


    for (i = 0; i < N; i++) {
        // update offset
        offset = sizeof(int)*i;
	// check the array write is in-bounds
        sassert (offset < size);
        sassert (offset >= 0);

        a[i] = i;
    }

#ifndef ERROR
    // update offset
    offset = sizeof(int)*(i-1);
    // check the array read is in-bounds
    sassert (offset < size);
    sassert (offset >= 0);

    printf("%d\n", a[i-1]);
#else
    // update offset
    offset = sizeof(int)*i;
    // check the array read is in-bounds
    sassert (offset < size);
    sassert (offset >= 0);

    printf("%d\n", a[i]);
#endif
    return 0;
}
