
/* 
   
   COMMAND:
   sea pf ptr1.c  -O0 --keep-temp --temp-dir=/tmp/ptr -S --cex=/tmp/cex.xml --log=cex -o /tmp/ptr/out.smt2  --horn-subsumption=false --horn-use-mem-safety=true  
   
   Fails with a counterexample in which the structure is allocated at
   address -4, thus the address of field g is at 0.
   
   The extra constraints added by horn-use-mem-safety do not help in
   this example because the constraints are added only for loads and
   not for every gep instruction.

   COMMAND:
   sea pf ptr1.c  -O0 --keep-temp --temp-dir=/tmp/ptr -S --cex=/tmp/cex.xml --log=cex -o /tmp/ptr/out.smt2  --horn-subsumption=false --horn-use-mem-safety=true -DERR2
   
   Succeeds because the extra load of s->g is enough to trigger
   horn-use-mem-safety to add extra constraints on the base address.
   

   The commands above produce intermediate files in text readable form
   in /tmp/ptr directory. These are useful to understand what compiler
   is doing to the program before it is analyzed.

   The option --horn-subsumption=false is needed to disable some
   preprocessing that otherwise simplifies this example too much.
  
*/
  
extern void __VERIFIER_error (void);
extern void __VERIFIER_assume (int);

#define assume __VERIFIER_assume

struct st
{
  int f;
  int g;
};

/* creates an instance of the struct */
extern struct st* mk(void);

/* a user */
extern void use (int);

void helper (int *h)
{
  if (!h) __VERIFIER_error ();
}



int main(void)
{
  struct st* s;
  s = 0;
  s = mk();
  use (s->f);
#ifdef ERR2
  use (s->g);
#endif
  helper (&(s->g));
  return 42;
}
