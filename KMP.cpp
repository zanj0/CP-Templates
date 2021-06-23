#include <bits/stdc++.h>
using namespace std;
vector <int> calculateLPS(string s) {
    vector <int> lps(s.size());
    int i = 1, j = 0;
    while (i < s.size()) {

        while (j &&  s[i] != s[j]) {
            j = lps[j - 1];
        }
        if (s[i] == s[j]) {
            lps[i] = j + 1;
            j++;
        }
        i++;

    }
    return lps;
}
int main() {
    return 0;
}