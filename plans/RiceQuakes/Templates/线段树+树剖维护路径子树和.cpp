#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, q, root, mod, t[4 * N], mk[4 * N], top[N], hson[N], dep[N], dn[N], a[N],
    fa[N], sz[N], b[N], mxdn[N], cnt;

void build(int l, int r, int pos = 1);
void push_down(int pos, int cl, int cr);
void add(int l, int r, int x, int pos = 1, int cl = 1, int cr = n);
int query(int l, int r, int pos = 1, int cl = 1, int cr = n);
vector<int> con[N];
void dfs(int a, int f) {
    fa[a] = f;
    sz[a] = 1;
    dep[a] = dep[f] + 1;
    int mx = 0;
    for (auto t : con[a]) {
        if (t == f)
            continue;
        dfs(t, a);
        sz[a] += sz[t];
        if (sz[t] > mx) {
            mx = sz[t];
            hson[a] = t;
        }
    }
}
void df(int a) {
    dn[a] = ++cnt;
    if (hson[a]) {
        top[hson[a]] = top[a];
        df(hson[a]);
    }
    for (auto t : con[a]) {
        if (top[t])
            continue;
        top[t] = t;
        df(t);
    }
    mxdn[a] = cnt;
}
void upd_path(int a, int b, int x) {
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) {
            add(dn[a], dn[top[a]], x);
            a = fa[top[a]];
        } else {
            add(dn[b], dn[top[b]], x);
            b = fa[top[b]];
        }
    }
    add(dn[a], dn[b], x);
}
int query_path(int a, int b) {
    int ans = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) {
            ans += query(dn[a], dn[top[a]]);
            a = fa[top[a]];
        } else {
            ans += query(dn[b], dn[top[b]]);
            b = fa[top[b]];
        }
    }
    return ans + query(dn[a], dn[b]);
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q >> root >> mod;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
        con[t].push_back(f);
    }
    dfs(root, root);
    top[root] = root;
    df(root);
    for (int i = 1; i <= n; i++) {
        a[dn[i]] = b[i];
    }
    build(1, n);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int f, t, x;
            cin >> f >> t >> x;
            upd_path(f, t, x);
        } else if (op == 2) {
            int f, t;
            cin >> f >> t;
            cout << query_path(f, t) % mod << '\n';
        } else if (op == 3) {
            int s, x;
            cin >> s >> x;
            add(dn[s], mxdn[s], x);
        } else {
            int s;
            cin >> s;
            cout << query(dn[s], mxdn[s]) % mod << '\n';
        }
    }
}

void build(int l, int r, int pos) {
    if (l == r) {
        t[pos] = a[l];
    } else {
        int mid = l + r >> 1;
        build(l, mid, pos * 2), build(mid + 1, r, pos * 2 + 1);
        t[pos] = t[pos * 2] + t[pos * 2 + 1];
    }
}
void push_down(int pos, int cl, int cr) {
    int mid = cl + cr >> 1;
    mk[pos * 2] += mk[pos];
    mk[pos * 2 + 1] += mk[pos];
    t[pos * 2] += (mid - cl + 1) * mk[pos];
    t[pos * 2 + 1] += (cr - mid) * mk[pos];
    mk[pos] = 0;
}
void add(int l, int r, int x, int pos, int cl, int cr) {
    if (l > r)
        swap(l, r);
    if (cr < l or cl > r) {
        return;
    } else if (cl >= l and cr <= r) {
        t[pos] += (cr - cl + 1) * x;
        if (cr > cl)
            mk[pos] += x;
    } else {
        int mid = cl + cr >> 1;
        push_down(pos, cl, cr);
        add(l, r, x, pos * 2, cl, mid), add(l, r, x, pos * 2 + 1, mid + 1, cr);
        t[pos] = t[pos * 2] + t[pos * 2 + 1];
    }
}
int query(int l, int r, int pos, int cl, int cr) {
    if (l > r)
        swap(l, r);
    if (cr < l or cl > r) {
        return 0;
    } else if (cl >= l and cr <= r) {
        return t[pos];
    } else {
        int mid = cl + cr >> 1;
        push_down(pos, cl, cr);
        return query(l, r, pos * 2, cl, mid) +
               query(l, r, pos * 2 + 1, mid + 1, cr);
    }
}