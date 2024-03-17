# 树形DP

## P1352 没有上司的舞会

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int r[6100], st[6100], dp[6100][2];
vector<int> g[6100];
void dfs(int u, int fa){
    dp[u][1] = r[u];
    for(int v : g[u]){
        if(v == fa) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][1], dp[v][0]);
        dp[u][1] += dp[v][0];
    }
}
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> r[i];
    }
    for(int i = 1; i < n; i ++){
        int x, y;
        cin >> x >> y;
        g[y].push_back(x);
        st[x] = true;
    }
    for(int i = 1; i <= n; i ++){
        if(st[i] == false){
            dfs(i, 0);
            cout << max(dp[i][0], dp[i][1]);
            break;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T --){
        solve();
    }

    return 0;
}
```

## GPLT L3 - 035 完美树

> 给你一棵树，每个结点具有 $0$ 或 $1$ 其中一种颜色， 你可以消耗 $p_i$ 代价修改颜色。定义完美树为 : 所有子树的01之差超过 1

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1e5 + 10;
int n, k, c[N], p[N], sz[N], dp[N][3];
vector<int> e[N];
void dfs(int u){
    /*
        sz[u] : 维护以 u 为根的子树大小
        cnt : 子树中 sz[v] 为奇数的数量
        sum0 : 维护偶数大小子树的代价
        sum1 : 维护所有奇数子树中 0 多一个的代价
        tmp : 维护 dp[v][1] - dp[v][0] 与 sum1 组合表示代价
    */
    sz[u] = 1; 
    int cnt = 0, sum0 = 0, sum1 = 0;
    vector<int> tmp;
    for(int v : e[u]){
        dfs(v);
        sz[u] += sz[v];
        if(sz[v] % 2 == 0){
            sum0 += dp[v][2];
        }
        else{
            cnt ++;
            sum1 += dp[v][1]; // 初始时全部都选 1
            tmp.push_back(dp[v][0] - dp[v][1]); // 选 0
        }
    }
    int len = tmp.size();
    sort(tmp.begin(), tmp.end());
    if(cnt == 0){ // 所有子树的大小都是偶数, sz[u] 是奇数
        // 以 u 为根的子树中 0 多一个
        dp[u][0] = sum0 + (c[u] == 0 ? 0 : p[u]);
        // 以 u 为根的子树中 1 多一个
        dp[u][1] = sum0 + (c[u] == 1 ? 0 : p[u]);
    }
    else if(cnt % 2 == 1){ // 奇数个奇数大小子树, sz[u] 是偶数
        int now = 0;
        for(int i = 0; i < len / 2; i ++) now += tmp[i]; // sum1 + now : 少选一个 0, 多选一个 1
        // 维护以 u 为根的子树中 0 的数量 = 1 的数量
        // 此时 u 的颜色为 0
        // 子树中多选一个 1, u 需要改为 0
        // 子树中多选一个 0, u 需要改为 1
        dp[u][2] = sum0 + sum1 + min(now + (c[u] == 1 ? p[u] : 0), now + tmp[len / 2] + (c[u] == 0 ? p[u] : 0));
    }
    else{ // 偶数个奇数大小的子树, sz[u] 是奇数
        int now = 0;
        for(int i = 0; i < len / 2; i ++) now += tmp[i]; // sum1 + now : 选一半 0 和一半 1
        // 维护 0 多一个的情况 :
        // 各选一半然后保证 u = 0 ; 多选一个 0, 少选一个 1, 将 u 改为 1, 此时 0 还是多一个
        dp[u][0] = sum0 + sum1 + min(now + (c[u] == 1 ? p[u] : 0), now + tmp[len / 2] + (c[u] == 0 ? p[u] : 0));
        // 维护 1 多一个的情况 :
        // 各选一半然后保证 u = 1 ; 多选一个 1, 少选一个 0, 将 u 改为 0, 此时 1 还是多一个 
        dp[u][1] = sum0 + sum1 + min(now + (c[u] == 0 ? p[u] : 0), now - tmp[len / 2 - 1] + (c[u] == 1 ? p[u] : 0));
    }
}
void solve(){
    cin >> n;
    for(int i = 1 ; i <= n; i ++){
        cin >> c[i] >> p[i] >> k;
        while(k --){
            int x;
            cin >> x;
            e[i].push_back(x);
        }
    }
    dfs(1);
    if(n % 2 == 1){
        cout << min(dp[1][0], dp[1][1]) << '\n';
    }
    else{
        cout << dp[1][2] << '\n';
    }
}
// 目标 : 任意一颗子树 0/1 之差不超过 1
// dp[i][0] : 以 i 为根的子树 0 比 1 多
// dp[i][1] : 以 i 为根的子树 1 比 0 多
// dp[i][2] : 以 i 为根的子树 1 和 0 个数相同
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T --){
        solve();
    }

    return 0;
}
```

## P2016 战略游戏

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int> e[1600];
int dp[1600][2];
void dfs(int u, int fa){
    dp[u][1] = 1;
    for(int v : e[u]){
        if(v == fa){
            continue;
        }
        dfs(v, u);
        dp[u][1] += min(dp[v][0], dp[v][1]);
        dp[u][0] += dp[v][1];
    }
}
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        int id, k, x;
        cin >> id >> k;
        id ++;
        for(int i = 1; i <= k; i ++){
            cin >> x;
            x ++;
            e[id].push_back(x);
            e[x].push_back(id);
        }
    }
    dfs(1, 0);
    cout << min(dp[1][0], dp[1][1]);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T --){
        solve();
    }

    return 0;
}
/*
    dp[u][0/1] 表示以 u 为根的子树中所有边都被观察到
    0 : 表示 u 不放 ; 1 : 表示 u 放
    所需要的最少士兵
*/
```

## P1122 最大子树和

$dp_u$ 表示以 $u$ 为根的子树的最大和，$dp_u+=\max(dp_v,0)$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, mx = -2e9;
int a[16010], dp[16010];
vector<int> e[16010];
void dfs(int u, int fa){
    dp[u] = a[u];
    for(int v : e[u]){
        if(v == fa) continue;
        dfs(v, u);
        dp[u] += max(0ll, dp[v]);
    }
    mx = max(mx, dp[u]);
}
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i < n; i ++){
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1, 0);
    cout << mx;
    return 0;
} 
/*
    dp[u] 表示以 u 为根节点的子树, 得到的最大值
*/
```

## P2014 选课

算是树形背包的裸题，注意到每个课 $s_i$ 都是正数，因此用最多选 $m$ 课得到的最大分数就能代表恰好选 $m$ 课得到的最大学分

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, w[310], v[310], f[310][310];
vector<int> e[310];
void dfs(int x){
    for(int i = 1; i <= m; i ++) f[x][i] = w[x];
    for(int y : e[x]){
        dfs(y);
        for(int i = m; i >= v[x];  i--){
            for(int j = 0; j + v[x] <= i; j ++){
                f[x][i] = max(f[x][i], f[y][j] + f[x][i - j]);
            }
        }
    }
}
void solve(){
    cin >> n >> m;
    if(m >= n) m = n;
    m ++;
    for(int i = 1; i <= n; i ++){
        int k;
        cin >> k >> w[i]; 
        e[k].push_back(i);
    }
    for(int i = 0; i <= n; i ++){
        v[i] = 1;
    }
    dfs(0);
    cout << f[0][m] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T --){
        solve();
    }

    return 0;
}
```
