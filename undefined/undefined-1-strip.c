#include <stdio.h>

extern void process (int * a);

int main (int argc, char **argv)
{  
  int i, a[10];   
  for (i=0 ; i<10 ; i++) 
    a[i] = i; 
#ifndef BAD  
  a[i-1] = 0;   /* line A: safe array access */
#else
  a[i] = 0;   /* line B: out-of-bound array access*/
#endif

#ifndef SKIPC  
  process (a);  /* line C */
#endif

  return 0; 
}
