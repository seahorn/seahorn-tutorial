int nd();

void __VERIFIER_error();

/* AGAF(x == 0) */
int main() {
	int x = nd();
	
	int c, reset = 0;
	if (x <= 0) {
		c = -x;
	} else if (x <= 9) {
		c = 21 - x;
	} else {
		c = x + 1;
	}
	
	while (1) {
		
		if (x == 0) reset = 1;
		c = c - 1;
		if (! (x == 0 || c >= 0)) __VERIFIER_error();
		
		if (x < 10) {
			x = x + 1;
		} else {
			x = -x;
		}
		
		if (reset == 1) {
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