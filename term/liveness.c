/* returns a non-deterministic value */ 
extern int nd (void);

extern void __VERIFIER_error (void);

// // original program
// int main() {
// 	int x = nd();
// 	while (1) {
// 		if (x < 10) {
// 			x = x + 1;
// 		} else {
// 			x = -x;
// 		}
// 	}
// 	return 0;
// }

// liveness property: AGAF(x == 0)
int main() {
	
	/**
	** The idea is to add one (or more) counter(s) for each loop
	** which are (lexicographically) strictly decreasing at each loop iteration
	** and then check if the property (in this case, x == 0) is satisfied 
	** of if their value is bounded from below.
	**/
	
	int x = nd();
	
	// -- the value of the counter gives a ranking function;
	// -- in this case the ranking function is
	// -- a piecewise-defined expression depending on x
	int c, reset = 0;
	if (x <= 0) {
		c = -x;
	} else if (x <= 9) {
		c = 21 - x;
	} else {
		c = x + 1;
	}
	
	while (1) {
		
		// -- whenever the property is satisfied, the ranking function should be reset  
		if (x == 0) reset = 1;
		// -- the ranking function is strictly decreasing
		c = c - 1;
		// -- the property x == 0 is satisfied or
		// -- the ranking function is lower bounded by zero
		if (! (x == 0 || c >= 0)) __VERIFIER_error();
		
		if (x < 10) {
			x = x + 1;
		} else {
			x = -x;
		}
		
		// -- the ranking function is reset, because the property was satisfied
		if (reset == 1) {
			reset = 0;
			if (x <= 0) {
				c = -x;
			} else if (x <= 9) {
				c = 21 - x;
			} else {
				c = x + 1;
			}
		}
	}
	return 0;
}