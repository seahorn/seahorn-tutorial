#include "seahorn/seahorn.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/**
 ** Prove all array accesses of "a" and "b" are in-bounds
 **  The idea is choose non-deterministically a pointer and keep track
 **  of the base address and size of the region to which the pointer
 **  points to.
 **  The solver takes care of resolving the non-determinism.
*/

#define N 5

typedef ptrdiff_t sea_ptrdiff_t;
typedef ptrdiff_t sea_size_t;

extern int nd(void);
extern int8_t *nd_int8_ptr (void);
extern sea_size_t nd_sea_size_t (void);

// -- non-deterministic (positive) base address of a non empty allocation site
static int8_t* base;
// -- a valid address between [base,...,base+size)
static int8_t* ptr;
// -- numerical difference between ptr and base
static sea_ptrdiff_t offset;
// -- size of the allocated regiony
static sea_size_t size;

int main(int argc, char**argv)
{

  // -- init
  base = nd_int8_ptr ();
  assume (base > 0);
  size = nd_sea_size_t ();
  assume (size >= 0);
  ptr = 0;
  offset = 0;

  int8_t a[N];

  // -- allocation of a
  int8_t *b_a  = &(a[0]);
  if (!ptr  && (b_a == base)) {
    // ptr = base;
    ptr = nd_int8_ptr ();
    assume (ptr == base);
    assume (size == sizeof(int8_t) * N);
    offset = 0;
  } else {
    assume (base+size < b_a);
  }

  int i=0;
  int8_t* q_a = b_a;
  for (; i < N; i++, q_a++) {
    // -- pointer arithmetic
    if (nd() && (q_a == ptr)) {
      ptr = nd_int8_ptr ();
      assume (ptr == (q_a + 1));
      offset += 1;
    }
    // -- a[i] = i;
    *q_a = i;
  }

  int8_t b[N];
  int8_t *b_b  = &(b[0]);

  // -- allocation of b
  if (!ptr  && (b_b == base)) {
    // ptr = base;
    ptr = nd_int8_ptr ();
    assume (ptr == base);
    assume (size == sizeof(int8_t) * N);
    offset = 0;
  } else {
    assume (base+size < b_b);
  }

  int j=0;
  int8_t* q_b = b_b;
  for (; j < N; j++, q_b++) {
    // -- pointer arithmetic
    if (nd() && (q_b == ptr)) {
      ptr = nd_int8_ptr ();
      assume (ptr == (q_b + 1));
      offset += 1;
    }
    // -- b[j] = j;
    *q_b = j;
  }

#ifndef ERROR
  // -- safe memory access
  if (ptr && (ptr  == (b_a + (i-1)))) {
    sassert (offset < size);
  }
  printf("%d\n", a[i-1]);

  // -- safe memory access
  if (ptr && (ptr  == (b_b + (j-1)))) {
    sassert (offset < size);
  }
  printf("%d\n", b[j-1]);

#else
  // -- safe memory access
  if (ptr && (ptr  == (b_a + (i-1)))) {
    sassert (offset < size);
  }
  printf("%d\n", a[i-1]);

  // -- unsafe memory access
  if (ptr && (ptr  == (b_b + j))) {
    sassert (offset < size);
  }
  printf("%d\n", b[j]);

#endif
  return 0;
}
