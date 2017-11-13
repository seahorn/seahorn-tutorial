#include "seahorn/seahorn.h"
extern int nd();

int main (){
    int x = 1;
    int y = 0;
    int n = nd();
    assume (n > 0);

    while (nd() && x < n) {
        x=x+y;
        y++;
    }

    sassert (x>=y);

    return 0;
}
