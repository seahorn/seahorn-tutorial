/**
 * Check whether main() has a buffer overflow. 
 *
 * Produce a counterexample. Correct. Verify your correction.
 
 * Commands to use:
 *
 * # compile
 * sea clang -S -o queue.ll queue.c
 * # instrument with buffer-overflow checks (BOC)
 * sea pp --boc -S -q queue.boc.ll queue.ll
 * # verify
 * sea pf --cex=trace.xml --inline queue.boc.ll 2>&1 | q.log
 * 
 * See q.log for a counterexample and the program being verified
 **/

#include <stdlib.h>
#include <stdio.h>

extern int nd ();

int buf[4];
int hi = 0;
int lo = 0;
int size = 4;

void enqueue (int x)
{
  if (hi >= size) 
  {
    printf ("Error queue overflow");
    exit (EXIT_FAILURE);    
  }

  buf [hi] = x;
  hi = (hi + 1);
}


int dequeue ()
{
  if (lo >= hi) 
  {
    printf ("Error queue underflow");
    exit (EXIT_FAILURE);
  }

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
