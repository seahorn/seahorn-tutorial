/**
 * Check whether main() has a buffer overflow. 
 *
 * Produce a counterexample. Correct. Verify your correction.
 
 * Commands to use:
 *
 * sea pf --do-bounds-check [--inline] [-g --cex=cex.xml --log=cex] queue.c
 **/

extern int nd (void);
extern void __VERIFIER_error() __attribute__ ((__noreturn__));

extern void __VERIFIER_assume(int);
void __VERIFIER_assert(int v) __attribute__ ((__always_inline__))
{if (!v) __VERIFIER_error ();}


#define assume __VERIFIER_assume
#define assert __VERIFIER_assert

#define N 4

int buf[N];
int hi = 0;
int lo = 0;
int size = N;

void enqueue (int x)
{
  buf [hi] = x;
  hi = (hi + 1);
}


int dequeue ()
{
  int res = buf [lo];
  lo = (lo + 1);
  return res;
}

int main (void)
{
  while (nd ())
  {
    if (nd ())
    {
      int x = nd ();
      enqueue (x);
    }
    else
      dequeue ();
  }
  return 0;
}
