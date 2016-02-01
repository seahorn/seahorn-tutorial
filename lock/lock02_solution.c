extern int nd (void);
extern void __VERIFIER_error(void) __attribute__ ((__noreturn__));
extern void __VERIFIER_assume(int);
void __VERIFIER_assert(int v) __attribute__ ((__always_inline__))
{if (!v) __VERIFIER_error ();}

#define assert __VERIFIER_assert
#define assume __VERIFIER_assume

/* Global ghost variable. Keeps the state of the lock. */
int g_lock = 0;

__attribute__((always_inline))
void lock (void) 
{
  /* stub modeling the lock function */
  assert (!g_lock);
  g_lock=1;
}

__attribute__((always_inline))
void unlock (void) 
{
  /* stub modeling the unlock function */
  assert (g_lock);
  g_lock=0;
}

int main (void) 
{
  int request, old, total;
  
  total = nd();
  request = 0;
  do {
    lock ();
    old = total;
    request = nd ();
    if (request)
      {
	unlock ();
	total = total + 1;       
      }
  } while (total != old);

  unlock ();

  return 0;
}

