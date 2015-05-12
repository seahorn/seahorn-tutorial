/* returns a non-deterministic value */ 
extern int nd (void);

extern void __VERIFIER_error (void);

// // -- original program
// int main() {
// 	int x = nd(), y = nd();
// 	while (x > 0 && y > 0) {
// 		if (nd()) {
// 			x = x - 1;
// 			y = nd();
// 		} else {
// 			y = y - 1;
// 		}
// 	}
// 	return 0;
// }

int main() {
	
	/**
	** The idea is to add one or more counters for each loop
	** which are lexicographically strictly decreasing at each loop iteration
	** and then check if their value is bounded from below.
	**/
	
	int x = nd(), y = nd();
	
	// -- the value of the counters gives a ranking function;
	// -- in this case the ranking function is
	// -- a tuple (c1,c2) of expressions depending on x and y
	int c1 = x, c2 = y;
	
	while (x > 0 && y > 0) {
		
		// -- the ranking function is lexicographically strictly decreasing
		if (c2 <= 0) {
			c1 = c1 - 1;
			c2 = y;
		} else {
			c2 = c2 - 1;
		}
		// -- the ranking function is lower bounded by zero
		if (! (c1 >= 0)) __VERIFIER_error();
		
		if (nd()) {
			x = x - 1;
			y = nd();
		} else {
			y = y - 1;
		}
	}
	return 0;
}