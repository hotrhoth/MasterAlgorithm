/*
Thành phần liên thông mạnh trong đồ thị có hướng:
- Từ một đỉnh bất kì luôn tồn tại ít nhất một đường đi đến bất kì đỉnh khác;
- Nếu một thành phần liên thông mạnh được co lại thành một đỉnh,
thì đồ thị sẽ trở thành một đồ thị có hướng không có chu trình;
- Tarjan tuyến tính 1 lần (Ngoài ra Kosaraju, Gabow);

-> Định lí 1: A, B thuộc thành phần liên thông mạnh C,
tất cả các đỉnh trên đường đi của A và B đều thuộc C;

-> Định lí 2: Nếu duyệt đỉnh r trước tiên, tồn tại r sao cho
mọi đỉnh C đều thuộc cây con gốc r trong dfs (gọi là chôt của C)

-> Định lí 3: luôn tìm đc đỉnh chốt a thoả mãn: chiều sâu bắt đầu
từ a không thăm đc bất kì một chốt nào khác;
*/

/*  Thuật toán Tarjan
-> Mảng low[], num[], 
duyệt từng đỉnh và bỏ vào stack,
tìm đc đỉnh num[u] == low[u] thì đây chính là đỉnh có thứ
tự thăm sớm nhất của tp liên thông mạnh;
*/

/*  Tim thanh phan lien thong manh
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int maxN = 100010;

int n, m, timedfs = 0, scc = 0;
int low[maxN], num[maxN];
bool deleted[maxN];
vector <int> g[maxN];
stack <int> st;

void dfs(int u);

int main() {
    cin >> n >> m;
    int u, v;
    for(int i=1; i<=m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    for(int i=1; i<=n; i++)
        if(!num[i]) dfs(i);

    cout << scc;
}

void dfs(int u) {
    num[u] = low[u] = ++timedfs;
    st.push(u);
    for (int v : g[u]) {
    	if (deleted[v]) continue;
        if (!num[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
    if (low[u] == num[u]) {
        scc++;
        int v;
        do {
            v = st.top(); 
            st.pop();
            deleted[v] = true;
        }
        while (v != u);
    }
}
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
-> Tim thanh phan lien thong manh, sau do co lai thanh
mot dinh, tao do thi DAG (Directed Acyclic Graph), mot di khong tro lai;
u, v la cac dinh tren do thi DAG tao thanh;
C[u] la tong gia tri kinh te cua dinh u

-> QHD tren DAG: f[u] = fax(f[v] + C[u])
*/

const int maxN = 100010;
const int INF  = 1e9 + 7;
 
int dx[] = {0, -1, 0, 1, 0};
int dy[] = {0,  0, 1, 0,-1};

int m, n;
char a[maxN];
int val[maxN], totalScc[maxN];

/* Lưu đồ thị ban đầu*/
vector <int> g[maxN];

/* Lưu đồ thị mới*/
vector <int> h[maxN];

/* Kỹ thuật "Biến mảng 2 chiều thành mảng 1 chiều" */
int getId(int i, int j){
    return (i - 1) * n + j;
}

/* Kiểm tra ô (i, j) có được đi vào không? */
bool check(int i, int j) {
    if (a[getId(i, j)] == '#') return false;
    return (i >= 1 && j >= 1 && i <= m && j <= n);
}

/* Tìm thành phần liên thông mạnh*/
int root[maxN];
int low[maxN], num[maxN];
bool deleted[maxN];
int timeDfs = 0, scc = 0;
stack <int> st;
 
void dfs(int u) {
    low[u] = num[u] = ++timeDfs;
    st.push(u);
    for (int v : g[u]) {
        if (deleted[v]) continue;
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
    }
 
    if (num[u] == low[u]) {
        scc++;
        int v;
        do {
            v = st.top();
            st.pop();
            deleted[v] = true;

            /* Tính tổng giá trị kinh tế của thành phần liên thông */
            totalScc[scc] += val[v];

            /*Đỉnh scc sẽ là đỉnh ảo đại diện cho v trong đồ thị DAG*/
            root[v] = scc;
        } while (v != u);
    }
}
 

/* Quy hoạch động trên đồ thị DAG */
int f[maxN];

int solve(int u) {
    if (h[u].empty()) return totalScc[u];
    if (f[u] != -1) return f[u];
    int cur = -INF;
    for (int v : h[u]) cur = max(cur, solve(v) + totalScc[u]);
    return f[u] = cur;
}
 
int main() {
    /* Xử lý dữ liệu đầu vào */
    cin >> m >> n;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j) {
            int u = getId(i, j);
            cin >> a[u];
            val[u] = (a[u] >= '0' && a[u] <= '9') ? a[u] - '0' : 0;
        }

    /* Xây dựng đồ thị ban đầu */ 
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int u = getId(i, j);
            if (a[u] == '#') continue;
            if (check(i, j + 1)) g[u].push_back(getId(i, j + 1));
            if (check(i + 1, j)) g[u].push_back(getId(i + 1, j));

            if (a[u] == 'W' && check(i, j - 1)) 
                g[u].push_back(getId(i, j - 1));
            
            if (a[u] == 'N' && check(i - 1, j)) 
                g[u].push_back(getId(i - 1, j));
        }
    }

    /* Tìm thành phần liên thông mạnh*/ 
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j){
            int u = getId(i, j);
            if (!num[u] && check(i, j)) dfs(u);
        }

    /* Xây dựng đồ thị mới */ 
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!check(i, j)) continue;
            int u  = getId(i, j);
            int ru = root[u];
            for (int v : g[u]) {
                int rv = root[v];
                if (ru != rv) {
                /* Có cung đi từ ru đến rv trên đồ thị mới do đỉnh 
                u trong TPLTM ru đi được tới đỉnh v trong TPLTM rv*/
                    h[ru].push_back(rv);
                }
            }
        }
    }
    fill(f, f + m * n + 1, -1);
    cout << solve(root[getId(1, 1)]);
}