/*
	JAI JAGANNATH!
*/
//@Author : zanj0

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set =  __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define LOCAL
#define ff              first
#define ss              second
#define pb              push_back
#define MOD             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
#define endl       		"\n"
#define timetaken cerr<<"Time : "<<1000*(long double)clock()/(long double)CLOCKS_PER_SEC<<"ms\n"

typedef long long int lli;

void zanj0()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
void Out(vector<int>& v){
	for(auto& it : v){
		cout << it << " ";
	}
	cout << endl;
}

// Suffix Array - Start
// Refer - https://cp-algorithms.com/string/suffix-array.html
const int ALPHABETS = 256;
vector<int> SortCyclicShifts(string const& s) {
  int n = s.size();
  vector<int> sorted_indices(n), equivalence_classes(n);
  vector<int> cnt(max(ALPHABETS, n), 0);

  for (int i = 0; i < n; i++) {
    cnt[s[i]]++;
  }

  for (int i = 1; i < ALPHABETS; i++) {
    cnt[i] += cnt[i - 1];
  }

  for (int i = 0; i < n; i++) {
    sorted_indices[--cnt[s[i]]] = i;
  }

  equivalence_classes[sorted_indices[0]] = 0;

  int equivalence_class = 1;
  for (int i = 1; i < n; i++) {
    if (s[sorted_indices[i]] != s[sorted_indices[i - 1]]) equivalence_class++;
    equivalence_classes[sorted_indices[i]] = equivalence_class - 1;
  }

  vector<int> sorted_indices_temporary(n), equivalence_classes_temporary(n);
  for (int length_power = 0; (1 << length_power) < n; length_power++) {
    for (int i = 0; i < n; i++) {
      sorted_indices_temporary[i] = sorted_indices[i] - (1 << length_power);
      if (sorted_indices_temporary[i] < 0) {
        sorted_indices_temporary[i] += n;
      }
    }

    fill(cnt.begin(), cnt.begin() + equivalence_class, 0);

    for (int i = 0; i < n; i++) {
      cnt[equivalence_classes[sorted_indices_temporary[i]]]++;
    }
    for (int i = 1; i < equivalence_class; i++) {
      cnt[i] += cnt[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
      sorted_indices[--cnt[equivalence_classes[sorted_indices_temporary[i]]]] =
          sorted_indices_temporary[i];
    }

    equivalence_classes_temporary[sorted_indices[0]] = 0;

    equivalence_class = 1;

    for (int i = 1; i < n; i++) {
      pair<int, int> curr = {
          equivalence_classes[sorted_indices[i]],
          equivalence_classes[(sorted_indices[i] + (1 << length_power)) % n]};
      pair<int, int> prev = {
          equivalence_classes[sorted_indices[i - 1]],
          equivalence_classes[(sorted_indices[i - 1] + (1 << length_power)) %
                              n]};
      if (prev != curr) equivalence_class++;
      equivalence_classes_temporary[sorted_indices[i]] = equivalence_class - 1;
    }
    equivalence_classes.swap(equivalence_classes_temporary);
  }

  return sorted_indices;
}

vector<int> SuffixArrayConstruction(string s) {
  s += '$';
  vector<int> sorted_shifts = SortCyclicShifts(s);
  sorted_shifts.erase(sorted_shifts.begin());
  return sorted_shifts;
}
// Suffix Array - End

bool IsSmallOrEqual(string& from, string& to, int to_l, int to_r){
	int len_to = to_r - to_l + 1;
	int j = to_l;
	for(int i = 0; i <min((int)from.size(), len_to); i++ ){
		if(from[i] > to[j]) return false;
		if(from[i] < to[j]) return true;
		j++;
	}
	return (int)from.size() <= len_to;
}
int FindStringsLowerBound(string& s, string& original_string, vector<int>& suffix_array){
	int ret = original_string.size();
	int low = 0, high = suffix_array.size() - 1;
	while(low <= high){
		int mid = low + (high - low) / 2;
		
		
		if(IsSmallOrEqual(s, original_string, suffix_array[mid], original_string.size() - 1)){
			ret = mid;
			high = mid - 1;
		}else low = mid + 1;
		
	}
	return ret;
}

void Solve(){
	string s;
	cin >> s;
	vector<int> suffix_array = SuffixArrayConstruction(s);
	
	int q;
	cin >> q;

	while(q--){
		string x;
		cin >> x;
		
		
		int b = FindStringsLowerBound(x, s, suffix_array);
		x += '~';
		int a = FindStringsLowerBound(x, s, suffix_array);
		
		cout <<  a - b << endl;
	}
	

}
int32_t main()
{
	zanj0();
	Solve();
	timetaken;
	return 0;
}