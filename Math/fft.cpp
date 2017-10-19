#include <bits/stdc++.h>
using namespace std;

double const pi = acos(-1);

using cc = complex<double>;
using poly = vector<cc>;

void fft(poly& p, bool inv) {
  // reverse bits
  int n = p.size();
  int logn = 31 - __builtin_clz(n);

  for(int i = 0; i < n; ++i) {
    int idx = 0;
    for(int j = 0; j < logn; ++j)
      if(i >> j & 1)
        idx |= (1 << (logn - j - 1));

    if(idx < i)
      swap(p[idx], p[i]);
  }

  // fft
  for(int m = 2; m <= n; m <<= 1) {
    int k = m >> 1;
    double ang = inv ? -2*pi/m : 2*pi/m;
    cc step(cos(ang), sin(ang));

    for(int j = 0; j < n; j += m) {
      cc w(1);

      for(int i = 0; i < k; ++i, w *= step) {
        auto x = p[j + i];
        auto y = p[j + i + k];
        p[j + i] = x + w * y;
        p[j + i + k] = x - w * y;
      }
    }
  }

  if(inv)
    for(int i = 0; i < n; ++i)
      p[i] /= n;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  string a, b;
  cin >> a >> b;

  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());

  int m = max(a.size(), b.size());
  int n = 1;

  while(n < m)
    n <<= 1;

  n <<= 1;

  poly poly_a(n, 0), poly_b(n, 0), poly_c(n, 0);

  for(size_t i = 0; i < a.size(); ++i)
    poly_a[i] = a[i] - '0';

  for(size_t i = 0; i < b.size(); ++i)
    poly_b[i] = b[i] - '0';

  fft(poly_a, false);
  fft(poly_b, false);

  for(int i = 0; i < n; ++i)
    poly_c[i] = poly_a[i] * poly_b[i];

  fft(poly_c, true);

  int carry = 0;
  string result;
  
  for(int i = 0; i < n; ++i) {
    int x = lround(poly_c[i].real() + carry);
    result.push_back(x%10+'0');
    carry = x / 10;
  }

  reverse(result.begin(), result.end());
  cout << result << endl;
}
