class Solution {
public:
    string GetUpdatedString(string& s) {
        int n = s.size();
        string ret = "";
        for (int i = 0; i < n; i++) {
            ret += '#';
            ret += s[i];
        }
        ret += '#';
        return ret;
    }

    vector<int> Manachar(string& s) {
        s = GetUpdatedString(s); // Adding '#' before character and after the last character. This is done because the implementation only supports finding the best palindrome length per centre for odd length strings.
        int n = s.size();
        vector<int> palindrome_length(n); // Longest length of the palidrome starting from ith position. Note: Length does not include the current character.
        int right = 0, mirror_character_position = 0, last_palindrome_middle = 0, distance_of_i_from_last_palindrome_middle = 0;

        for (int i = 0; i < n; i++) {

            // Using the precomputed length from the last palindrome.
            distance_of_i_from_last_palindrome_middle = i - last_palindrome_middle;
            mirror_character_position = last_palindrome_middle - distance_of_i_from_last_palindrome_middle;
            if (i <= right) {
                palindrome_length[i] = min(right - i, palindrome_length[mirror_character_position]);
            }

            // Checking for better answer with ith character as the centre.
            int new_left = i - (1 + palindrome_length[i]);
            int new_right = i + (1 + palindrome_length[i]);
            while (new_left >= 0 && new_right < n && s[new_left] == s[new_right]) {
                palindrome_length[i]++;
                new_right++;
                new_left--;
            }

            // 'right' denotes the right most index till which we have found a palindrome. Updating 'right' if 'new_right' exceeds 'right'.
            if (new_right - 1 > right ) {
                right = new_right - 1;
                last_palindrome_middle = i;
            }
        }
        return palindrome_length;
    }

    string GetLongestPalindrome(string& s, vector<int>& longest_palindrome_per_centre) {
        string ret = "";
        int n = s.size();
        int best_length = -1;
        int centre_with_best_length = -1;

        for (int i = 0; i < n; i++) {
            if (longest_palindrome_per_centre[i] > best_length) {
                best_length = longest_palindrome_per_centre[i];
                centre_with_best_length = i;
            }
        }

        for (int i = centre_with_best_length - best_length; i <= centre_with_best_length + best_length; i++) {
            if (s[i] != '#') {
                ret += s[i];
            }
        }
        return ret;
    }

    string longestPalindrome(string s) {
        vector<int> longest_palindrome_per_centre = Manachar(s);
        return GetLongestPalindrome(s, longest_palindrome_per_centre);;
    }
};




== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
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

**************

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

bool IsPalindrome(int l, int r, vector<int>& v) {
    return v[l + r] >= r - l + 1;
}