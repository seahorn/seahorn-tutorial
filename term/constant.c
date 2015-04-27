int nd();

void __VERIFIER_error();

int main() {
	int x = nd();
	
	int c = 4;
	
	while (x >= 0) {
		
		c = c - 1;
		if (! (c >= 0)) __VERIFIER_error();
		
		x = - 2 * x + 10;
	}
	return 0;
}