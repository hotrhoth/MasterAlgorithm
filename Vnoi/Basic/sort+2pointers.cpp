//https://visualgo.net/en/sorting

#include <iostream>
#include <vector>
using namespace std;

/*
int i = 1, j = 1;
vector<int> c;
while (i <= n || j <= m){
    if (j == m + 1 || (i <= n && a[i] <= b[j]))
        c.push_back(a[i++]);
    else 
        c.push_back(b[j++]);
}
for (auto it: c)
    cout << it << " ";
*/
/*
int i = 1, j = N;
while (i < j) {
    if (a[i] + a[j] == x) {
        cout << i << " " << j;
        return 0;
    }
    if (a[i] + a[j] < x)
        i += 1;
    else
        j -= 1;
}
cout << "No solution";
*/

/*
int ans = 0, sum = 0;
for (int l = 1, r = 1; r <= n; r++) {
    sum += a[r];
    while (sum > s) {
      sum -= a[l];
      l++;
    }
    ans = max(ans, r - l + 1);
}
cout << ans;
*/

// https://www.youtube.com/watch?v=PvrxZaH_eZ4
