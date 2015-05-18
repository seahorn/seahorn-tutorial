/**
 * Example that benefits from the mix of abstract interpretation and PDR
 *
 * # does not solve
 * sea pf ex01.c
 *
 * # does not solve
 * sea pf -O0 ex01.c
 *
 * # abstract interpretation + optimization
 * sea pf --horn-ikos ex01.c
 *
 * # abstract interpretation + pdr
 * sea pf --horn-ikos -O0 ex01.c
 */

int nd();
void __VERIFIER_error(void);

__attribute__((always_inline))
void assert (int v) {if (!v) __VERIFIER_error ();}

int main(void)
{
  
  int x = 1;
  int y = 0;
  
  while (nd ())
  {
    x = x + y;
    y = y + 1;
  }
  assert(x >= y);
  return 0;
}
