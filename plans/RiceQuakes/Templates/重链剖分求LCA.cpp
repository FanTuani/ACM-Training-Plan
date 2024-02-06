#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f3f3f3f;
vector<int> con[N];
int dep[N], hson[N], fa[N], sz[N], top[N];
void dfs(int a, int f) {
    fa[a] = f;
    sz[a] = 1;
    dep[a] = dep[f] + 1;
    int mx = 0;
    for (int t : con[a]) {
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
    for (int t : con[a]) {
        if (t == fa[a])
            continue;
        if (t == hson[a])  // top[t] = hson[a] == t ? top[a] : t;
            top[t] = top[a];
        else
            top[t] = t;
        df(t);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q, s;
    cin >> n >> q >> s;
    for (int i = 1; i < n; i++) {
        int f, t;
        cin >> f >> t;
        con[f].push_back(t);
        con[t].push_back(f);
    }
    dfs(s, s);
    top[s] = s;
    df(s);
    while (q--) {
        int a, b;
        cin >> a >> b;
        while (top[a] != top[b]) {
            if (dep[top[a]] > dep[top[b]])
                a = fa[top[a]];
            else
                b = fa[top[b]];
        }
        if (dep[a] > dep[b])
            cout << b << '\n';
        else
            cout << a << '\n';
    }
}