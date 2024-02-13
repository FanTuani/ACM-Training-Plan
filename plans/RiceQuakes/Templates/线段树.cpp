#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, a[N], tree[4 * N], mark[4 * N];
void build(int l = 1, int r = n, int pos = 1) {
    if (l == r) {
        tree[pos] = a[l];
    } else {
        int mid = (l + r) / 2;
        build(l, mid, pos * 2), build(mid + 1, r, pos * 2 + 1);
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}
void push_down(int pos, int cl, int cr) {
    int mid = (cl + cr) / 2;
    tree[pos * 2] += (mid - cl + 1) * mark[pos];
    tree[pos * 2 + 1] += (cr - mid) * mark[pos];
    mark[pos * 2] += mark[pos];
    mark[pos * 2 + 1] += mark[pos];
    mark[pos] = 0;
}
void add(int l, int r, int ad, int pos = 1, int cl = 1, int cr = n) {
    if (cl > r or cr < l) {
        return;
    } else if (cl >= l and cr <= r) {
        tree[pos] += (cr - cl + 1) * ad;
        if (cr > cl)
            mark[pos] += ad;
    } else {
        push_down(pos, cl, cr);
        int mid = (cl + cr) / 2;
        add(l, r, ad, pos * 2, cl, mid);
        add(l, r, ad, pos * 2 + 1, mid + 1, cr);
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
    }
}
int query(int l, int r, int pos = 1, int cl = 1, int cr = n) {
    if (cl > r or cr < l) {
        return 0;
    } else if (cl >= l and cr <= r) {
        return tree[pos];
    } else {
        push_down(pos, cl, cr);
        int mid = (cl + cr) / 2;
        return query(l, r, pos * 2, cl, mid) +
               query(l, r, pos * 2 + 1, mid + 1, cr);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();
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