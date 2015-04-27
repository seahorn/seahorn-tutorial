int nd();

void __VERIFIER_error();

int main() {
	int x = nd(), y = nd();
	
	int c1 = x, c2 = y;
	
	while (x > 0 && y > 0) {
		
		if (c2 <= 0) {
			c1 = c1 - 1;
			c2 = y;
		} else {
			c2 = c2 - 1;
		}
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