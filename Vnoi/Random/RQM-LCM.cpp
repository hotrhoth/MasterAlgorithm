/*
    Bai toan RMQ va LCA, moi quan he giua chung

    -> RMQ: mang A[0, N-1], tra loi Q truy van, moi truy van gom i, j.
    Can dua vi tri cua phan tu co gia tri nho nhat tu i den j cua mang A,
    ki hieu RMQ(i, j)

    -> LCA: cho cay goc T, tra loi Q truy van, tim to tien xa goc nhat
    la to tien cua u va v, ki hieu LCA(u, v)
*/

/*
RMQ: 
    - Giá trị RQM(i, j) trong một mảng M[0, N-1][0, N-1]
*/

// O(N^2)
#include <iostream>
#include <math.h>
using namespace std;

const int N = 100;
int m[N][N]; // luu vi tri cua phan tu nho nhat
int a[N] = {2, 4, 3, 1, 6, 7, 8, 9, 1, 7};
int n;

// O(n^2)
void rmq_n2() {
    for(int i=0; i<n; i++) m[i][i] = i;
    for(int i=0; i<n; i++) 
        for(int j=i+1; j<n; j++) 
            if(a[m[i][j-1]] < a[j])
                m[i][j] = m[i][j-1];
            else m[i][j] = j;
}

// O(√n)
/*
Chia mang thanh √n phan, dung mang M[0, √n] de luu gia tri moi phan,
tinh M trong O(n)
*/

const int N_test = 10;
int tmp = N_test / sqrt(N_test); // so phan tu 1 nhom


int m_tmp[N_test];

// 0 1 2 | 3 4 5 | 6 7 8 | 9
//   0       1       2     3

int t = N_test / tmp + 1; // so nhom
void rmq_sqrtn() {
    int cnt = 0;
    for(int i=0; i<t; i++) {
        m_tmp[i] = i*tmp;
        for(int j=0+i*tmp; j<((i+1)*tmp) && j < N_test; j++)
            if (a[j] < a[m_tmp[i]])
                m_tmp[i] = j;
    }
}
int solve(int i, int j) { // nay lay gia tri, hoac vi tri
    int t1 = i/tmp; // i o nhom 0
    int t2 = j/tmp; // j o nhom 2
    int ans = 100;
    for(int t=t1+1; t<t2; t++) ans = min(ans, a[m_tmp[t]]);
    for(int t=i; t<(t1+1)*tmp; t++) ans = min(ans, a[t]);
    for(int t=t2*tmp; t<(t2+1)*tmp; t++) ans = min(ans, a[t]);
    return ans;
    
}

/*
Sparse table: tien xu li cho doan con co do dai 2^k;
-> Su dung mang m[0, N-1][0, logN], voi m[i][j] la chi so cua phan tu
co gia tri nho nhat trong doan co do dai 2^j va bat dau o i;
-> Truy van m[i][j] = m[i][j-1] va m[i+ 2^(j-1)][j-1];
*/

void process2(int m[][N], int a[], int N) {
    int i, j;
    for(int i=0; i<N; i++) m[i][0] = i;
    // tinh m voi khoang dai 2^j
    for(j=1; i<<j <=N; i++) 
        for(int i=0; i + (1<<j) - 1 < N; i++)
            if(a[m[i][j-1]] < a[m[i + (1<<(j-1))][j-1]])
                m[i][j] = m[i][j - 1];
            else
                m[i][j] = m[i + (1 << (j - 1))][j - 1];
}
// -> Tinh RMQ(i, j) dua vao 2 doan con do dai 2^k phu het [i, j]
// voi k = lam tron xuong (log(j-i+1));
// xet m[i][j] va m[j-2^k + 1][k]
// vd [2, 7]:
/*
k = 2; -> m[2][2] 2-> 2 + 2^2 - 1 (2, 3, 4, 5);
       -> m[4][2] 4-> 4 + 4 - 1 (4, 5, 6, 7);

*/
int main() {
    rmq_sqrtn();
    for(int i=0; i<t; i++) cout << a[m_tmp[i]] << " ";
    cout << "\n";
    int ans = solve(2, 7);
    cout << ans;
}

/*
Cây phân đoạn (segment tree, interval tree, range tree);
-> Biểu diễn cây bằng một mảng m[1, 2 * 2 ^ (logN + 1)]
voi m[i] la vi tri co gia tri nho nhat trong doan ma nut i quan li
*/
int maxind = 2 * pow(2, log2(N) + 1) + 1;

