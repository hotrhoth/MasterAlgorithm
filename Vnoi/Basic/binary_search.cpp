// Tim kiem tren mang sa sap xep san

// O(log(n))
/*
Thư viện STL C++ thực hiện các tìm kiếm trong các hàm 
LOWER_BOUND tra ve iter chi vi tri phan tu < target
UPPER_BOUND tra ve iter chi vi tri phan tu > target
binary_search -> tra ve bool tim dc hay khong
equal_range -> return std::make_pair(std::lower_bound(first, last, value),
                         std::upper_bound(first, last, value));
*/
// Khong gian tim kiem la 1 -> size(A)
/*
binary_search(A, target) {
    lo = 1, hi = size(A);
    while(lo <= hi) {
        mid = lo + (hi-lo)/2;
        if(A[mid] == target) return mid;
        else if(A[mid]<target) lo = mid + 1;
        else hi = mid - 1;
    }
}
*/

int binary_search(int A[], int sizeA, int target) {
    int lo = 1, hi = sizeA;
    while (lo <= hi) {
        int mid = lo + (hi - lo)/2;
        if (A[mid] == target)
            return mid;       	
        else if (A[mid] < target)
            lo = mid+1;
        else
            hi = mid-1;
    }
    // không tìm thấy giá trị target trong mảng A
    return -1;
}    	

// Ham so don dieu
/*
    -> Day P(S) cua ban co dang false - true;
    -> Co the tim duoc phan tu false lon nhat, tim phan tu true nho nhat
    -> Hay kiem tra bai co ban co nghiem trc khong da
*/

// Tim x nho nhat ma P(x) true
bool P(int x) {
    // logic ham P o day
    // Vi du : Boolean(a[x] >= 55)
    return true;
}
// -> f f f f t t t

int binary_search_smallest(int lo, int hi) {
    while(lo < hi) {
        int mid = lo + (hi - lo) / 2; // lam tron xuong de lay smallest
        if(P(mid) == true)  hi = mid;
        else lo = mid + 1;
    }

    if(P(lo) == false) return -1; // tat ca la false ma dang can true

    return lo;
}
// -> Giai phap truyen nua khoang [lo, hi) -> hay co the truyen [0, N)
// Tim x lon nhat ma P(x) false
/*
    Với trường hợp ta muốn tìm vị trí phần tử false cuối cùng thì 
    nửa khoảng cần tìm sẽ là (lo, hi] và hàm sẽ tự động trả về lo 
    nếu mọi giá trị trong khoảng là true.
*/
int binary_search_biggest(int lo, int hi) {
    while(lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // lam tron len de lay biggest
        if(P(mid) == true)  hi = mid - 1;
        else lo = mid;
    }

    if(P(lo) == true) return -1; // tat ca deu la true

    return lo;
}


// Tim kiem nhi phan tren so thuc
// dich chuyen can khong nguyen

bool P(double x) {
    // Logic của hàm P ở đây
    return true;  // thay giá trị này bằng giá trị đúng logic.
}

bool isTerminated(double lo, double hi) {
    // trả về kết quả của việc kiểm tra
    // lo và hi có thỏa điều kiện dừng chưa 
}

double binary_search(double lo, double hi) {
    while (isTerminated(lo, hi) == false) {
        double mid = lo + (hi-lo)/2;
        if (P(mid) == true)
            hi = mid;
        else
            lo = mid;
    }
    // trung bình cộng lo và hi xấp xỉ 
    // ranh giới giữa false và true
    return lo + (hi-lo)/2; 
}
/*
1. Dừng sau một số vòng lặp cố định (fixed): 
    Thông thường khi làm bài tập trên TopCoder, 
    chỉ cần lặp khoảng 100 lần là đủ (nhiều khi là thừa) 
    để đạt được độ chính xác mong muốn cho những bài dạng thế này.

2. Sai số tuyệt đối (absolute error): dừng khi hi - lo <= epsilon
    (ep thường rất nhỏ, khoảng 1e−8). 
    Cách này được sử dụng nếu thời gian chặt và bạn phải tiết kiệm số lần lặp.
*/
