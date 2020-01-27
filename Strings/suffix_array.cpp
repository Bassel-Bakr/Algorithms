#include<bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> suf_con(string const& s) {
  int n = s.size();
  
  if(n == 0)
    return {};
  
  vector<int> cnt;
  vector<int> sa(n);
  vector<int> tmp(n);
  vector<int> rank[2];
  rank[0].resize(n);
  rank[1].resize(n);
  
  iota(sa.begin(), sa.end(), 0);
    
  // initial rank
  for(int i = 0; i < n; ++i)
    rank[0][sa[i]] = s[sa[i]];
    
  for(int len = 0; len < n; len = max(1, 2 * len)) {
    // calculate 2nd rank
    for(auto x : sa) {
      int next = x + len;
      rank[1][x] = (next < n) ? rank[0][next] : 0;
    }
    
    // radix sort
    int m = 1;
    if(len)
      m += rank[0][sa.back()];
    else
      m += *max_element(rank[0].begin(), rank[0].end());
    
    for(int r = 1; r >= 0; --r) {
      swap(sa, tmp);
      cnt.assign(m, 0);
      for(auto x : tmp)
        ++cnt[rank[r][x]];
      for(int i = 0, sum = 0; i < m; ++i) {
        sum += cnt[i];
        cnt[i] = sum - cnt[i];
      }
      for(auto x : tmp)
        sa[cnt[rank[r][x]]++] = x;
    }
    
    // calculate 1st rank and pos
    for(int i = 0, j = 0, k = 1; i < n; i = j, ++k) {
      int r0 = rank[0][sa[i]];
      int r1 = rank[1][sa[i]];
      while(j < n && r0 == rank[0][sa[j]] && r1 == rank[1][sa[j]])
        rank[0][sa[j++]] = k;
    }
    
    // done?
    if(rank[0][sa.back()] == n)
      break;
  }
  
  return sa;
}

int main()
{
  cin.tie(0);
  cin.sync_with_stdio(0);

  string s = "banana";
  
  auto sa = suf_con(s);
  
  for(int i = 0; i < int(s.size()); ++i)
    cout << sa[i] << ' ' << s.substr(sa[i], s.size()) << endl;
}
