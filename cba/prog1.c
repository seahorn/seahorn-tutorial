/**
 * Two-threaded programs with entry points thread1() and thread2()
 */

int x, y;


void thread1 ()
{
  int lx, ly;

  int oldx, newx;

  lx = x;       /* read x */
  oldx = lx;

  y = 1;       /* set y to 1 */
  ly = y;      /* read y */
  
  lx += ly;    /* inc lx */
 
  x = lx;      /* write x */
  newx = x;    /* read x */
  
  assert (oldx < newx);  /* assert that x increased */
  
}

void thread2 ()
{
  y = -1;     /* write y */
}

void main (void)
{
  /** assume x is positive and not too large */
  __CPROVER_assume (x > 0);
  __CPROVER_assume (x < INT_MAX - 1);
  
  /** run threads (not real pthreads syntax) */
  pthread_create (&thread1);
  pthread_create (&thread2);
    
}
