/*
DFS duyet do thi theo chieu sau, 
giai bai toan tim khop cau va thanh phan lien thong manh

- Trong đồ thị có hướng, có 4 loại cung:
    + Tree edge (cung cây): dfs cây đc cạnh u -> v;
    + Forward edge (cung xuôi): cạnh không thuộc dfs nhưng có dạng u -> v;
    + Back edge (cung ngược): cung không thuộc dfs có dạng v -> u;
    + Cross edge (cung chéo): cung không thuộc dfs có dạng u -> v nhưng thuộc 2 nhánh khác nhau

- Trong đồ thị vô hướng:
    + Không tồn tại cung chéo.
    + Chỉ định nghĩa lại:
        -> Cung xuôi: là cung thuộc dfs, nét liền;
        -> Cung ngược: là cung không thuộc dfs, nét đứt;

- Một số mảng quan trọng trong dfs:
    + num[]: thứ tự mà mỗi đỉnh bắt đầu duyệt dfs;
    + low[]: cho biết thứ tự (giá trị num) nhỏ nhất có thể đi sâu đến được từ u
        đi xuôi xuống theo các cung trên cây, đỉnh có thứ tự thăm sớm nhất
        từ cây con gốc u hoặc kề cạnh với 1 đỉnh bất kì nằm trong cây con của u.
    + tail[]: cho biết thời điểm kế thúc duyệt dfs cũng là tđ duyệt xong điểm đó.

    -> Các đỉnh có thứ tự thăm nằm trong khoảng num[u] đến tail[u] 
    là các đỉnh nằm trong cây con gốc u.

- Cách thực hiện:
    + Duyệt dfs từ đỉnh gốc: low[u] = num[u] = timedfs;
    + Nếu v chưa đc thăm low[u] = min(low[u], low[v]);
    ngc lại low[u] = min(low[u], num[v]);
    (v khác cha trực tiếp của u)
    + Duyệt xong u, cập nhật tail[u] = timedfs;
*/

#include <iostream>
#include <vector>
using namespace std;

const int maxN = 10010;
int low[maxN], num[maxN], tail[maxN];
vector <int> g[maxN];

int timedfs = 0;

void dfs(int u, int pre) {
    num[u] = low[u] = ++ timedfs;
    for(int v: g[u]) {
        if(v==pre) continue;
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], num[v]);
        tail[u] = timedfs;
    }
}

/*
-> Thành phần liên thông là đồ thị con trong đó 2 đỉnh bất kì đều có đường đi 
đến với nhau, và không thể nhân thêm đỉnh nào mà vẫn duy trì tính chât trên.

Dfs tìm khớp, cầu trong đồ thị vô hướng:
    - Đỉnh khớp là đỉnh nếu loại bỏ đỉnh này và các cạnh liên thuộc với nó ra
    thì số tp liên thông của đồ thị tăng lên.
    - Cạnh cầu là cạnh nếu bỏ cạnh này thì thành phần liên thông của đồ thị tăng lên.

Nhận xét:
-> Cạnh cầu (u, v) nếu low[v] = num[v];
-> Đỉnh khớp u khi:
    + Đỉnh u là gốc dfs và có ít nhất 2 con trực tiếp trong dfs
    + Đỉnh u không là gốc dfs và low[v] >= num[u] (vói v là một con trực tiếp của u)
*/
int n, m;
int u, v;

bool joint[maxN];
int bridge = 0;

void dfs_joint_bridge(int u, int pre) {
    int child = 0;
    num[u] = low[u] = ++ timedfs;
    for(int v: g[u]) {
        if(v==pre) continue;
        if(!num[v]) {
            dfs_joint_bridge(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v]==num[v]) bridge++;
            child++;
            if(u==pre){
                if(child>1) joint[u] = true;
            }
            else if(low[v] >= num[u]) joint[u] = true;
        }
        else low[u] = min(low[u], num[v]);
    }

}

int main() {
    cin >> n >> m;
    for(int i=1; i<=m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1; i<=n; i++) 
        if(!num[i]) dfs_joint_bridge(i, i);

    int cntJoint = 0;
    for (int i = 1; i <= n; i++) cntJoint += joint[i];

    cout << cntJoint << ' ' << bridge;

}

