Geometry Notes — Cross(a, b, c) / Orientation Test
1. Function Definition (what it computes)
long long Cross(pair<lli, lli> &a, pair<lli, lli> &b, pair<lli, lli> &c) {
    return (b.ff - a.ff) * (c.ss - a.ss)
         - (b.ss - a.ss) * (c.ff - a.ff);
}


a = (ax, ay)

b = (bx, by)

c = (cx, cy)

ff = x-coordinate, ss = y-coordinate in your code

This computes the 2D cross product of vectors AB and AC.

2. Vectors involved

AB = (bx - ax, by - ay)

AC = (cx - ax, cy - ay)

The function does:

Cross(a,b,c) = AB.x * AC.y - AB.y * AC.x
             = (bx-ax)*(cy-ay) - (by-ay)*(cx-ax)

3. Core intuition

Cross(a,b,c) tells you the turn direction when you walk from a → b → c.

It's an orientation test for 3 points.

4. Sign meaning (VERY IMPORTANT)

Cross(a,b,c) > 0

Turn is counterclockwise (left turn).

Point c lies to the left / above the directed line a → b.

Cross(a,b,c) < 0

Turn is clockwise (right turn).

Point c lies to the right / below the directed line a → b.

Cross(a,b,c) == 0

Points a, b, c are collinear (on the same straight line).

This is all you usually need in hull code.

5. Geometric meaning

|Cross(a,b,c)| / 2 = area of triangle △abc.

Bigger absolute value ⇒ "sharper" turn.

0 ⇒ no area ⇒ perfectly straight line.

6. Why convex hull cares

When building an upper convex hull (monotone chain style):

You keep points in increasing x.

Before adding a new point now = c, you look at the last two hull points second_last = a, last = b.

You check Cross(a, b, c).

Typical logic in upper hull:

while (hull.size() >= 2) {
    if (Cross(second_last, last, now) > 0) {
        // left turn => bulges upward => bad for upper hull
        // so remove `last`
        hull.pop_back();
    } else break;
}
hull.push_back(now);


Interpretation:

For the upper hull, we do NOT allow a left turn (Cross > 0).
That means the middle point last was "sticking up" and making the chain non-convex, so we delete it.

We only allow right turns or straight lines (Cross ≤ 0), which gives a downward/outer boundary.

For a lower hull, you'd invert the condition and pop on Cross < 0.

7. Mental picture to remember

Draw arrow from a to b.

Stand on a and face b.

If c is on your left side → Cross > 0.

If c is on your right side → Cross < 0.

If c is straight ahead/back on the same line → Cross = 0.

8. TL;DR cheat lines

Cross(a,b,c) = orientation of (a,b,c).

Sign of cross tells turn direction.

Used to maintain convexity: pop middle point if it creates the wrong turn for the hull you're building.