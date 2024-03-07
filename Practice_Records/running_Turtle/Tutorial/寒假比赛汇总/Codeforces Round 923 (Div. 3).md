# Codeforces Round 923 (Div. 3)

## A

想把黑色全部染色还要最短, 最左到最右染色即可

```cpp
void solve(){
    cin>>n>>s;
    if(s.find("B")==string::npos) cout<<"0\n";
    else cout<<(int)s.rfind("B")-(int)s.find("B")+1<<'\n';
}
```

## B

根据题意模拟即可

```cpp
void solve(){
    map<char, int> q;    
    q.clear();
    string res="";
    cin>>n;
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        if(x==0){
            for(char j='a'; j<='z'; j++){
                if(q[j]==0){
                    q[j]=1;
                    res+=(char)j;
                    break;        
                }
            }
        }
        else{
            for(char j='a'; j<='z'; j++){
                if(q[j]==x){
                    q[j]=x+1;
                    res+=(char)j;
                    break;        
                }
            }
        }
    }
    cout<<res<<'\n';
}
```

## C

- [1,k] 同时出现在a,b之中

- a,b都需要至少包含[1,k]中一半的元素

- 借助线段的思想理解

```cpp
bool check1(int len1, int x[], int len2, int y[]){
    set<int> tmp;
    for(int i=1; i<=len1; i++){
        if(x[i]>=1 && x[i]<=k){
            tmp.insert(x[i]);    
        }
    }
    for(int i=1; i<=len2; i++){
        if(y[i]>=1 && y[i]<=k){
            tmp.insert(y[i]);
        } 
    }
    return (tmp.size()>=k);
}
bool check2(int len, int x[]){
    set<int> tmp;
    for(int i=1; i<=len; i++){
        if(x[i]>=1 && x[i]<=k){
            tmp.insert(x[i]);    
        }
    }
    return (tmp.size()>=k/2);
}
void solve(){
    cin>>n>>m>>k;
    for(int i=1; i<=n; i++){
        cin>>a[i];
    }
    for(int i=1; i<=m; i++){
        cin>>b[i];
    }
    cout<<(check1(n,a,m,b)&&check2(n,a)&&check2(m,b)?"YES":"NO")<<'\n';
    // 1. a+b 至少包含出来 [1, k] 所有数字
    // 2. a & b 至少包含 k/2 个合法数字
}
```

## D

维护数值转折点的前缀和,二分查找位置

```cpp
int n, q;
int last, s[1000010];
void solve(){
    cin>>n;
    last=-1;
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        s[i]=s[i-1];
        if(x!=last){
            s[i] ++;            
        }
        last=x;
    }
    cin>>q;
    for(int i=1; i<=q; i++){
        int left, right;
        cin>>left>>right;
        if(s[left]==s[right]){
            cout<<"-1 -1\n";
        }
        else{
            int l=left, r=right;
            while(l<r){
                int mid=l+r>>1;
                if(s[mid]>s[left]) r=mid;
                else l=mid+1;
            }
            cout<<left<<' '<<r<<'\n';
        }
    }
    cout<<'\n';
}
```

## E

观察到 , $s$ 数组的形态为 $[x,x+1,x,x+1,\cdots]$ 或 $[x,x-1,x,x-1,x,\cdots]$ 

按照第一种方式构造,

- 对于奇数位, $a_{i+k}=a_i+1$ 

- 对于偶数位, $a_{i+k}=a_i-1$ 

填充完前 $k$ 个, 按以上两种方式构造即可

```cpp
int n, k;
int a[200010];
void solve(){
    cin>>n>>k;
    int l=1, r=n;
    for(int i=1; i<=k; i++){
        if(i&1){
            a[i]=l;
            for(int j=i+k; j<=n; j+=k){
                a[j]=a[j-k]+1;
                l=a[j];
            }
            l ++;
        }
        else{
            a[i]=r;
            for(int j=i+k; j<=n; j+=k){
                a[j]=a[j-k]-1;
                r=a[j];
            }
            r --;
        }
    }
    for(int i=1; i<=n; i++){
        cout<<a[i]<<" \n"[i==n];
    }
}
```

## F

按照边权从大到小维护并查集, 同时构建一张图, 其中只不包含添加后成环的边, 最后一条没添加的边就是最轻的边, 再用 `dfs` 找到这个环。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, st, ed;
int fa[200010];
vector<int> ans;
struct Edge{
    int u, v, w;
}e[200010];
bool vis[200010];
vector<int> To[200010];
int find(int x){
    if(x!=fa[x]) fa[x]=find(fa[x]);
    return fa[x];
}
bool merge(int u, int v){
    int fu=find(u), fv=find(v);
    if(fu==fv){
        return true;
    }
    else{
        fa[fv]=fu;
        return false;
    }
}
void dfs(int u){
    if(u==ed){
        cout<<ans.size()<<'\n';
        for(int i=0; i<ans.size(); i++)
            cout<<ans[i]<<" \n"[i==ans.size()-1];
        return;
    }
    for(auto v : To[u]){
        if(!vis[v]){
            vis[v]=true;
            ans.push_back(v);
            dfs(v);
            ans.pop_back();
            vis[v]=false;
        }
    }
}
void solve(){
    ans.clear();
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        fa[i]=i;
        To[i].clear();
        vis[i]=false;
    }
    for(int i=1; i<=m; i++){
        int a, b, w;
        cin>>a>>b>>w;
        e[i]={a,b,w};
    }
    sort(e+1,e+m+1,[](Edge a, Edge b){
        return a.w>b.w;
    });
    int pos;
    for(int i=1; i<=m; i++){
        int u=e[i].u, v=e[i].v, w=e[i].w;
        if(merge(u, v)){
            pos=i;
        }
        else{
            To[u].push_back(v);
            To[v].push_back(u);
        }
    }
    cout<<e[pos].w<<' ';
    st=e[pos].u,ed=e[pos].v;
    vis[st]=true, ans.push_back(st);
    dfs(st);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    while(T --){
        solve();
    }    

    return 0;
} 
```
