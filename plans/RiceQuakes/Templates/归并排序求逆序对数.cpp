#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int T, ans, t[N], a[N];
int rev(int l, int r) {
    if (l == r)
        return 0;
    int mid = l + r >> 1;
    int ans = rev(l, mid) + rev(mid + 1, r);
    int pl = l, pr = mid + 1, idx = l;
    while (pl <= mid and pr <= r) {
        if (a[pl] < a[pr])
            t[idx++] = a[pl++];
        else
            t[idx++] = a[pr++], ans += mid - pl + 1;
    }
    while (pl <= mid)
        t[idx++] = a[pl++];
    while (pr <= r)
        t[idx++] = a[pr++];
    for (int i = l; i <= r; i++)
        a[i] = t[i];
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        cout << rev(1, n) << '\n';
    }
}