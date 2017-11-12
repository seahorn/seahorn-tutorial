#include <seahorn/seahorn.h>
/* returns a non-deterministic value */
extern int nd (void);

// // -- original program
// int main() {
//   int x = nd();
//   while (x <= 10) {
//      x = x + 1;
//   }
//   return 0;
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
    // -- a single expression depending on x
    int c = 11 - x;

    while (x <= 10) {

        // -- the ranking function is strictly decreasing
        c = c - 1;
        // -- the ranking function is lower bounded by zero
        sassert(c >= 0);

        x = x + 1;
    }
    return 0;
}
