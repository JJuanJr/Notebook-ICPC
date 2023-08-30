int gray(int n) { return n ^ (n >> 1); }

int revert_gray(int gray) {
	int n = 0;
	for (; gray; gray >>= 1)
		n ^= gray;
	return n;
}
