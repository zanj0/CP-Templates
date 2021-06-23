int distSq(const pair <int, int>&  p, const pair <int, int>&  q)
{
	return (p.ff - q.ff) * (p.ff - q.ff) + (p.ss - q.ss) * (p.ss - q.ss);
}

// This function returns true if (p1, p2, p3, p4) form a
// square, otherwise false
bool isSquare(const pair <int, int>&  p1, const pair <int, int>&  p2, const pair <int, int>&  p3, const pair <int, int>&  p4)
{
	int d2 = distSq(p1, p2); // from p1 to p2
	int d3 = distSq(p1, p3); // from p1 to p3
	int d4 = distSq(p1, p4); // from p1 to p4

	if (d2 == 0 || d3 == 0 || d4 == 0)
		return false;

	// If lengths if (p1, p2) and (p1, p3) are same, then
	// following conditions must met to form a square.
	// 1) Square of length of (p1, p4) is same as twice
	// the square of (p1, p2)
	// 2) Square of length of (p2, p3) is same
	// as twice the square of (p2, p4)

	if (d2 == d3 && 2 * d2 == d4
	        && 2 * distSq(p2, p4) == distSq(p2, p3)) {
		return true;
	}

	// The below two cases are similar to above case
	if (d3 == d4 && 2 * d3 == d2
	        && 2 * distSq(p3, p2) == distSq(p3, p4)) {
		return true;
	}
	if (d2 == d4 && 2 * d2 == d3
	        && 2 * distSq(p2, p3) == distSq(p2, p4)) {
		return true;
	}

	return false;
}