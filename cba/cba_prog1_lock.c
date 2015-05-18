#include <limits.h>

extern void __VERIFIER_assume(int);
extern void __VERIFIER_error(void);
void assert (int v) {if (!v) __VERIFIER_error ();}

/** total number of rounds (i.e., context-switches */
#define R 3
/** current round */
char r;

char x[R], y[R];   /** global varialbes */
char ix[R], iy[R]; /** initial global values */

/** saved value of the assertion */
char saved_assert = 1;

/** nondeterministic character */
char nondet_char ();
/* context switch */
void cs();

/** entry point of thread 1 */
void thread1 ();
/** entry point of thread 2 */
void thread2 ();

/** global lock, 1 when held */
char lock = 0;
/** lock/unlock functions */
void Lock ();
void Unlock ();


int main (void)
{
  char i;

  /** initialize global state */
  for (i = 0; i < R; i++)
    {
      x[i] = ix[i] = nondet_char ();
      y[i] = iy[i] = nondet_char ();
    }
  
  /** initial assumptions on x */
  __VERIFIER_assume (x[0] > 0);
  __VERIFIER_assume (x[0] < CHAR_MAX - 1);

  /** start in round 0 and run thread1 */
  r = 0;
  thread1();
  
  /** start in round 0 and run thread2 */
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

/** body of thread 1 */
void thread1 ()
{
  char lx, ly;

  char oldx, newx;
  
  Lock ();
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
  Unlock ();
  
  saved_assert = (oldx < newx);  /* assert that x increased */
}

/** body of thread 2*/
void thread2 ()
{
  cs ();
  y[r] = -1;
}

/** context switch */
void cs()
{
  char oldr;
  
  if (lock) return;
  if (nondet_char()) return;
  
  oldr = r;
  r = nondet_char ();
  __VERIFIER_assume (r > oldr);
  __VERIFIER_assume (r < R);
  
}

/** acquire the lock  */
void Lock () { lock = 1; }
/** release the lock */
void Unlock () { lock = 0; }

