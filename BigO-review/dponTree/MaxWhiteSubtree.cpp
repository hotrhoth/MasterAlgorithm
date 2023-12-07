#include <bits/stdc++.h>
using namespace std;
/*
n dinh, undirected n-1 edges
av = white 1 v black 0
-> max of diff white-black of subtree that contains vertex i
*/
int n;
vector <int> col, indp, outdp;
vector <vector<int>> g;

void dfsin(int node, int par) {
  if(col[node]==1) indp[node] = 1;
  else indp[node] = -1;
  for(auto &v: g[node]) {
    if(v!=par) {
      dfsin(v,node);
      indp[node] += max(0, indp[v]);
    }
  }
}

void dfsout(int node, int par, int outval) {
  outdp[node] = outval;
  for(auto &v: g[node]) {
    if(v!=par) {
      int outvaldash = max(0, outval + indp[node] - max(0, indp[v]));
      dfsout(v,node,outvaldash);
    }
  }
}

int main() {
  cin >> n;
  col.clear(); col.resize(n+1);
  g.clear(); g.resize(n+1);
  for(int i=1; i<=n; i++) cin >> col[i];
  for(int i=0; i<n-1; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  indp.clear(); indp.resize(n+1);
  outdp.clear(); outdp.resize(n+1);
  dfsin(1,1);
  dfsout(1,1,0);
  for(int i=1; i<=n; i++) cout << indp[i] + outdp[i] << " ";
  cout << "\n";
}
