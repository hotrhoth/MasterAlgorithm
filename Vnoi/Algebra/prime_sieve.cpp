// Sieve of Eratosthenes, Bitset, Linear Sieve, Segmented Sieve, Wheel Factorization, Algo Meissel - Lehmer

/*

*/

// O(n * log(log(n)))
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

const int MAXN = 1000005;
bool isPrime[MAXN];
int min_prime[MAXN];

// Phan tich so nguyen thanh cac so nguyen to

/*
    min_prime[i] luu uoc nguyen to nho nhat cua so i
*/

void sieve(int n){
    for(int i=2; i<=n; i++) isPrime[i] = true;
    for(int i=2; i<=n; i++){
        if(isPrime[i]) { // min_prime[i] == 0, i la so nguyen to
            for(int j=i*2; j<=n; j+=i) isPrime[j] = false;
            /*
                if(min_prime[j] == 0) min_prime[j] = i;
            */
        }
    }
    /* uoc nguyen to i cung la uoc min nguyen to cua chinh no
    for(int i=2; i<=n; i++) if(min_prime[j] == 0) min_prime[j] = i;
    */
}

// -> Cai tien phep tinh
/*
    Neu p < X < p^2 : 1 < k < p, k da dc xet r:
    -> chi xet X >= p^2;
*/

void Erarosthenes(int n){
    for(int i=2; i<=n; i++) isPrime[i] = true;
    int ntmp = sqrt(n);
    for(int i=2; i<=ntmp; i++){
        if(isPrime[i]) {
            for(int j=i*i; j<=n; j+=i) isPrime[j] = false;
        }
    }
}

// O(log(n))
vector<int> factorize(int n){
    vector<int> res;

    while(n!=1) {
        res.push_back(min_prime[n]);
        n /= min_prime[n];
    }

    if(n > 1) res.push_back(n);
    return res;
}

// O(sqrt(n))

// da sang so nguyen to ra mang primes
// lu so nguyen to tu 2 den sqrt(n)

vector<long long> Factorize(long long n) {
    vector<int> primes;
    vector<long long> res;
    for(int p: primes) {
        if(1LL * p * p > n) break;
        while(n%p==0) {
            res.push_back(p);
            n /= p; // dem so lan xuat hien cung dc
        }
    }

    if(n > 1) res.push_back(n);
    return res;
}

// Tim so nguyen to trong doan [L; R]
// Danh dau so nguyen to trong doan 1, sqrt(R)

// Time: O(N * log(log(R)) + sqrt(R) * log(log(sqrt(R)))
// Space:   O(N + sqrt(R))
vector<bool> sieve (long long L, long long R){
    long long sqrtR = sqrt(R);
    vector<long long> primes;
    vector<bool> mark(sqrtR + 1, false);

    // sinh ra cac so nguyen to <= sqrt(R)
    for(int i=2; i<=sqrtR; i++){
        if(!mark[i]){ 
            primes.push_back(i);
            for(int j=i*i; j<=sqrt(R); j+=i) mark[j] = true;
        } 
    }

    vector<bool> isPrime(R+L-1, true);
    // [L, R] = [2, 10];
    // primes = {2, 3, 5, 7}
    // Danh dau mang lui lai j -  L;
    for(long long i: primes) {
        // (L + i -1) / i * i  la boi nho nhat cua i ma >= i
        for(long long j = max(i * i, (L + i -1) / i * i) ; j<=R; j+=i) 
            isPrime[j - L] = false;
    }
    if(L==0) isPrime[0] = false;
    return isPrime;
}

// Phi ham Euler - Bai toan giai o ham main
/* 
    Tóm tắt đề: Cho số nguyên dương T và T số nguyên dương ni. 
    phi(n) được định nghĩa là số lượng các số nguyên dương nhỏ hơn hoặc bằng n và nguyên tố cùng nhau với n.
    Hãy tính phi hàm phi(n) của T số nguyên dương đã cho.
    phi(n) = n * (p1 - 1) / p1 * .. * (pk -  1) / pk  
    // p1,.. pk la cca uoc nguyen to cua n
*/

