# sol

## A

- 开头没有刺

- 下一个格子不是刺, 直接走到下一个格子

- 下一个是刺, 看看跳两格的操作能否合法

```cpp
void solve(){
    cin>>n>>s;
    int res=0;
    for(int i=0; i<n; i++){
        if(s[i]=='@') res++;
        if(s[i]=='*'&&i+1<n&&s[i+1]=='*') break;
    }
    cout<<res<<'\n';
}
```

## B

对于每个 $a_i$ , 输出一个数 $x$ , 满足 $x=k\times a_i$ , $x>now$ , 且 $x$ 尽量小

$x=\lfloor\frac{now}{a_i}\rfloor*a_i+a_i$ 

```cpp
void solve(){
    cin>>n;
    now=0;
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        now=(now/x)*x+x;
    }
    cout<<now<<'\n';    
}
```

（赛时推了一下式子,没推好,用了上取整,没推出来,二分写的）

## C

根据结果序列倒着推, 可以取模, 从而避免了数值过大

```cpp
void solve(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>a[i];
    } 
    cin>>s;
    // 找到最后剩余的一个字母的位置 
    int l=1,r=n;
    for(int i=0; i<s.size()-1; i++){
        if(s[i]=='L') l++;
        else r--; 
    }
    // 存放答案 
    vector<int> ans;
    int p=a[l]%m;
    for(int i=s.size()-1; i>=1; i--){
        ans.push_back(p);
        if(s[i-1]=='L'){ // 观察上一个字母是什么 
            l--;
            p=p*a[l]%m;
        }
        else{
            r++;
            p=p*a[r]%m;
        }
    }
    ans.push_back(p);
    for(int i=ans.size()-1; i>=0; i--){
        cout<<ans[i]<<" \n"[i==0];
    }
}
```

(赛时没发现数据会超过 $long\;long$ , 是 $n$ 个 $a_i$ 相乘, 是 $(a_i)^n$ , 理解成了相加的过程,以为是 $n*a_i$ )

## D

- 不是王牌花色的先跟自己同花色打

- 打剩下的去找王牌花色

- 如果王牌花色还有剩的,内部消化

```cpp
int n;
char x;
int cnt1, cnt2;
string s1[35], s2[35];
bool st1[35], st2[35]; 
void solve(){
    cin>>n>>x;
    cnt1=0, cnt2=0;
    for(int i=1; i<=n*2; i++){
        string s;
        cin>>s;
        if(s[1]==x){
            s1[++cnt1]=s;
        }
        else{
            s2[++cnt2]=s;
        }
        st1[i]=st2[i]=false;
    }
    sort(s1+1,s1+cnt1+1,[](string a, string b){
        return a[0]<b[0];
    });
    sort(s2+1,s2+cnt2+1,[](string a, string b){
        return a[0]<b[0];
    });
    vector<pair<string,string> > ans;
    for(int i=1; i<=cnt2; i++){
        if(st2[i]) continue;
        for(int j=i+1; j<=cnt2; j++){
            if(st2[j]) continue;
            if(s2[i][1]==s2[j][1]){
                ans.push_back({s2[i],s2[j]});
                st2[i]=true;
                st2[j]=true;
                break;
            }
        }
    }
    int tmp=0;
    for(int i=1; i<=cnt2; i++){
        if(st2[i]==false){
            if(tmp<cnt1){
                tmp++;
                ans.push_back({s2[i], s1[tmp]});
            }
        }
    }
    for(int i=tmp+1; i+1<=cnt1; i+=2){
        ans.push_back({s1[i], s1[i+1]});
    }
    if(ans.size()==n){
        for(auto t : ans){
            cout<<t.first<<' '<<t.second<<'\n';
        }
    }
    else{
        cout<<"IMPOSSIBLE\n";
    }
}
```

- 赛时洋洋洒洒写了一大堆, 一开始 $dfs$ 枚举第一个人的出牌顺序, 再用匈牙利求第二个人的卡牌与第一个人的最大匹配, 发现超时了, 最坏时间复杂度 $O(t*2^n*n^3)$ , 会超时

- 然后想到取消 $dfs$ , 直接匈牙利算法求最大匹配, 其实这样不一定是二分图(有奇环), 当时不知道怎么想的, 还是写了, 写出来发现不对了, 然后比赛就结束了

- 其实赛时观察过题人数都接近 $C$ 了, 就能想到这题没有那么多算法, 有点当局者迷了

## E

找规律, 从每一位的角度考虑, 发现对于 $x$ , 个位变化 $x$ 次, 十位变化 $\frac{x}{10}$ 次, 百位变化 $\frac{x}{100}$ 次, ... 把式子竖起来看, 发现每一位是一种前缀和, 模拟一下高精度加法就行了。

```cpp
int n;
int s[400010];
string str;
void solve(){
    cin>>n>>str;
    for(int i=0; i<str.size(); i++){
        s[i+1]=s[i]+(str[i]-'0');
    }
    vector<int> ans;
    int t=0;
    for(int i=n; i>=1; i--){
        t+=s[i];
        ans.push_back(t%10);
        t/=10;
    }
    if(t) ans.push_back(t);
    int p=ans.size()-1;
    while(ans[p]==0) p--;
    for(int i=p; i>=0; i--){
        cout<<ans[i];
    }
    cout<<'\n';
}
```

## F

- $dp_i$ 表示当前考虑到 $i$ 点，且选择 $i$ 点的答案数

- $cnt_i$ 表示满足以下条件线段的数量 : $l\leq i \leq r$ 

- $lft_i$ 表示所有包含 $i$ 的线段中最左边的左端点

- $cnt_i$ 用差分来维护

- $lft_i$ 具有单调性, 反证法 : 假设 $lft_{i+1}<lft_i$ , 那么存在线段 $[lft_{i+1},\geq i+1]$ , 这个线段包括了 $i$, 会更新 $lft_i$ 

- 根据 $lft_i$ 的单调性, 对线段排序之后, 用 $j$ 表示下一个待求 $lft$ 下标, 先给定的 $l$ 一定更小, 对于每个线段, 直接更新所有 $[l,r]$ 中的尚未更新的 $lft$ 

```cpp
int const N = 1e6+10;
int n, m;
pair<int, int> seg[N];
int dp[N], maxv[N], lft[N], cnt[N];
// dp[i]=max(dp[j])+cnt[i], j<lft[i]
// cnt[i] 表示满足以下条件线段数量 : l<=i<=r
// lft[i] 表示所有包含 i 的线段的最左端点 
// 维护 cnt 用差分  
void solve(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cnt[i]=0;
    }
    for(int i=1; i<=m; i++){
        int l, r;
        cin>>l>>r;
        seg[i]={l, r};
        cnt[l]++, cnt[r+1]--;
    }
    for(int i=1; i<=n; i++){
        cnt[i]+=cnt[i-1];
    }
    sort(seg+1, seg+m+1);
    // j 表示下一个待求 lft 下标 
    for(int i=1, j=1; i<=m; i++){
        int l=seg[i].first, r=seg[i].second;
        while(j<=n&&j<=r){
            lft[j]=l;
            j++;
        }
    }
    int res=0;
    for(int i=1; i<=n; i++){
        dp[i]=(cnt[i]?maxv[lft[i]-1]+cnt[i]:dp[i-1]);
        maxv[i]=max(maxv[i-1], dp[i]);
        res=max(res, dp[i]);
    }
    cout<<res<<'\n';
}
```

- 不太容易看出来的 $dp$

- $lft$ 的维护较为困难, 单调性也稍难看出, 待求坐标的维护思想值得学习
