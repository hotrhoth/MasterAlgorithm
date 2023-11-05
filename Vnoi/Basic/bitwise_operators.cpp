/*
    Info: Bitwise operators, Fenwick tree, Bitmask, Pragma
*/

/* Gioi thieu
    - Bieu dien nhi phan duoc danh so bang tien to 0b
    - Bitmask la chuoi so 0, 1 tuong ung voi tat, bat
    -> BD bitmask bang kieu so nguyen
    - Undefined behaviour (UB)
    - int (32 bit), long long (64 bit)
*/

/* Kien thuc
Tên hàm	                       Giá trị trả về	     Trường hợp UB
std::__builtin_popcountll(x)	Số Bit bật	 
std::__builtin_parityll(x)	    Số Bit bật modulo 2	 
std::__builtin_clzll(x)	        Số Bit 0 ở đầu	       x == 0
std::__lg(x)	                ⌊log2(𝑥)⌋	 
std::__builtin_ctzll(x)	        Số Bit 0 ở cuối	       x == 0
std::__builtin_ffsll(x)	        Số thứ tự của Bit 1 đầu tiên	 
*/

/*
    - Truy cap bit thu i: 
    A & (1LL<<i) hay (A >> i) % 2 hay (A >> i) & 1
    - Chinh su bit:
        + Gan mot bit bang 0: A & ~(1 << i)
        + Gan mot bit bang 1: A | (1 << i)
        + Flip bit: A ^ (1 << i)
    - Tat bit cao nhat cua bitmask:
    A & ((1<<i)-1)
    - Bieu dien tap hop:
        + Giao: A & B
        + Hop: A | B
        + Hieu: (A ^ B) & A
        + Hieu doi xung: A ^ B
        + Phan bu: ~A & (1 << n) - 1 // tat bit tai vi tri n
        + Kiem tra tap con: (A & B) == A
        + Tao hop chi co phan tu i: 1 << i

*/

#include <vector>
using std::vector;

bool get_bit(unsigned long long mask, int pos){
    return mask & (1ULL << pos);
}

// Lap qua moi tap con cua tap cho truoc

void loop_subset(const vector<int> &s) {
    for(int mask=0; mask<(1<<s.size()); mask++) {
        vector <int> a;
        for(int i=0; i<s.size(); i++) {
            // neu bit o vi tri i bat thi no thuoc tap hop
            if(mask & (1<<i)) a.push_back(s[i]);
        }

        // Thuc hien thao tac voi tap con a
    }
}

// Fenwick tree
/*
    -> Bai toan: cho mot tap hop S gom cac so nguyen to
    phan biet. Goi a la tich cac so trong ta S. 
    Trong cac so thuoc khoang [0, n], dem so so
    nguyen to cung nhau voi a.
*/

// Bai toan bao ham loai tru
/*
    Lap moi tap hop con T cua S. Goi b la tich cac 
    so trong tap T, va x la so so trong khoang [0, n] 
    chia het cho b. Chan phan tu thi cong vao dap an,
    nguoc lai tru x vao dap an.
*/

#define ull unsigned long long

ull solve(const vector<ull> &a, ull n) {
    ull res = 0;
    for(int mask=0; mask<(1<<a.size()); mask++) {
        ull b = 1;
        for(int i=0; i<a.size(); i++) {
            // neu bit o vi tri i bat thi no thuoc tap hop
            if(mask & (1<<i)) b *= a[i];
        }

        ull x = res / b + 1;

        if(__builtin_parity(mask)) res -= x;
        else res += x;

        // Thuc hien thao tac voi tap con a
    }
    return res;
}

/*
    Chu y: 
    - Operator Precendence:
        + >>, << thuc hien sau +, -
        + &, ^, | dung sau == va ca phep tinh toan
    -> Nen su dung ()
*/

// Lap qua moi tap hop con cua mot bitmask

void loop_mask_subset(int S) {
    for(int mask=S; true; mask = (mask-1)&S) {
        // Thuc hien giam dan tap hop con cua S
        if(mask==0) break;
    }
}

void loop_subset_of_all_masks(int n){
    for (int S = 0; S < 1<<n; S++){
        // Thực hiện thao tác nào đó với tập con S
        for (int T=S; true; T = (T-1) & S){
            // Thực hiện thao tác nào đó với tập con T của S
        }
    }
}

// Lap qua moi bo x tap con phan biet

/*
    -> Cho mot tap S do dai n voi mot so x. 
    Hay in ra tat ca cac cach chia cac phan tu trong
    S vao x tap hop khong giao nhau sao cho moi phan tu
    nam trong dung mot tap hop.
*/
// Can tao ra (A, B) -> (B, A\C, C)
// Hieu doi xung la hop 2 tap hop r bo di phan giao
void loop_triplets(int n) {
    int S = (1<<n) - 1;
    for(int A = S; true; A=(A-1)&S) {
        int B = S ^ A;
        for(int C=A; true; C=(C-1)&A) {
            // in ra B, A^C, C
            if(C==0) break;
        }
        if(A==0) break;
    }
}

void solve_4_sets(vector<int> &sets);

// x la so phan tu duoc lay trong sets, mask la trang thai hien gio
void generate_partitions(vector<int> &sets, int mask, int x) {
    if(x==1) {
        sets.push_back(mask);
        // thuc hien gi do voi sets
        // da tim ra sets thoa man
        solve_4_sets(sets);
        // bo phan tu do ra r de quy tiep
        sets.pop_back();
        return;
    }
    for(int s=mask; true; s=(s-1)&mask) {
        sets.push_back(mask);
        // thuc hien gi do voi sets
        generate_partitions(sets, mask^s, x-1);
        sets.pop_back();
        if(s==0) break;
    }
}

int main() {
    int n = 10, parts = 5;
    vector <int> sets;
    generate_partitions(sets, (1<<n)-1, parts);
}

/*
    -> Su dung pragma:
    #pragma GCC target("popcnt,lzcnt,bmi,bmi2,abm")

    -> Phan biet
    Trong C++, phép Logical Right Shift sẽ được sử dụng 
    nếu toán tử đầu tiên là một số thuộc loại unsigned, 
    còn nếu không thì phép Arithmetic Right Shift sẽ được sử dụng.
    
    + Logical Right Shift:
    voi so unsigned thi co y nghia la /2^x;
    + Arithmetic Right Shift:
    voi so am cung co nghia la /2^x va lam tron xuong;

*/
