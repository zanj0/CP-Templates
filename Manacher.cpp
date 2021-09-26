vector<int> manachar(string s)
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

//In case of even palindromes I suggest to use the same code with the string s1#s2#... #sn

// Odd
vector<int> d1 (n);
int l = 0, r = -1;
for (int i = 0; i < n; ++i) {
    int k = (i > r ? 0 : min (d1[l + r - i], r - i)) + 1;
    while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])  ++k;
    d1[i] = k--;
    if (i + k > r)
        l = i - k,  r = i + k;
}
// Even
vector<int> d2 (n);
l = 0, r = -1;
for (int i = 0; i < n; ++i) {
    int k = (i > r ? 0 : min (d2[l + r - i + 1], r - i + 1)) + 1;
    while (i + k - 1 < n && i - k >= 0 && s[i + k - 1] == s[i - k])  ++k;
    d2[i] = --k;
    if (i + k - 1 > r)
        l = i - k,  r = i + k - 1;
}









*********************
#include <bits/stdc++.h>

using namespace std;


template <int delta> struct ManacherBase {
private:
    static const int maxn = 1e5 + 1;
    int r[maxn];
    char s[maxn];
    int mid, n, i;

public:
    ManacherBase(): mid(0), i(0), n(1)
    {
        memset(r, -1, sizeof(int)*maxn);
        s[0] = '$';
        r[0] = 0;
    }

    int get(int pos)
    {
        pos++;
        if (pos <= mid)
            return r[pos];
        else
            return min(r[mid - (pos - mid)], n - pos - 1);
    }

    void addLetter(char c)
    {
        s[n] = s[n + 1] = c;

        while (s[i - r[i] - 1 + delta] != s[i + r[i] + 1])
            r[++i] = get(i - 1);
        r[mid = i]++, n++;
    }

    int maxPal()
    {
        return ( n - mid - 1 ) * 2 + 1 - delta;
    }
} ;

struct Manacher {
private:
    ManacherBase<1> manacherEven;
    ManacherBase<0> manacherOdd;
public:
    void addLetter(char c)
    {
        manacherEven.addLetter(c);
        manacherOdd.addLetter(c);
    }

    int maxPal()
    {
        return max(manacherEven.maxPal(), manacherOdd.maxPal());
    }
    int getRad(int type, int pos)
    {
        if (type)
            return manacherOdd.get(pos);
        else
            return manacherEven.get(pos);
    }
} ;

main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string t;
    while (cin >> t)
    {
        int n = t.size();
        Manacher test;
        for (int i = 0; i < n; i++)
        {
            test.addLetter(t[i]);
            cout << "Arrays for string " << t.substr(0, i + 1) << ":" << endl;
            for (int z = 0; z < 2; z++)
            {
                for (int j = 0; j <= i; j++)
                    cout << test.getRad(z, j) << ' ';
                cout << endl;
            }
        }
        cout << "=========================================" << endl;
    }
}


*********************

https://github.com/ADJA/algos/blob/master/Strings/PalindromeTree.cpp