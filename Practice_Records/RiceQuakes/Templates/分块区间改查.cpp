#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], bel[N], sum[N], mark[N], st[N], ed[N], len[N];
void prework() {
    int sq = sqrt(n);    // number of intervals
    int dwlen = n / sq;  // standard interval lenth
    for (int i = 1; i <= sq; i++) {
        st[i] = dwlen * (i - 1) + 1;
        ed[i] = i == sq ? n : dwlen * i;  // the last interval is longer
        len[i] = ed[i] - st[i] + 1;
        for (int j = st[i]; j <= ed[i]; j++) {
            bel[j] = i;
        }
    }
}
void add(int l, int r, int k) {
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            a[i] += k;
            sum[bel[i]] += k;
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            mark[i] += k;
        }
    }
}
int query(int l, int r) {
    int ans = 0;
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            ans += a[i] + mark[bel[i]];
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            ans += a[i] + mark[bel[i]];
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            ans += a[i] + mark[bel[i]];
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            ans += len[i] * mark[i] + sum[i];
        }
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    prework();
    int sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        for (int j = st[i]; j <= ed[i]; j++) {
            sum[i] += a[j];
        }
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            add(l, r, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << '\n';
        }
    }
}