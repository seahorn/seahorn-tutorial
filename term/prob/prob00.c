/***
 *** Decide whether this program terminates
 *** If it does, use a model checker to verify a ranking function.
 *** If it does not, use a model checker to find a non-terminating execution.
 ***
 ***/

/** Returns a non-deterministic value */
extern int nd (void);

int main(void)
{
  int x;
  int dir = 1;

  x = nd();
  while (x > 0)
    {
      x = x + dir;

      if (x > 10) dir = -1 * dir;
      if (x < 5) dir = -1 * dir;

      printf ("(x=%d,dir=%d)\n", x, dir);
    }
  return 0;
}