// b la node bat dau, e la node ket thuc, node la node quan li
void initialize(int node, int b, int e, int M[], int A[], int N) {
    if(b==e) M[node] = b;
    else {
        initialize(2 * node, b, (b+e)/2, M, A, N);
        initialize(2 * node +  1,(b+e)/2 + 1, e, M, A, N);

        if(A[M[2*node]] <= A[M[2*node + 1]])
            M[node] = M[2*node];
        else M[node] = M[2*node + 1];
    }
}
// truy van
int query(int node, int b, int e, int M[], int A[], int i, int j) {
    // doan can tinh khong giao voi nut hien tai
    if(i>e || j<b) return -1;
    // doan can tinh nam hoan toan trong nut hien tai
    if(b>=i && e<=j) return M[node];

    // tim tren cay con trai
    int p1 = query(2 * node, b, (b+e)/2, M, A, i, j);
    // tim tren cay con phai
    int p2 = query(2 * node, (b+e)/2 + 1, e, M, A, i, j);

    if (p1 == -1)
        return M[node] = p2;
    if (p2 == -1)
        return M[node] = p1;
    if (A[p1] <= A[p2])
        return M[node] = p1;
    return M[node] = p2;
}

/*
Bai toan LCA:
    -> Thuat toan don gian nhat:
        - Đặt h(u) là độ cao của đỉnh u xet tu dinh goc
        - Truy vấn u, v; giả sử h(u) > h(v);
            + đi u -> u', u' la to tien cua u cho toi khi h(u') = h(v)
            + khi da chung do cao, di dong thoi u va v
*/

/*
int h[N];
int parent[N];

int LCA(int u, int v) {
    if(h[u] < h[v]) swap(u, v);

    while(h[u] > h[v]) u = parent[u];

    while(u!=v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}
*/

/*
Ý tưởng chia input chia cay thanh √H phần, H là chiều cao của cây
Các phần bao gồm tầng i -> (i+1)*√N - 1, ...
-> Sử dụng mảng P[1, maxN]:
với mỗi nút, ta biết được tổ tiên ở phần ngay trên nó;
-> Tính P bằng dfs (T[i] là cha của i, nr = √H, L[i] là tầng của nút i);
*/

const int maxN = 100;
vector<int> g[maxN];

void dfs(int node, int T[maxN], int N, int P[maxN], int L[maxN], int nr) {

    // Nếu nút ở phần đầu tiên, thì P[node] = 1
    // Nếu nút ở đầu của 1 phần, thì P[node] = T[node]
    // Trường hợp còn lại, P[node] = P[T[node]]

    if(L[node] < nr) P[node] = 1;
    else if (!(L[node] % nr)) P[node] = T[node];
    else P[node] = P[T[node]];

    for(int k: g[node]) 
        dfs(k, T, N, P, L, nr);    
}

int LCA(int T[], int P[], int L[], int x, int y)
{
    // Nếu còn nút ở phần tiếp theo không phải là tổ tiên của cả x và y,
    // ta nhảy lên phần tiếp theo. Đoạn này cũng tương tự như thuật toán
    // <O(1), O(N)> nhưng thay vì nhảy từng nút, ta nhảy từng đoạn.

    while (P[x] != P[y])
        if (L[x] > L[y])
            x = P[x];
        else
            y = P[y];

    // Giờ x và y ở cùng phần. Ta tìm LCA giống như thuật <O(1), O(N)>
    while (x != y)
        if (L[x] > L[y])
            x = T[x];
        else
            y = T[y];

    return x;
}

/*
Sử dụng Sparse Table: -> Tính một mảng P[1, N][1, logN],
                        với P[i][j] là tổ tiên thứ 2^j của i
    P[i][j] = T[i], với j=0
            = P[P[i][j-1]][j-1] với j>0
*/

void process3(int N, int T[maxN], int P[maxN][maxN])
{
    int i, j;

    // Khởi tạo
    for (i = 0; i < N; i++)
        for (j = 0; 1 << j < N; j++)
            P[i][j] = -1;

    // Khởi tạo cha thứ 2^0 = 1 của mỗi nút
    for (i = 0; i < N; i++)
        P[i][0] = T[i];

    // Quy hoạch động
    for (j = 1; 1 << j < N; j++)
        for (i = 0; i < N; i++)
            if (P[i][j - 1] != -1)
                P[i][j] = P[P[i][j - 1]][j - 1];
}

/*
function LCA(N, P[MAXN][MAXLOGN], T[MAXN], h[MAXN], u, v):
  if h(u) < h(v):
    // Đổi u và v
    swap(u, v)

  log = log2( h(u) )

  // Tìm tổ tiên u' của u sao cho h(u') = h(v)

  for i = log .. 0:
    if h(u) - 2^i >= h(v):
      u = P[u][i]

  if u == v:
    return u

  // Tính LCA(u, v):
  for i = log .. 0:
    if P[u][i] != -1 and P[u][i] != P[v][i]:
      u = P[u][i]
      v = P[v][i]

  return T[u];
*/

/*
Còn phần cuối, sẽ quay lại để đọc về liên hệ giữa 2 bài toán:
https://vnoi.info/wiki/translate/topcoder/Range-Minimum-Query-and-Lowest-Common-Ancestor
*/
