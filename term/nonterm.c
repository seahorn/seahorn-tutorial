
/***
 *** returns a counterexample that shows an infinite execution (i.e.,
 *** the same program state is reached twice.
 ***
 ***/

/** Returns a non-deterministic value */ 
extern int nd (void);

extern void __VERIFIER_assume (int);
extern void __VERIFIER_error (void);
void assert (int v) { if (!v) __VERIFIER_error (); }


void main(void)
{

  /**
   ** The idea is to non-deterministically store a state during
   ** execution and then check if it was repeated or not. CBMC takes
   ** care of resolving the non-determinism.
   **/


  // -- place to store 'saved' version of x and dir
  int sx;
  int sdir;

  // -- flag to indicate that we've stored a previous state
  int f;


  // -- x and dir of the original program
  int x;
  int dir = 1;

  // -- initially, the flag is unset, everything else is
  // -- non-deterministic, but saved values differ from real values
  f = 0;
  x = nd ();
  sx = nd ();
  sdir = nd ();
  __VERIFIER_assume (x != sx);
  __VERIFIER_assume (sdir != dir);
  
  while (x > 0)
    {

      // -- non-deterministically either save current state, or check
      // -- if current state is different from saved state. The f flag
      // -- ensures that the state is saved at least once before the
      // -- assertion is made
      if (nd ())
      {	f = 1;
        sx = x;
        sdir = dir; }
      else
	assert (!f || (x != sx || dir != sdir));
     
      x = x + dir;
      
      if (x > 10) dir = -1 * dir;
      if (x < 5) dir = -1 * dir;
    }
  
}