int ntest, f[MAXN + 5];

/* 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int nTest; cin >>  nTest;

    for(int i=1; i<=MAXN; i++) f[i] = i;

    for(int i=2; i<=MAXN; i++) // i la so nguyen to
        if(f[i] == i) {
            for(int j = i; j<=MAXN; j+=i)
                f[j] = f[j] * i / (i-1); // bang n * lan luot cong thuc so nguyen to 
        }

    while(nTest--){
        int n; cin >> n;
        cout << f[n] << endl;
    }
}
*/




/*
    bool a[n] dung space, voi n <= 10^6 on hon
    vector<bool> toi uu hon voi n lon
*/

// Sang sieve le
// Time O(n / 2 * log(log(n)))
// Space O(n/2)
vector<bool> is_Prime_odd;

void sieve_odd(int n) {
    // is_Prime_odd[t] = true <=> 2 * t + 1 la so nguyen to
    is_Prime_odd.assign(n / 2 + 1, true);
    is_Prime_odd[0] = false;
    // duyen tu 3 -> sqrt(n)
    // <=> t = 1 -> sqrt(n)/2 <=> t * t <= n / 4;
    int ntmp = sqrt(n) / 2;
    for(int t = 1; t <= ntmp; t++) {
        int i = 2 * t + 1;
        if(is_Prime_odd[t]) { 
            // Cong 2i de ra so le tiep theo
            for(int j = i * i; j<=n; j += 2*i)
                is_Prime_odd[j/2] = false;
        }
    }
}

// Su dung bitset
/*
    Time O(n * log(log(n)))
    Space O(n / 32)
    -> Dung 1 int luu 8 bool
    // kh hieu - chac chi shift de doc lan luot tung bit tron 8 bit
    [n >> 3] 
    1 << (n & 7)      
*/
#define doc(n) (prime_bits[n >> 3] & (1 << (n & 7)))
#define set(n) {prime_bits[n >> 3] |= (1 << (n & 7));}
vector<int> prime_bits;
void sieve_bits(int n){
    prime_bits.assign((n >> 3) + 5, 0);
    set(0); set(1);
    for(int i = 2; i * i <= n; i++){  
        int w1 = doc(i);
        if (!doc(i)){
            for(int j = i * i; j <= n; j += i){
                set(j);
                int w2 = prime_bits[j >> 3] |= (1 << (j & 7));
            }
        }
    }
}

// Linear sieve la dung mang min_prime da de cap o tren

// Segmented sieve 
// Toi uu Space O(sqrt(n) + S)
// Time O(n * log(log(n)) + n * pi(sqrt(n)) / S)
/*
    Goi S la kich thuoc moi doan, co [N / S] doan
    -> Doan thu k (k = 0 .. [N / S] - 1) la (kS; min(kS + S - 1, n))
    -> Tai sao S = 10000, qua lon hay minh kh hieu
*/

vector<int> primes;
void segmented_sieve(int n) {
    const int S = 10000;

    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            // start_idx * p là bội nhỏ nhất của p mà start_idx * p >= start
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                result++;
        }
    }
    cout << result << '\n'; // In ra số số nguyên tố tìm được
}

int main() {
    segmented_sieve(53);
}
// Wheel Factorization (Doc them)
/*
    Xet tap hop boi, tap hop so du
    - VD chi xet 6k+1, 6k+5;
    - VD xet voi 30
*/

// Các thông số của bánh xe
// Bội của các số nguyên tố bé
const int wheel_size = 2 * 3 * 5;
const int num_offsets = 8;
// Tập các số dư
const int wheel_offsets[] = {1, 7, 11, 13, 17, 19, 23, 29};
// Thứ tự của 1 số trong offsets
int num_in_offsets[wheel_size];

vector<bool> is_prime;

// vị trí trong mảng is_prime
int pos(const int &v){
    return v / wheel_size * num_offsets + num_in_offsets[v % wheel_size] - 1;
}
