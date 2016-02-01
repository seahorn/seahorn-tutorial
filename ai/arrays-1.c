// This is an excerpt of automatically code generate from Simulink.
// It is from the TCS (thermal control system) module in Laddee onboard flight system

// The TCS has a map from heater ids to sensor values. These values
// can be in some small range (0: OFF, 1:ON, 2: MANUAL). All the
// sensor values are OFF initially. During operation, the sensor
// values can only be updated to one of these 0...2 values.

#include <stdlib.h>

extern void __VERIFIER_assume (int);
extern void __VERIFIER_error (void);
__attribute__((always_inline)) void assert (int v)  { if (!v) __VERIFIER_error (); }

extern int nd ();

#define N 1000

// --- This is actually how Simulink translates the input/outputs of
//     the models to C: taking the address of a global variable and
//     pass the address to all functions.
struct table {
  int x;
  int a[N];
};
struct table _t;
struct table * t = &_t;

int main ()
{  
  int i,j,v;

  for (i=0;i<N;i++)
    t->a[i] = 0;

  for (i=0;i<N;i++)
  {
    v = nd ();    
    if (nd () && (v >= 0 && v <= 2))
      t->a[i] = v;
  }

  for (j=0;j<N;j++)  
    assert (t->a[j] >= 0 && 
            t->a[j] <= 2);

  return 42;
}
