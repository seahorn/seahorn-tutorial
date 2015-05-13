int unknown(void);

extern void __VERIFIER_assume (int);
extern void __VERIFIER_error (void);
void assert (int v) { if (!v) __VERIFIER_error (); }
#define assume __VERIFIER_assume
#define static_assert assert

/*
 * Adapted from ex17.c in NECLA test suite
 */

int main(void) {
   int b;
   int j = 0;
   int flag = unknown();

   for (b=0; b < 100 ; ++b){
      if (flag)
         j = j +1;
   }


   if(flag)
      static_assert(j==100);

   return 0;
}
