extern int nd ();


extern void __VERIFIER_error(void);

__attribute__((always_inline))
void assert (int v) 
{if (!v) __VERIFIER_error();}

extern int nd();
int g_lock = 0;

__attribute__((always_inline))
void lock (void) 
{
  assert (!g_lock);
  g_lock=1;
}

__attribute__((always_inline))
void unlock (void) 
{
  assert (g_lock);
  g_lock=0;
}

int main (void) 
{
  int request, old, total;
  
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

