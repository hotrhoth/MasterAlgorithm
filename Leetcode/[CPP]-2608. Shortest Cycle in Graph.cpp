#include <bits/stdc++.h>
using namespace std;

#define N 10000

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>> &edges) {
        vector<int> gr[N];
        for (auto edge: edges) {
            gr[edge[0]].push_back(edge[1]);
            gr[edge[1]].push_back(edge[0]);
        }
      
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            vector<int> dist(n, (int) (1e9));
            vector<int> par(n, -1);
            dist[i] = 0;
            queue<int> q;
            q.push(i);
          
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int child: gr[x]) {
                    if (dist[child] == (int) (1e9)) {
                        dist[child] = 1 + dist[x];
                        par[child] = x;
                        q.push(child);
                      
                    } else if (par[x] != child and par[child] != x)
                        ans = min(ans, dist[x] + dist[child] + 1);
                }
            }
        }
        if (ans == INT_MAX)
            return -1;
        else
            return ans;
    }
};
