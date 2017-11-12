/***
 *** Decide whether this program terminates
 *** If it does, use a model checker to verify a ranking function.
 *** If it does not, use a model checker to find a non-terminating execution.
 ***
 ***/


/** Returns a non-deterministic value */
extern int nd (void);

int main ()
{
  int x = nd();
  while (x >= 0)
    x = -2 * x + 10;
  return 0;
}
