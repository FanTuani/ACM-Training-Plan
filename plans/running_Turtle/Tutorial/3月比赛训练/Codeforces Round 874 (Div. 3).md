# Codeforces Round 874 (Div. 3)

## A

对于字符串 $s$ , 记录下所有的 $s_i+s_{i+1}$ ， 答案即是他们的种类之和

```cpp
int n;
string s;
void solve(){
    set<string> res;
    cin>>n>>s;
    for(int i=0; i<n-1; i++){
        res.insert(s.substr(i, 2));
    }
    cout<<res.size()<<'\n';
}
```

## B

实际上, 如果我们把 $a$ 排序, 在坐标轴上按照 $[a_i-k,a_i+k]$ 画出一片不规则区域。要想 $b_i$ 构成的曲线被完全包括在其中, $b$ 数组最好的选择是升序放入其中。现在 $a$ 是乱序的, 把 $a$ 离散化之后, 输出 $b$ 数组中对应那么大的数

```cpp
struct node{
    int val, id;
    bool operator < (const node & T){
        return val<T.val;
    }
};
node a[100010], tmp[100010];
int n, k, b[100010];
void solve(){
    cin>>n>>k;
    for(int i=1; i<=n; i++){
        cin>>a[i].val;
        a[i].id=i;
        tmp[i]=a[i];
    }
    for(int i=1; i<=n; i++) cin>>b[i];
    sort(tmp+1, tmp+n+1);
    sort(b+1, b+n+1);
    for(int i=1; i<=n; i++){
        a[tmp[i].id].id=i;
    }
    for(int i=1; i<=n; i++){
        cout<<b[a[i].id]<<" \n"[i==n];
    }
}
```

## C

> 给你一个数组 $a$ , 对每个 $a_i$ 执行任意次数以下操作 : 
> 
> 1. 保持 $a_i$ 不变
> 
> 2. 令 $a_i=a_i-a_j$ , $j\in [1,n]$ 
> 
> 判断能否通过以上操作使得 $a$ 数组中所有 $a_i$ 的奇偶性相同, 且 $a_i\geq 0$ 

- 如果 $a$ 中全部都是奇数或者全部都是偶数, 成立 ;

- 如果 $a$ 中即有奇数，又有偶数 :
  
  - 无法把 $a$ 全部构造为偶数, 因为最小的奇数没有奇数可以减
  
  - 只要最小的偶数大于最小的奇数, 既可以全部构造成奇数, 否则不能

```cpp
int n;
int a[200010], b[200010];
void solve(){
    a[0]=b[0]=0;
    cin>>n;
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        if(x&1) a[++a[0]]=x;
        else b[++b[0]]=x;
    }
    if(a[0]==0||b[0]==0){
        cout<<"YES\n";
    }
    else{
        sort(a+1, a+a[0]+1);
        sort(b+1, b+b[0]+1);
        if(b[1]>a[1]) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```

## D

```latex
错因 : 
    char 溢出, char 可以存 [0, 255], 想用 string 存答案, 
    必须保证每个字符比较小，或者干脆直接不用（推荐）
解法 :
    n=1, 输出 1 即可 ;
    否则记录下 n 和 n-1 的位置 p1, p2: 
    如果最大值位于 n, 翻转 [n,n] 或者 枚举左端点 [1,p1-1], 
    固定右端点为 p1-1, 进行翻转比较答案 ;
    如果最大值位于 1, 同理以上操作把 n-1 翻转到第一位, 更新答案 ;
    其余情况, 直接枚举左端点, 固定右端点， 同时更新答案
```

```cpp
int n, p1, p2, cnt;
int a[2100];
vector<int> ans;
void op(int l, int r){
    vector<int> tmp;
    for(int i=r+1; i<=n; i++) tmp.push_back(a[i]);
    for(int i=r; i>=l;  i--) tmp.push_back(a[i]);
    for(int i=1; i<l; i++) tmp.push_back(a[i]);
    if(ans.size()==0){
        swap(ans, tmp);
    }
    else{
        for(int i=1; i<=n; i++){
            if(tmp[i]>ans[i]){
                swap(ans, tmp);
                break;
            }
            else if(tmp[i]<ans[i]) break;
        }
    }
}
// 操作种类 : 
// r<n, 将 a[r+1] 放在第一个位置
// r=n, 将 a[n] 放在第一个位置  
void solve(){
    ans.clear();
    cnt=0;
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        if(a[i]==n) p1=i;
        if(a[i]==n-1) p2=i;
    }
    if(n==1){
        cout<<"1\n";
        return ;
    }
    if(p1==n){ // 最大值位于 n 
        op(n, n);
        for(int i=1; i<=n-1; i++) op(i,n-1);
    }
    else if(p1!=1){
        for(int i=1; i<=p1-1; i++) op(i,p1-1);
    }
    else{
        if(p2==n){
            op(n,n);
            for(int i=1; i<=n-1; i++) op(i,n-1);
        }
        else{
            for(int i=1; i<=p2-1; i++) op(i,p2-1);
        }
    }
    for(auto t : ans) cout<<t<<' ';
    cout<<'\n';
}
```

