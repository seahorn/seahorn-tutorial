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

#define size 4
int buf[size];
int hi = 0;
int lo = 0;

void enqueue (int x)
{
  int next = (hi + 1) % size;
  
  // -- no more space
  if (next == lo) return;
  
  buf [next] = x;
  hi = next;
}


int dequeue ()
{
  // -- the queue is empty
  if (lo == hi) return -1;
  
  int res = buf [lo];
  lo = (lo + 1) % size;
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
