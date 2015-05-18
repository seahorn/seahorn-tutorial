/** Verify whether lock() or unlock() can be called twice in a row */

extern int nd();
void lock (void);
void unlock (void);


void lock1 (void)
{
  int in_irq;
  int buf[10];
  int i;
  
  
  if (in_irq) 
    lock ();
  
  for (i = 0; i < 5; i++)
    buf [i] = nd();

  if (in_irq)
    lock ();
}