## E

首先, 根据题目条件, 所有点的入度 $\leq 2$ 。

 我们首先去掉所有重边，用并查集维护连通的点, 如果成环了, 那么所有连通点一定都在环内;

最多成环的数量就是所有连通块的数量，最少成环的数量就是所有成环的连通块数量, 如果还有不在环内的点, 最少成环的数量 $+1$  

```cpp
int n, p[200010], sz[200010];
int find(int x){
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
void solve(){
    int cnt=0, s=0; // 环的数量 ; 环内点的数量 
    set<pair<int, int>> eg; // 存入边, 然后去掉重边 
    cin>>n;
    for(int i=1; i<=n; i++){
        p[i]=i;
        sz[i]=1;
    }
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        eg.insert({min(i, x),max(i,x)});
    }
    for(auto t : eg){
        int a=t.first, b=t.second;
        int pa=find(a), pb=find(b);
        if(pa==pb){ // 因为每个点的度最多为 2, 且无重边, 因此所有联通点都在环内 
            cnt ++;
            s+=sz[pa];
        }
        else{
            p[pb]=pa;
            sz[pa]+=sz[pb];            
        }
    }
    int res=0; // 最多环 
    for(int i=1; i<=n; i++){
        res+=(p[i]==i);
    }
    cout<<cnt+(s!=n)<<' '<<res<<'\n';
}
```

## F

把相同的数据打包成 `pair : {val, cnt}`, 然后从小到大排序

每 $m$ 个检查一次，如果 $mx-mn=m-1$ , 答案加上这段的区间乘

区间乘注意用逆元处理

```cpp
int const P = 1e9+7;
int n, m;
int tmp[200010], pd[200010];
pair<int, int> a[200010]; // {数值, 次数} 
int ksm(int a, int k){
    int res=1;
    while(k){
        if(k&1) res=(res*a)%P;
        k>>=1;
        a=(a*a)%P;
    }
    return res;
}
int inv(int x){
    return ksm(x, P-2);
}
void solve(){
    map<int, pair<int,int> > q; // 统计某个值的 {l, r} 端点 
    int cnt=0;
    pd[0]=1;
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>tmp[i]; 
    }
    sort(tmp+1, tmp+n+1);
    for(int i=1; i<=n; i++){
        int j=i;
        while(j<=n&&tmp[j]==tmp[i]) j++;
        a[++cnt]={tmp[i], j-i};
        i=j-1;
    }
    for(int i=1; i<=cnt; i++){
        pd[i]=pd[i-1]*a[i].second%P;
    }    
    // 至少有 m 个数, 首先预处理前 m 个数
    int res=0;
    for(int i=1; i+m-1<=cnt; i++){
        int r=i+m-1;
        if(r<=cnt&&a[r].first-a[i].first==m-1) res=(res+pd[r]*inv(pd[i-1])%P)%P;
    }
    cout<<res<<'\n';
}
```

## G

`dfs` 深搜时, 入下回离, 回的时候, 即可统计当前节点左右子树的节点数量, 如果回的时候节点数等于 $3$ , 切割该点与父节点的边 ; 如果节点数 $>3$ , 无解

```cpp
#define int long long
int n;
vector<pair<int, int>> g[200010];
int d[200010];
vector<int> ans;
int ok=1;
void dfs(int u, int fa, int id){
    if(ok==0) return ;
    d[u]=1;
    for(auto eg : g[u]){
        int v=eg.first, id_=eg.second;
        if(v==fa) continue;
        dfs(v, u, id_);
        d[u]+=d[v];
    }
    if(d[u]>3) ok=0;
    if(d[u]==3){
        d[u]=0;
        ans.push_back(id);
    }
}
void solve(){
    ok=1;
    ans.clear();
    cin>>n;
    for(int i=1; i<=n; i++) g[i].clear();
    for(int i=1; i<n; i++){
        int u, v;
        cin>>u>>v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    dfs(1, 0, 0);
    if(ok==false || d[1]) cout<<"-1\n";
    else{
        ans.pop_back();
        cout<<ans.size()<<'\n';
        for(auto i : ans) cout<<i<<' ';
        cout<<'\n';
    }
} 
```
