/***
 *** Decide whether this program terminates
 *** If it does, use a model checker to verify a ranking function.
 *** If it does not, use a model checker to find a non-terminating execution.
 ***
 ***/

/* returns a non-deterministic value */
extern int nd (void);

int main()
{
  int x = nd(), y = nd();
  while (x > 0 && y > 0)
  {
    if (nd())
    {
      x = x - 1;
      y = nd();
    }
    else
    {
      y = y - 1;
    }
  }
  return 0;
}

