#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f3f3f3f;
int n, a[N], tr[N];
struct P {
    int num, idx;
} b[N];
bool cmp(P q, P w) {
    return q.num < w.num;
}
int lowbit(int x) {
    return x & (-x);
}
void add(int pos, int x) {
    while (pos <= n) {
        tr[pos] += x;
        pos += lowbit(pos);
    }
}
int ask(int pos) {
    int ans = 0;
    while (pos) {
        ans += tr[pos];
        pos -= lowbit(pos);
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i].num;
        b[i].idx = i;
    }
    sort(b + 1, b + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        if (b[i].num != b[i - 1].num)
            a[b[i].idx] = i;
        else
            a[b[i].idx] = a[b[i - 1].idx]; // if not unique
    }  // lsh
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += ask(a[i] - 1);
        add(a[i], 1);
    }
    cout << ans;
}