#include<seahorn/seahorn.h>
extern int nd();

int g_lock = 0;

__attribute__((always_inline))
void lock (void) 
{
  sassert (!g_lock);
  g_lock=1;
}

__attribute__((always_inline))
void unlock (void) 
{
  sassert (g_lock);
  g_lock=0;
}


int main (void)
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

 return 0;
}
