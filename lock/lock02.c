/** Verify whether lock() or unlock() can be called twice in a row */
extern int nd ();

int main (void) 
{
  int request, old, total;
  
  request = 0;
  total = nd();
  do {
    lock ();
    old = total;
    request = nd ();
    if (request)
      {
	unlock ();
	total = total + 1;       
      }
  } while (total != old);

  unlock ();

  return 0;
}


