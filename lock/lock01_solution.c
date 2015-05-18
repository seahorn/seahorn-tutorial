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


void main (void)
{
  int in_irq;
  int buf[10];
  int i;
  
  in_irq = nd();
  
  if (in_irq) 
    lock ();
  
 for (i = 0; i < 5; i++)
    buf [i] = nd();

  if (in_irq)
    lock ();
}
