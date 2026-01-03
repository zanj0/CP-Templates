
bool BellmanFord(lli v, lli t, lli n, vector<vector<lli>> &edges, vector<lli> &path)
{
    vector<lli> d(n);
    d[v] = 0;
    vector<lli> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i)
    {
        x = -1;
        for (auto &e : edges)
            if (d[e[0]] < inf)
                if (d[e[1]] > d[e[0]] + e[2])
                {
                    d[e[1]] = max(-inf, d[e[0]] + e[2]);
                    p[e[1]] = e[0];
                    x = e[1];
                    
                }
        // dbg(d);
    }
    if (x == -1)
    {
        return false;
    }

    lli y = x;
    for (lli i = 0; i < n; ++i)
        y = p[y];

    for (lli cur = y;; cur = p[cur])
    {
        path.push_back(cur);
        if (cur == y && path.size() > 1)
            break;
    }
    reverse(path.begin(), path.end());
    
    return true;
}
