# Codeforces Round 928 (Div. 4) A~E+G

## A

统计 A 的个数, 查看其是否 $\geq 3$ 

```cpp
void solve(){
	string s;
    cin>>s;
    int cnt=0;
    for(int i=0; i<5; i++){
        cnt+=(s[i]=='A');
    }
    cout<<(cnt>=3?"A":"B")<<'\n';
}
```

## B

找到最左边的位置 $l$ 和最右边的位置 $r$ 。

正方形满足 : 1 的个数 = $(r-l+1)^2$ , 而三角形不满足

```cpp
int n;
char g[110][110];
void solve(){
	cin>>n;
    int l=2e9, r=-2e9, s=0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>g[i][j];
            if(g[i][j]=='1'){
                l=min(l,j);
                r=max(r,j);
                s++;
            }
        }
    }
    if((r-l+1)*(r-l+1)!=s) cout<<"TRIANGLE\n";
    else cout<<"SQUARE\n";
}
```

## C

根据题意预处理答案, 对每个询问输出答案即可

预处理代码 :

```cpp
void init(){
	for(int i=1; i<=2e5; i++){
		int cnt=0, tmp=i;
		while(tmp){
			cnt+=tmp%10;
			tmp/=10;
		}
		s[i]=s[i-1]+cnt;
	}
}
```

## D

由题意可知, 一组中最多有两个数， 如果有两个数 $a$ , $b$ , 需要满足 $a\oplus b=2147483647$ 。

因此对于每个 $a$ , 寻找有没有 $2147483647\oplus a$ , 有的话, 将它们俩放到一组。

```cpp
int n;
map<int, int> q;
void solve(){
	q.clear();
	cin>>n;
	for(int i=1; i<=n; i++){
		int x;
		cin>>x;
		q[x] ++;
	}
	// a^b=2147483647
	// 知 a, 得b=2147483647^a 
	int res=0;
	for(auto t : q){
		int a=t.first, b=t.second;
		if(b==0) continue;
		int c=(a^2147483647LL), d=q[c];
		res+=max(b,d);
		q[c]=0;
	}
	cout<<res<<'\n';
}
```

## E

观察可得, 有效的步骤只有 $2^i$ , $i\in 0,1,2,\cdots$ 布。

假设当前牌还有 $x$ 张, 每一步会选出 $\lceil\frac{x}{2}\rceil$ 张牌。

对于给定的 $n$, $k$, 在 $O(\log n)$ 时间内就能求出哪一步

```cpp
void solve(){
	cin>>n>>k;
	int now=0, cnt=1, tmp;
	while(now<k){
		cnt*=2ll;
		tmp=(n+1)/2;
		now+=(n+1)/2;
		n=n-(n+1)/2;
	}
	cnt/=2, now-=tmp;
	cout<<cnt*(2ll*(k-now)-1)<<'\n';
}
```

## G

对于每个结点 $x$ , 统计它的除父节点以外的相邻结点的 $P$ 个数 $cntp$ 和 $S$ 结点个数 $cnts$ 。

如果当前节点是 $S$ , 需要建 $cntp$ 座墙 ;

如果当前节点是 $P$ , 需要建 $cnts$ 座墙 ;

如果当前节点是 $C$ , 需要建 $\min (cnts,cntp)$ 座墙, 并转化为子节点数量大的那个结点。

```cpp
int n, res=0;
string str;
vector<int> e[N];
void dfs(int u, int fa){
	int cnts=0, cntp=0;
	for(auto v : e[u]){
		if(v==fa) continue;
		dfs(v, u);
		if(str[v]=='S') cnts ++;
		else if(str[v]=='P')cntp ++;
	}
	if(str[u]=='S') res+=cntp;
	else if(str[u]=='P') res+=cnts;
	else{
		res+=min(cntp,cnts);
		if(cntp>cnts){
			str[u]='P';	
		}
		else if(cntp<cnts){
			str[u]='S';
		}
		else{
			str[u]='C';
		}
	}
}
```


