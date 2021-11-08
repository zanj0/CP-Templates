int mult(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }
    if (a == inf || b == inf)
    {
        return inf;
    }
    int p = a * b;
    if (p % a == 0 && p / a == b && p <= inf)
    {
        return p;
    }
    else
    {
        return inf;
    }
}

int cmmmc(int a, int b)
{
    if (a == inf || b == inf)
    {
        return inf;
    }
    return mult(a / __gcd(a, b), b);
}