#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
 
int main() {
	string pattern, text;
	cin >> pattern >> text;
 
	string s = pattern + "$" + text;
 
	int n = s.size();
	int m = pattern.size();
 
	// kmp
	vector<int> k(n);
	for(int i = 1, j = 0; i < n; ++i) {
		while(s[i] != s[j] && j)
			j = k[j-1];
		k[i] = (j += (s[i] == s[j]));
	}
 
	// z
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i < n; ++i) {
		if(i < r)
			z[i] = min(z[i-l], r-i);
		int& len = z[i];
		while(i + len < n && s[len] == s[i + len])
			len++;
		if(i + len > r)
			l = i, r = i + len;
	}
 
	int k_cnt = count(k.begin(), k.end(), m);
	int z_cnt = count(z.begin(), z.end(), m);
 
	assert(k_cnt == z_cnt);
 
	cout << k_cnt << " VS " << z_cnt << endl;
}
