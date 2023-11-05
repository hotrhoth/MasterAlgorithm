/*
    Info: CSES (MITM) su dung backtracking, tim kiem nhi phan, hai con tro
*/

// -> La thuat toan tum kiem khi dau vao nho nhung khong du nho de backtracking

/*
    - Gioi thieu: cho mang t co N phan tu.
    Hoi co bao nhieu cach chon tap hop con sao cho co tong bang x
*/

// backtracking -> Do phuc tap 2^n qua lon
#include <iostream>
#include <vector>
using namespace std;

const int N = 40 + 2;
int n, x;
int t[N];
vector<int> A, B;
long long cnt;


// dang quay lui toi phan tu i, va dang co tong sum
void TRY(int i, int sum) {
    if(sum > x) return;
    if(i > n){
        if(sum == x) cnt++;
    } 

    else {
        TRY(i+1, sum);
        TRY(i+1, sum + t[i]);
    }
}

long long solve() {
    cnt = 0;
    TRY(1, 0);
    return cnt;
}

/*
    TOI UU Ky thuat MITM
    - Dat K = N / 2
    - Duyet tap con cua A, B, tinh tong tung tap
    - Sap xep A, B

*/

void TryX(int i, int sum) {
    if(sum > x) return;
    if(i > n/2){
        A.push_back(sum);
    } 

    else {
        TRY(i+1, sum);
        TRY(i+1, sum + t[i]);
    }
}

void TryY(int i, int sum) {
    if(sum > x) return;
    if(i > n){
        B.push_back(sum);
    } 

    else {
        TRY(i+1, sum);
        TRY(i+1, sum + t[i]);
    }
}
/*
int main() {
    cin >> n >> x;
    for(int i=1; i<=n; i++) cin >> t[i];

    // Quay lui 2 tap X va Y

    TryX(1, 0);
    TryY(n/2+1, 0);

    sort(B.begin(), B.end());

    long long cnt = 0;
    for(int sum : A) { 
        // Cong cac phan tu co the trung
        cnt += upper_bound(B.begin(), B.end(), x - sum)
             - lower_bound(B.begin(), B.end(), x - sum);
    }
    cout << cnt << "\n";

}
*/

/*
    -> Dung hai con tro
     // Quay lui 2 tập X và Y
  TryX(1, 0);
  TryY(n / 2 + 1, 0);

  // Sắp xếp mảng A và B
  sort(A.begin(), A.end(), greater<int>());
  sort(B.begin(), B.end());

  // Sử dụng kỹ thuật 2 con trỏ
  long long cnt = 0;
  for (int i = 0, j1 = 0, j2 = 0; i < A.size(); ++i) {
      int s = x - A[i]; // cần đếm lượng B[j] thoả B[j] = s
      while (j1 < B.size() && B[j1] < s) ++j1;
      while (j2 < B.size() && B[j2] <= s) ++j2;
      cnt += j2 - j1;
  }
  cout << cnt << '\n';
*/

/*
    -> Bai toan 1:
    Có 𝑁 cục vàng, mỗi cục vàng có trọng lượng 𝑊𝑖 và giá trị 𝑉𝑖. 
    Bạn có một cái túi có tải trọng tối đa là 𝑀. 
    Hỏi tổng giá trị vàng lớn nhất có thể thu được mà không làm rách túi.

    -> Giai quyet bai toan con:
    Voi moi cap (sumWi, sumVi) cua tap A, can tim
    mot cap (sumWj, sumVj) trong tap B sao cho
    sumWj <= M-sumWi va sumVi la lon nhat.

    -> Sap xep lai mang B:
    maxsumVj = max(sumV1, ..., sumVj)
*/
using namespace std;

const int MaxSize = (1<<20) + 10;
int m;
int w[N], v[N];

long long sumVA[MaxSize];
long long sumWA[MaxSize];
int sizeA;

pair<int, long long> B1[MaxSize];
long long sumWB[MaxSize];
long long maxsumVB[MaxSize];
int sizeB;

void TryX(int i, long long sumW, long long sumV) {
    if (sumW > m) return;
    if (i > n / 2) {
        ++sizeA;
        sumWA[sizeA] = sumW;
        sumVA[sizeA] = sumV;
        return;
    }
    TryX(i + 1, sumW, sumV);
    TryX(i + 1, sumW + w[i], sumV + v[i]);
}

void TryY(int i, long long sumW, long long sumV) {
    if (sumW > m) return;
    if (i > n) {
        ++sizeB;
        B1[sizeB].first  = sumW;
        B1[sizeB].second = sumV;
        return;
    }
    TryY(i + 1, sumW, sumV);
    TryY(i + 1, sumW + w[i], sumV + v[i]);
}

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> w[i] >> v[i];

    TryX(1, 0, 0);
    TryY(n / 2 + 1, 0, 0);
    sort(B1+1, B1+sizeB+1); // sort sizeB phan tu va bd tu B1+1

    for(int i=1; i<=sizeB; ++i) {
        sumWB[i] = B1[i].first;
        maxsumVB[i] = max(maxsumVB[i-1], B1[i].second);
    }
    long long res;
    for(int i=1; i<=sizeA; ++i) {
        int j = upper_bound(sumWB + 1, sumWB + sizeB + 1, m - sumWA[i]) - sumWB - 1;
        res = max(res, sumVA[i] + maxsumVB[j]);
    }
}

/* 
    -> Bai toan 2:
    Cho mảng 𝑎 gồm 𝑛 số nguyên, đếm số lượng dãy con tăng có độ dài 3.

    for (int j = 0; j < n; ++j) {
    int smaller = 0, bigger = 0;
    for (int i = 0; i < j; ++i) {
        if (a[i] < a[j]) ++smaller;
    }
    for (int k = j + 1; k < n; ++k) {
        if (a[k] > a[j]) ++bigger;
    }
    answer += smaller * bigger;
}
*/

/*
    -> Bai toan 3;
    Cho mảng 𝑎 gồm 𝑛 số nguyên và số nguyên 𝑥. 
    Ta cần tìm 4 vị trí phân biệt sao cho tổng giá trị ở 4 vị trí đó bằng 𝑥.
    using namespace std;
const int N = 1000 + 3;
int n, x;
int a[N];

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // preprocess
    map<int, pair<int, int>> mp;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            mp[a[i] + a[j]] = make_pair(i, j);

    // solve
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            // thay vì 2 vòng for, bây giờ ta chỉ cần 
            // truy vấn trên std::map
            int X = x - a[i] - a[j];
            if (mp.count(X)) {
                pair<int, int> arr = mp[X];
                if (j < arr.first) {
                    cout << i << ' ' << j << ' ' << arr.first << ' ' << arr.second;
                    return 0;
                }
            }
        }

    cout << "IMPOSSIBLE";
}
*/

/*
Cho đồ thị có hướng 𝑛 đỉnh (𝑛≤100) và bậc ngoài của mỗi đỉnh không quá 40.
Tất cả đỉnh đều được tô màu. Tìm một đường đi độ dài 9 sao cho 
9 đỉnh trong đường đi có màu phân biệt. 
Nếu có nhiều cách chọn, in ra bất kỳ, ngược lại, in ra "fail".

Giới hạn thời gian là rất lớn (12 giây).
    -> Gap lai doc o day: (kho hieu hon co ay nx)
    https://vnoi.info/wiki/algo/basic/meet-in-the-middle.md
*/

