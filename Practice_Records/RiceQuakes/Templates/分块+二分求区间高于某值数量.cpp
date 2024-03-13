#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, a[N], len[N], st[N], ed[N], bel[N], mark[N], d[N];
void prework() {
    int sq = sqrt(n);
    int dwlen = n / sq;
    for (int i = 1; i <= sq; i++) {
        st[i] = dwlen * (i - 1) + 1;
        ed[i] = i == sq ? n : dwlen * i;
        len[i] = ed[i] - st[i] + 1;
        for (int j = st[i]; j <= ed[i]; j++) {
            a[j] = d[j];
            bel[j] = i;
        }
    }
    for (int i = 1; i <= sq; i++) {
        sort(a + st[i], a + ed[i] + 1);
    }
}
void add(int l, int r, int x) {
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            d[i] += x;
        }
        for (int i = st[bel[l]]; i <= ed[bel[l]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[l]], a + ed[bel[l]] + 1);
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            d[i] += x;
        }
        for (int i = st[bel[l]]; i <= ed[bel[l]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[l]], a + ed[bel[l]] + 1);
        for (int i = st[bel[r]]; i <= r; i++) {
            d[i] += x;
        }
        for (int i = st[bel[r]]; i <= ed[bel[r]]; i++) {
            a[i] = d[i];
        }
        sort(a + st[bel[r]], a + ed[bel[r]] + 1);
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            mark[i] += x;
        }
    }
}
int bs(int l, int r, int x) {  // num of >=x
    while (l <= r) {
        int mid = l + r + 1 >> 1;
        if (a[mid] >= x)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return ed[bel[l]] - r;
}
int query(int l, int r, int x) {
    int ans = 0;
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
    } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
        for (int i = st[bel[r]]; i <= r; i++) {
            if (d[i] + mark[bel[i]] >= x)
                ans++;
        }
        for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
            ans += bs(st[i], ed[i], x - mark[i]);
        }
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    prework();
    while (q--) {
        char op;
        int l, r, x;
        cin >> op >> l >> r >> x;
        if (op == 'M') {
            add(l, r, x);
        } else {
            cout << query(l, r, x) << '\n';
        }
    }
}