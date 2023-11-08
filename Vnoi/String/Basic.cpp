/* 
    Basic about string:
    - Xau con (substring)
    - Prefix, Proper Prefix
    - Suffix, Proper Suffix

    Cac dang bai:
    - So khop chuoi (string matching):
        + Tim kiem needle trong haystack (dong rom)
        + Thuat toan KMP
        + Hash
        + Z algo
    - Xau doi xung (Palindrome)
        + QHD
        + Hash
        + Palindrome Tree (trong ./overview/translate/)
    - Cau truc du lieu: Trie
    - Cac bai Ad-hoc (ngau nhien)
*/

// Thuat toan Manacher
/*
    Cho xau S.
    - Voi moi vi tri i cua xau A, tim xau doi xung dai nhat nhan i la tam.
    - Voi moi cap i, i+1 cua xau S, tim xau doi xung dai nhat nhan i va i+1 la tam.
*/
// a.b  a.b.c -> luon le
#include <iostream>
// Bai toan nay chi tim vi tri tam nen khong tinh 1 ki tu la palindrome
#include <string>
using namespace std;
const char DUMMY = '.'; // dam bao dummy khong co trong string

// Tim xau con doi xung dai nhat O(n)
int manacher(string s) {
    int n  = s.size() * 2 - 1;
    vector <int> f = vector <int>(n, 0);

    string a = string(n, DUMMY);
    for(int i=0; i<n; i+=2) a[i] = s[i/2];
    // ki tu o vi tri chan
    int l = 0, r = -1, center, res = 0;
    // l, r là biên của bounding box
    // i la tam cua palindrome
    // j la vi tri bat dau bien chay doi xung
    for(int i=0, j=0; i<n; i++) {
        j = (i>r ? 0 : min(f[l+r-i], r-i)) + 1;

        while(i-j>=0 && i+j <n && a[i-j]==a[i+j]) j++;
        f[i] = --j; // lui lai cai bien vua thoat

        if(i+j>r) {
            r = i+j;
            l = i-j;
        }

        // Ví dụ:
        // s = aabcb
        // a = a.a.b.c.b
        // f = 011010200
        // neu vi tri le, co 2 ki tu chan o ben
        // dau tien tinh luon gia tri co the dummy, lam tron xuong da 
        // bo ki tu dummy * 2 ra do dai + 1 co the la ki tu roi - dummy
        int len = (f[i] + i%2) /2 * 2 + 1 - i%2;
        if(len>res){
            res=len;
            center=i;
        }
    }
    return res;
}

// Minimal string rotation

/*
    Cho mot xau S, xet cac xau thu duoc tu xau S bang phep xoay.
    -> Giong xep hinh tron: abcd
        => abcd, dabc, cdab, bcda
    -> Tim xau co thu tu tu dien nho nhat
*/


int minmove(string s) {
    int n = s.length();
    // x is the smallest string before string y
    int x, y, i, j, u, v; // i, j la bien chay trong chuoi x, y
    for(x=0, y=1; y<n; ++y) {
        // i, u la vi tri bat dau cua string x
        // j, v la vi tri bat dau cua string y
        i = u = x;
        j = v = y;

        // i, j lam nhiem vu so sanh ki tu
        // u, v lam nhiem vu luon tang de gan lai luc 
        // trong khi cac ki tu dau tien cua hai chuoi bang nhau
        while(s[i]==s[j]) {
            ++u; ++v; // so ki tu da bang nhau bd tu x, y
            // neu i, j == n thi dem lai tu 0
            if(++i == n) i = 0; 
            if(++j == n) j = 0;
            if(i==x) break; // tat ca strings equal
        }
        
        if(s[i] <= s[j]) y = v;
        else {
            // tim ra ki tu o i > o j
            x = y;
            if(u>y) y = u;
        }
    }
    return x;
}
void lyndon(string);

int main() {
    cout << minmove("dabbabbdhkls") << "\n";
    lyndon("dabcababcdacd");
}
// Lyndon Decomposition

/*
    s = w1w2...wn trong do w1>=w2>=...>=wn
    -> Tach xau s thanh it xau nhat, sao cho moi xau deu la Lyndon word
    -> Lyndon word la cac xau khac rong,
    ma co thu tu tu dien nho hon tat ca thu duoc bang pheo xau cua no.

    A string is called simple (or a Lyndon word), if it is 
    strictly smaller than any of its own nontrivial suffixes. 
    Examples of simple strings are:
    a, b, ab, aab, abb, ababb, abcd
*/

// in ra nha
// s = s1s2s3, s1 la simple, s2 la pre-simple, s3 untouched
void lyndon(string s) {
    int n = int(s.length());
    int i = 0; 
    // pointer i always point to the beginning of string s2
    while(i<n) {
        // pointer j points to the beginning of s3
        // k points to the current char compared to
        int j = i + 1, k = i;

        // want to add s[j] to s2,
        // which requires comparison with s[k]
        while(j<n && s[k]<=s[j]) {
            // s2 + s[j] becomes simple
            // set k back to beginning of s2 to compare next char
            if(s[k]<s[j]) k = i;
            else k++;
            ++j;
        }

        while(i<=k) {
            // luc nay i = k (da test)
            cout << s.substr(i, j-k) << " ";
            i += j-k;
        }
    }
    cout << endl;
}
