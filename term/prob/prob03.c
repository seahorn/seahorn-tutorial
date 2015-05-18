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
  int x = nd();
  while (x != 0)
  {
    if (x < 10) 
      x = x + 1;
    else 
      x = -x;
  }
  return 0;
}
