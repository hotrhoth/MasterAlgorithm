/*
    Info : Primes, small Fermat, Ranbin - Miler
*/

// Primes (trong ham co nhieu doan ghi BigO co the thay the boi nhau)
#include <iostream>
#include <math.h>
using std::cin;
using std::cout;
#include <vector>

bool primeCheck(int n) {
    
    int tmp = sqrt(n);

    // O(sqrt(n)/30)
    if(n==2 || n==3) return true;
    if(n<3 || n % 2 == 0 || n %3 == 0) return false;
    for(int i=5; i<=tmp; i++)           // i la uoc chay hmm
    if(n % i == 0 || n % (i+2) == 0) return false;

    return true;

    // O(n) 
    if(n < 2) return false;
    for(int i=2; i<n; i++) {
        if(n % i == 0) return false; 
    }
    return true;

    // O(sqrt(n))
    if(n < 2) return false;
    
    for(int i=2; i<=tmp; i++) {
        if(n % i == 0) return false; 
    }
    return true;
}

void primeFactorization(int n) {

    int tmp = sqrt(n);
    for(int i=2; i<=tmp; i++) {
        while(n % i == 0) {
            n /= i;
            cout << i << " ";
        }
    }

    // n bay gio la so nguyen to
    if(n > 1) cout << n << "\n";
}

// Small Fermat 
/*
    Theorem: Neu p la prime, every a: gcd(a, p) = 1, a^(p-1) = 1 (mod p)
    -> To check prime, for a in [2, n-1] complex
    -> Increase chances, with many random as
    -> Khong chinh xac tuyet doi nen khong la thuat toan, chi du tot
    -> Khong thoa man thi la hop so, ngc lai thi khong chac
*/

// O(c*log(n)) || O(c*log^2(n)), c la so lan thu cua co so a

// Calculate a^k (mod n)
int binaryPower(long long a, long long k, int n) {
    a = a % n;
    long long res = 1;

    while(k) {
        if(k&1) res = (res * a) % n;
        a = (a * a) % n;
        k /= 2;
    }
    return res;
}

//Fermat, chi dung voi sinh test ngau nhien voi muc do tin cay du tot

bool isProbabyPrime(int n) {
    if(n < 7) return n==2 || n==3 || n==5;

    static const int repeatedNum = 5;
    for(int i=0; i<repeatedNum; ++i) {
        int a = rand() % (n-3) + 2;
        if(binaryPower(a, n-1, n) != 1) return false;
    }
    return true;
}

// Error Fermat in Carmichael nums (phai cho dung uoc cua so khong phai nguyen to)
/*
    Số các số Carmichael nhỏ hơn 1e6 là 43
    Số các số Carmichael nhỏ hơn 1e9 là 646
    Số các số Carmichael nhỏ hơn 1e18 là 1401644
*/

// Algo Ranbin-Miler
/*
    Với mọi số nguyên dương x, a^(n-1) = 1 (mod n) -> n-1 = 2^k * m (m le)
    ta tìm được duy nhất hai số tự nhiên k, m sao cho x = 2^k * m (m le)
    -> To check Prime: ton tai
       + a^m = 1 (mod n) 
    || + exist: 0 <= l <= k-1: a^(2^l * m) = -1 (modn)
    -> Khong thoa man thi la hop so, nguoc lai thi khong chac
    -> Do chinh xac cao hon Small Fermat
*/
//  -> Probabilistic (Phep thu xac suat)
//  Do chinh xac sau x lan thu (1 - 1/4^x) * 100%

//
bool test(long long a, long long n, long long k, long long m) {
    long long mod = binaryPower(a, m, n);
    if(mod == 1 || mod == n - 1) return true;
    for(int l=1; l <= k-1; ++l) {
        mod = (mod * mod) % n;
        if(mod == n - 1) return true;
    }
    return false;
}

// O(c * log n)
bool RabinMiller(long long n) {
    if(n==2 || n==3 || n==5 || n==7) return true;
    if(n < 11) return false;

    long long m = n-1, k = 0;
    while(m % 2 == 0){
        m/=2; k++;
    }
    const int repeatedNum = 4;
    for(int i = 0; i< repeatedNum; i++) {
        int a = rand() % (n-3) + 2;
        if(!test(a, n, k, m)) return  false;
    }
    return true;
}

// Deterministic Algo - Thuat toan don dinh
/*
    Dinh de Riemann tong quat (GRH)
    Do chinh xac 100%
    Nếu 𝑛 <= 3 * 1e9, chỉ cần xét a thuộc {2, 3, 5, 7}
    Nếu 𝑛 <= 2e64, chỉ cần xét a thuộc {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
*/

bool MillerRanbin(long long n) {
    if(n==2 || n==3 || n==5 || n==7) return true;
    if(n < 11) return false;

    long long m = n-1, k = 0;
    while(m % 2 == 0){
        m/=2; k++;
    }

    int checkSet[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // len = 12
    for(int i=0; i < 12; i++) {
        if(!test(checkSet[i], n, k, m)) return  false;
    }
    return true;

}
int main() {
    cout << isProbabyPrime(53) << "\n";
    cout << primeCheck(53) << "\n";
    cout << RabinMiller(53) << "\n";
    cout << MillerRanbin(53) << "\n";
}
