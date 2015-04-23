#include <limits.h>

extern void __VERIFIER_assume(int);
extern void __VERIFIER_error(void);
void assert (int v) {if (!v) __VERIFIER_error ();}

/** Total number of rounds */
#define R 3
/** rounds */
char r;

char x[R], y[R];   /** global varialbes */
char ix[R], iy[R]; /** initial global values */

char saved_assert = 1;

char nondet_char (void);
void cs(void);
void thread1 (void);
void thread2 (void);



int main (void)
{
  char i;
  for (i = 0; i < R; i++)
    {
      x[i] = ix[i] = nondet_char ();
      y[i] = iy[i] = nondet_char ();
    }
  
  __VERIFIER_assume (x[0] > 0);
  __VERIFIER_assume (x[0] < CHAR_MAX - 1);

  r = 0;
  thread1();
  
  r = 0;
  thread2();

  /** check assumptions */
  for (i = 0; i < R - 1; i++)
    {
      __VERIFIER_assume (x[i] == ix[i+1]);
      __VERIFIER_assume (y[i] == iy[i+1]);
    }
  
  /** check assertion */
  assert (saved_assert);
  return 0;
}

void thread1 ()
{
  char lx, ly;

  char oldx, newx;

  cs ();
  lx = x[r];       /* read x */
  oldx = lx;

  cs ();
  y[r] = 1;       /* set y to 1 */
  
  cs ();
  ly = y[r];      /* read y */
  
  lx += ly;      /* inc lx */
 
  cs ();
  x[r] = lx;      /* write x */

  cs ();
  newx = x[r];    /* read x */
  
  saved_assert = (oldx < newx);  /* assert that x increased */
}

void thread2 ()
{
  cs ();
  y[r] = -1;
}


void cs()
{
  char oldr;
  
  if (nondet_char()) return;
  
  oldr = r;
  r = nondet_char ();
  __VERIFIER_assume (r > oldr);
  __VERIFIER_assume (r < R);
  
}

