#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], lg[N], f[N][32];
void prework() {
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    for (int i = 1; i <= n; i++) {
        f[i][0] = a[i];
    }
    for (int i = 1; i < 31; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            f[j][i] = max(f[j][i - 1], f[j + (1 << i - 1)][i - 1]);
        }
    }
}
int query(int l, int r) {
    int len = lg[r - l + 1];
    return max(f[l][len], f[r - (1 << len) + 1][len]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    prework();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}