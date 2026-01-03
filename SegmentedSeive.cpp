vector<lli> less_than_equal_root_r_primes;
vector<bool> SegmentedSeive(lli L, lli R)
{
	lli lim = sqrtl(R);
	vector<lli> mark(lim + 1, false);
	vector<lli> primes;
	for (lli i = 2; i <= lim; i++)
	{
		if (!mark[i])
		{
			primes.push_back(i);
			for (lli j = i * i; j <= lim; j += i)
			{
				mark[j] = true;
			}
		}
	}
	less_than_equal_root_r_primes = primes;
	lli n = R - L + 1;
	vector<bool> ret(n, true);

	for (auto &p : primes)
	{
		for (lli i = max(p * p, ((L + p - 1) / p) * p); i <= R; i += p)
		{
			ret[i - L] = false;
		}
	}
	if (L == 1)
		ret[0] = false;

	return ret;
}