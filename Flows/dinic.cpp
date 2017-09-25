#include <bits/stdc++.h>
using namespace std;

template<class T = long long>
struct dinic {
  using edge = tuple<int,T,int>;
  using real_edge = tuple<int,int,T,bool>;

  int n, m;
  vector<int> q;
  vector<int> idx;
  vector<int> dist;
  vector<vector<edge>> g;
  vector<real_edge> graph_edges;

  void add_edge(int u, int v, int c, bool undirected) {
    if(u != v)
      graph_edges.emplace_back(u, v, c, undirected);
  }

  void build() {
    n = 0;
    m = graph_edges.size() * 2;
    for(auto const& e : graph_edges)
      n = max({n, get<0>(e), get<1>(e)});

    g.resize(n+1);
    q.resize(n+1);
    idx.resize(n+1);
    dist.resize(n+1);

    for(auto const& e : graph_edges) {
      T c;
      int u, v;
      bool rev;
      tie(u, v, c, rev) = e;

      int u_size = g[u].size();
      int v_size = g[v].size();

      g[u].emplace_back(v, c, v_size);
      g[v].emplace_back(u, c*rev, u_size);
    }
  }

  bool bfs(int s, int t) {
    int inf = n+n+n;
    fill(dist.begin(), dist.end(), inf);
    int l = 0, r = 0;
    dist[s] = 0;
    for(q[r++] = s; l < r; ++l) {
      int u = q[l];
      for(auto const& e : g[u]) {
        T c;
        int v;
        tie(v, c, std::ignore) = e;
        if(c && dist[v] > dist[u] + 1) {
          dist[v] = dist[u] + 1;
          q[r++] = v;
        }
      }
    }
    return dist[t] != inf;
  }

  T dfs(int u, int t, T f) {
    if(u == t)
      return (f <= 0 ? 0 : f);

    for(int& i = idx[u]; i < g[u].size(); ++i) {
      int v, rev;
      T& c = get<1>(g[u][i]);
      tie(v, ignore, rev) = g[u][i];

      if(not (c) || not (dist[v] == dist[u] + 1))
        continue;

      T x = dfs(v, t, f < 0 ? c : min(f, c));

      if(x > 0) {
        T& c_rev = get<1>(g[v][rev]);
        c -= x;
        c_rev += x;
        return x;
      }
    }
    return 0;
  }

  T max_flow(int s, int t) {
    build();

    T flow = 0;

    while(bfs(s, t)) {
      fill(idx.begin(), idx.end(), 0);
      while(int f = dfs(s, t, -1))
        flow += f;
    }

    return flow;
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  dinic<long long> flow;
  for(int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    flow.add_edge(u, v, c, true);
  }

  cout << flow.max_flow(1, n);
}
