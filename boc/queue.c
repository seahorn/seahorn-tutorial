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
extern int nd ();

int buf[4];
int hi = 0;
int lo = 0;
int size = 4;

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
