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
	
	// manacher's
	string p(2*n+1, '*');
	for(int i = 0; i < n; ++i)
		p[2*i+1] = s[i];
	n = 2*n+1;
	vector<int> man(n);
	for(int i = 0, c = 0, r = 0; i < n; ++i) {
		if(i < r)
			man[i] = min(man[c - (i - c)], r-i);
		int& rad = man[i];
		while(0 <= i - rad && i + rad < n && p[i-rad] == p[i+rad])
			rad++;
		if(i + rad > r)
			c = i, r = i + rad;
	}
	
	int k_cnt = count(k.begin(), k.end(), m);
	int z_cnt = count(z.begin(), z.end(), m);
	int longest_palindrome = *max_element(man.begin(), man.end()) - 1;
	
	assert(k_cnt == z_cnt);
	assert(longest_palindrome == 9);
	
	cout << k_cnt << " VS " << z_cnt << endl;
	cout << "Longest palindrome length = " << longest_palindrome << endl;
}
