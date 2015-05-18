/***
 *** Decide whether this program satisfies temporal property AG AF
 *** (x==0), or, in English, 'in every execution of the program, the
 *** state in which x == 0 occurs infinitely often'.
 ***
 *** If the program satisfies the property, develop a verifiable
 *** proof. Otherwise, find a counterexample.
 ***/

/* returns a non-deterministic value */ 
extern int nd (void);

int main()
{
  int x = nd();
  while (1)
  {
    if (x < 10) {
      x = x + 1;
    } else {
      x = -x;
    }
  }
  return 0;
}

