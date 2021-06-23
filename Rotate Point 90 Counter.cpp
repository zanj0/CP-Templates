pair <int, int> move(pair <int, int>& p, pair <int, int>& q) {
	p.ff -= q.ff;
	p.ss -= q.ss;
	int ff = -p.ss;
	int ss = p.ff;
	p.ff = ff;
	p.ss = ss;
	p.ff += q.ff;
	p.ss += q.ss;
	return p;
}