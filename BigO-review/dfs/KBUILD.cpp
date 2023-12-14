/*
N hon dao, N-1 cay cau;
-> Kiem tra moi cay cau tren duong di tu dao a den dao b (di nhieu ngay)
Co bao nhieu cay cau chua kiem tra?
-> Them canh u, v vao cay de tao chu trinh,
dem so canh chua tham la canh cau do thi
*/

#include <iostream>
#include <vector>

using namespace std;
 
const int maxN = 2e5 + 10;

int n, m;
int timeDfs = 0, bridge = 0;
int low[maxN], num[maxN];
vector <int> g[maxN];
 
void dfs(int u, int pre) {
    num[u] = low[u] = ++timeDfs;
    for (int v : g[u]) {
        if (v == pre) continue;
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] == num[v]) bridge++;
        }
        else low[u] = min(low[u], num[v]);
    }
}
 
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 1);
    cout << bridge;
}
