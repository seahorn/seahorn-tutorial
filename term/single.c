int nd();

void __VERIFIER_error();

int main() {
	int x = nd();
	
	int c = 11 - x;
	
	while (x <= 10) {
		
		c = c - 1;
		if (! (c >= 0)) __VERIFIER_error();
		
		x = x + 1;
	}
	return 0;
}