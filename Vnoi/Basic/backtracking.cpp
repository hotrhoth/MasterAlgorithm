/*
    Info: De quy, Thuat toan quay lui, Ky thuat nhanh can
*/

// De quy - Recursion
/*
    gcd(a, b) = gcd(b, a mod b) (b < a)
    - Phan neo (TH co so)
    - Phan de quy
*/

// Thuat toan quay lui - bai toan liet ke cac cau hinh
// -> Duyet vet can

/*
void backtrack(int pos) {
    // Truong hop co so
    if(<pos la vi tri cuoi>) {
        <output/ luu lai tap hop da dung neu thoa man>
        return;
    }

    // Phan de quy
    for(<tat ca gia tri i co the o vi tri pos>) {
        <them gia tri i vao tap dang xet>
        backtrack(pos+1);
        <xoa bo gia tri i khoi tap dang xet>
    }
}
*/

// -> Bai toan sinh cac day nhi phan

#include <iostream>
#include <string.h>
using namespace std;

int n;
string curString;

// sinh cac day nhi phan co n do dai

void genString(int pos) {
    // TH co so
    if(pos > n) {
        cout << curString << endl;
        return;
    }

    // De quy
    for(char i = '0'; i<='1'; i++) {
        curString.push_back(i); // them ki tu moi vao day
        genString(pos+1);
        curString.pop_back(); // bo ki tu nay
    }

}

/*
int main() {
    cin >> n;
    curString = "";
    genString(1); // luc nay la rong
}
*/

// -> Sinh to hop (tap hop con)
/*
    S = 1, .. n
    In ra tat ca tap hop con co chinh xac k phan tu cua S
    - Xay dung cac tap con P la cac day thoa man P(i) > P(i-1)
    -> Gia su, da xay dung duoc day den vi tri thu i, 
        va Pi la gia tri cuoi cung duoc them vao.
        Tai vi tri thu i+1, do co P(i+1) > P(i) nen ta chi thu
            tu cac so tu P(i) + 1 -> n
    -> De quy ket thuc khi tap con da du k phan tu
*/

int k;
vector <int> curSubset;

void printSubset() {
    for(int i: curSubset) cout << i << " ";
    cout << endl;
}

void genSubset(int pos) {
    int lastNum = (curSubset.empty() ? 0: curSubset.back());
    for(int i = lastNum+1; i<=n; i++){
        curSubset.push_back(i);
        if(curSubset.size() == k) printSubset();
        else genSubset(pos+1);
        curSubset.pop_back();
    }
}

/*
int main() {
    cin >> n >> k;
    curSubset.clear();
    genSubset(1);
}
*/

// Bai toan phan tich so
/*
    Co nhung cach nao de lay cac to tien cho menh gia cua chung la S
    -> Luu cac to tien da co vao mot tap hop, sau do lay cac to tien 
        sao cho to sau co menh gia khong nho hon to truoc
    // Luu mang curMoneySet, curMoneySum
*/

int a[15];
long long S, curMoneySum;
vector <int> curMoneySet;

void printMoneySet()
{
    for (auto i : curMoneySet) cout << a[i] << " ";
    cout << "\n";
}

//Hàm đệ quy
void genMoneySet(int pos)
{
    int lastIndex = (curMoneySet.empty() ? 1 : curMoneySet.back());
    for (int i = lastIndex; i <= n; i ++)
    {
        //Lấy thêm 1 tờ tiền mới vào tập hợp
        curMoneySet.push_back(i);
        curMoneySum += a[i];
        
        //Gọi đệ quy
        if (curMoneySum >= S)
        {
            if (curMoneySum == S) printMoneySet();
            /*
            bestSet.clear();
                for (int i : curMoneySet) bestSet.push_back(i);
            */
        }
        else // if (bestSet.empty() || curMoneySet.size() < bestSet.size()) 
            genMoneySet(pos + 1);
        
        //Bỏ tờ tiền này ra khỏi tập hợp
        curMoneySet.pop_back();
        curMoneySum -= a[i];
    }
}

/*
int main()
{
    cin >> n >> S;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    curMoneySet.clear();
    curMoneySum = 0;
    genMoneySet(1);

    return 0;
}
*/

// -> Bai toan xep hau
/*
    Xep n quan hau (n<=12) len ban co n*n 
        sao cho khong co quan hau an nhau
    -> Hai quan hau an nhau khi
        - Cung hang : xA = xB
        - Cung cot : yA = yB
        - Cung duong cheo :
            -> xA + yA = xB + yB (duong cheo phu)
            -> xA - yA = xB - yB (duong cheo chinh)
    -> Muc tieu: sinh ra nhung bo toa do thoa man cac dieu kien tren
    -> Tim tat ca cach xep thoa man
    -> Sinh lan luot theo tung hang, va dam bao quan Hau sau se 
        khong cung cot va khong cung duong cheo voi quan Hau truoc.
        -> Mang danh dau cot, duong cheo phu, duong cheo chinh:
            isInCol[], isInDiag1[], isInDiag2[]
            -> isInCol[k] nhan true neu da co mot quan Hau da o cot k
            -> isInDiag1[] nhan true neu da co Hau o duong cheo phu tong k
            -> isInDiag2[] nhan true neu da co Hau o duong cheo phu hieu k
*/

bool isInCol[13], isInDiag1[26], isInDiag2[26];
vector <int> curQueenSetX, curQueenSetY;

void printQueenSet() {
    for(int i=0; i<n; i++) {
        printf("(%u, %u)", curQueenSetX[i], curQueenSetY[i]);
        if(i < n-1) cout << ", ";
    }
    cout << "\n";
}

int res = 0;
void genQueenSet(int curRow) {
    for(int curCol=1; curCol<=n; curCol++) {
        int curDiag1 = curCol+curRow;
        int curDiag2 = curRow-curCol+13; // de tranh chi so am
        if(isInCol[curCol] == true) continue;
        if(isInDiag1[curDiag1] == true) continue;
        if(isInDiag2[curDiag2] == true) continue;

        curQueenSetX.push_back(curRow);
        curQueenSetY.push_back(curCol);
        isInCol[curCol] = true;
        isInDiag1[curDiag1] = true;
        isInDiag2[curDiag2] = true;
        if(curQueenSetX.size() == n){
            printQueenSet(); res++;
            }
        else(genQueenSet(curRow + 1));

        curQueenSetX.pop_back();
        curQueenSetY.pop_back();
        isInCol[curCol] = false;
        isInDiag1[curDiag1] = false;
        isInDiag2[curDiag2] = false;

    }
}

/*
int main() {
    cin >> n;

    memset(isInCol, 0, sizeof(isInCol));
    memset(isInDiag1, 0, sizeof(isInDiag1));
    memset(isInDiag2, 0, sizeof(isInDiag2));

    genQueenSet(1);
    cout << res << endl;
}
*/

// Ky thuat nhanh can
/*
    -> Co nhung luc khong can liet ke, chi can tim truong hop tot nhat
    -> Ta cap nhat trang thai tot nhat hoac khong cap nhat
    Bai toan doi tien sao cho so nto tien la nho nhat
    -> Dung mot mang bestSet;
    van luu o mang curMoneySet;
    -> Cap nhat bestSet khi curMoneySum == S; push_back tung phan tu o curMoneySet vao
    -> Neu(bestSet.empty() || curMoneySet.size() < bestSet.size())
            goi ham o vi tri pos + 1; // de co co hoi cap nhat tiep theo
*/
