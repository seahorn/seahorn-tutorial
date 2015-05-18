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

extern int nd();
#define SZ 16

int a[SZ];

int main (void)
{
  int x = nd();
  signed low = 0, high = SZ;
 
  while (low < high)
  {
    signed middle = low + ((high - low) / 2);
    
    if (a[middle]<x)
      high = middle;
    else if (a [middle] > x)
      low = middle + 1;
    else /* a [middle] == x ! */
      return middle;
  }
 return -1;
}

