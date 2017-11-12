#include<seahorn/seahorn.h>

/* returns a non-deterministic value */
extern int nd (void);

// // -- original program
// int main() {
//      int x = nd();
//      while (x != 0) {
//              if (x < 10) {
//                      x = x + 1;
//              } else {
//                      x = -x;
//              }
//      }
//      return 0;
// }

int main() {
    /**
     ** The idea is to add one (or more) counter(s) for each loop
     ** which are (lexicographically) strictly decreasing at each loop iteration
     ** and then check if their value is bounded from below.
     **/

    int x = nd();

    // -- the value of the counter gives a ranking function;
    // -- in this case the ranking function is
    // -- a piecewise-defined expression depending on x
    int c;
    if (x <= 0) {
        c = -x;
    } else if (x <= 9) {
        c = 21 - x;
    } else {
        c = x + 1;
    }

    while (x != 0) {

        // -- the ranking function is strictly decreasing
        c = c - 1;
        // -- the ranking function is lower bounded by zero
        sassert(c >= 0);

        if (x < 10) {
            x = x + 1;
        } else {
            x = -x;
        }
    }
    return 0;
}
