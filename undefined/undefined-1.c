/* 

   This program shows how modern compilers rely on undefined behaviour
   in order to optimize code which can produce surprising results for
   analyzers and verifiers.

   We will use buffer overflow as our property.

   The program is initially safe since all the array accesses are
   between 0 and 9 and our array "a" has size of 10. Try the commands:

   sea clang undefined-1.c -o undefined-1.bc
   sea pp undefined-1.bc --boc -o undefined-1.pp.bc
   sea horn undefined-1.pp.bc --solve 
   > unsat

   This confirms that our program is safe.
   Now, let us comment line A and uncomment B and try again:

   sea clang undefined-1.c -o undefined-1.bc
   sea pp undefined-1.bc --boc -o undefined-1.pp.bc
   sea horn undefined-1.pp.bc --solve 
   > sat

   The program is now unsafe because it has an out-of-bound array
   access at line B because i is 10.

   Finally, let us comment line C and try again the same commands:

   sea clang undefined-1.c -o undefined-1.bc
   sea pp undefined-1.bc --boc -o undefined-1.pp.bc
   sea horn undefined-1.pp.bc --solve 
   > unsat

   The program is again safe but note that we still have the out-bound
   array access at line B. A fair question is: Is SeaHorn unsound?

   The issue here is that the compiler notices that the array "a" is
   dead code and therefore it removes all the array accesses from the
   program. You might say that the compiler should not do this since
   there is an out-of-bound access. However, the compiler is free to
   do it since this is undefined behaviour. The C standard allows
   compilers to do whatever they want in this kind of situations. LLVM
   decides to remove the access.

   Coming back to our question, Seahorn is sound since Seahorn
   verifies LLVM bitecode and not the original C program.

*/

#include <stdio.h>

extern void process (int * a);

int main (int argc, char **argv)
{  
  int i, a[10];   
  for (i=0 ; i<10 ; i++) 
  {
    a[i] = i; 
  }
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
