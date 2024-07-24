lli Sqt(const lli n) {
	lli r = (lli)(sqrt(n));
	while (r * r < n)
		r++;
	while (r * r > n)
		r--;
	return r;
}