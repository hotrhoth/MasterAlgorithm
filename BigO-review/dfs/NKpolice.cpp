/*
N thanh pho (duoc danh so 1 -> N), M duong 2 chieu. Hai truy van: yes ? no
1. TP A, B va duong noi G1, G2. Co the di chuyen tu A -> B neu duong noi bi chan?
2. A, B, C. Co the di tu A -> B neu khong the di vao C?
-> Truy van 1: Sau khi bo G1, G2 ? TP A, B co thuoc cung 1 thanh phan lien thong?
    Dinh v nam trong cay con goc u cua dfs: num[u] <= num[v] <= tail[u]
-> Truy van 2: 
    Goi pa la to tien dinh A va la con truc tiep cua C, pb la cua B
    A, B thuoc cung mot thanh phan lien thong sau khi bo C va cac canh lien thuoc C khi
    - Ca hai A, B deu khong nam trong cay con dfs goc C
    - pa == pb la cung mot cay con goc pa
    - Ton tai cung nguoc noi tu cay con dfs goc pa len to tien cua C
    Khi mot diem khong thuoc cay (quan trong) con goc C va mot diem co duong noi
    - Ca hai deu co cung nguoc
*/

#include <iostream>
#include <vector>
using namespace std;

const int maxN = 100010;

int n, m, q;
int timedfs = 0;
int low[maxN], num[maxN], tail[maxN];
int depth[maxN], p[maxN][20]; // depth de chia chieu cao sparse tree
bool joint[maxN];
vector <int> g[maxN];

void calP();
int findParent(int u, int par);
bool checkInSubtree(int u, int root);
bool solve1(int a, int b, int g1, int g2);
bool solve2(int a, int b, int c);

void dfs(int u, int pre) {
    int child = 0;
    num[u] = low[u] = ++timedfs;
    for(int v: g[u]) {
        if(v==pre) continue;
        if(!num[v]) {
            child++;
            p[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(u==pre) { // u la dinh goc cua dfs
                if(child > 1) joint[u] = true;
            } else if(low[v]>=num[u]) joint[u] = true;
        }
        else low[u] = min(low[u], num[v]);

    }
    tail[u] = timedfs;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, v;
    for(int i=1; i<=m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    depth[1] = 1;
    dfs(1, 1);
    calP();
    cin >> q;
    while (q--) {
        int type, a, b, c, g1, g2;
        cin >> type;
        if (type == 1) {
            cin >> a >> b >> g1 >> g2;
            cout << (solve1(a, b, g1, g2) ? "yes\n" : "no\n");
        }
        else {
            cin >> a >> b >> c;
            cout << (solve2(a, b, c) ? "yes\n" : "no\n");
        }
    }

}

void calP() {
    p[1][0] = 1;
    for(int j=1; j<=19; j++) {
        for(int i=1; i<=n; i++) {
            // o i + 2^j = i + 2^(j-1) + 2^(j-1)
            p[i][j] = p[p[i][j-1]][j-1];
        }
    }
}

int findParent(int u, int par) {
    for(int i=19; i>=0; i--) {
        if(depth[p[u][i]] > depth[par]) u = p[u][i];
    }
    return u;
}

bool checkInSubtree(int u, int root) {
    return num[root] <= num[u] && num[u] <= tail[root];
}

bool solve1(int a, int b, int g1, int g2) {
    // doi vi tri g1, g2
    if(num[g1] > num[g2]) swap(g1, g2);
    
    // kiem tra canh cau
    if(low[g2] != num[g2]) return true;
    if (checkInSubtree(a, g2) && !checkInSubtree(b, g2)) return false;
    if (checkInSubtree(b, g2) && !checkInSubtree(a, g2)) return false;
    return true;

}

bool solve2(int a, int b, int c) {
    if(!joint[c]) return true;

    int pa = 0, pb = 0;
    if (checkInSubtree(a, c)) pa = findParent(a, c);
    if (checkInSubtree(b, c)) pb = findParent(b, c);

    if (!pa && !pb) return true; 
    if (pa == pb) return true; 
    if (!pa && low[pb] < num[c]) return true; 
    if (!pb && low[pa] < num[c]) return true;
    if (pa && pb && low[pa] < num[c] && low[pb] < num[c]) return true;

    return false;
}
