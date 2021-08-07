vector<int> pal_array(string s)
{
    int n = s.size();
    s = "@" + s + "$";
    vector<int> len(n + 1);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        len[i] = min(r - i, len[l + (r - i)]);
        while (s[i - len[i]] == s[i + len[i]])
            len[i]++;
        if (i + len[i] > r)
        {
            l = i - len[i];
            r = i + len[i];
        }
    }
    len.erase(begin(len));
    return len;
}