int nd();

void __VERIFIER_error();

int main() {
	int x = nd();
	
	int c;
	if (x <= 0) {
		c = -x;
	} else if (x <= 9) {
		c = 21 - x;
	} else {
		c = x + 1;
	}
	
	while (x != 0) {

		c = c - 1;
		if (! (c >= 0)) __VERIFIER_error();

		if (x < 10) {
			x = x + 1;
		} else {
			x = -x;
		}
	}
	return 0;
}