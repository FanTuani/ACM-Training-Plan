# Codeforces Round 922 (Div. 2) A~F

## A

优先横着放 $1\times2$ 的砖块, $m$ 是奇数再补一块 $1\times 3$ 的砖块

所以 , $answer=n\times\lfloor \frac{m}{2}\rfloor$ 

```cpp
void solve(){
    cin>>n>>m;
    cout<<n*(m/2)<<'\n';
}
```

## B

先把 $a$ 排序 , 发现给出的样例输出中的逆序对跟把 $a$ 排序的逆序对数量一样, 交上过了

实际上 , 以样例三为例 :

- stdin : 

```latex
6
2 3 4 6 5 1
1 2 4 3 5 6
```

因为交换次数是无限的 , 我们先把 $a$ 排序 , 得到如下数组 :

```latex
1 2 3 4 5 6
6 1 2 4 5 3
```

此时如果在进行交换 , 因为 $a$ 已经有序 , 交换后 , $a$ 增加的逆序对一定大于 $b$ 的减少逆序对

关于上述结论的证明 : 

> 设排列 $a$ 为 $1,2,3,4,5,\cdots,n$ , 排列 $b$ 是 $n$ 长度的任意排列
> 
> 以 $逆序对等于每个元素后面有几个元素比它小累加求和$ 计算逆序对。
> 
> 现在我们将 $a$ 中下标 $i,j(i<j)$ 进行交换, 
> 
> 可以得出, 此次交换只对 $[i,j]$ 区间元素产生的逆序对贡献有影响
> 
> 对于 $i$ 位置, $j$ 被交换过来, 对于 $a$ , 增加了 $j-i$ 个逆序对, 这是 $i$ 位置最大贡献 , $b$ 的交换一定不会超过这个值
> 
> 对于 $j$ 位置 , 基于我们计算逆序对的方式 , 对逆序对没有影响
> 
> 对于 $k\in(i,j)$ ，由于 $k$ 后面的位置只有 $a_j$ 发生了变化, 只要计算 $a_j$ 对位置 $k$ 的影响, 而 $a$ 交换后一定会增加一个逆序对, $b$ 交换后至多减少一个逆序对。
> 
> 综上所述 , 先把 $a$ 排序, 此时进行任意交换都不会使答案更优

   现在

```cpp
void solve(){
    int n;
    cin>>n;
    vector<int> a(n+5);
    vector<int> b(n+5);
    map<int, int> at; // a 中元素 i 的位置 
    for(int i=1; i<=n; i++){
        cin>>a[i];
        at[a[i]]=i;
    }
    for(int i=1; i<=n; i++) cin>>b[i];
    for(int i=1; i<=n; i++){
        if(a[i]!=i){
            int p=at[i];
            at[i]=i;
            at[a[i]]=p;
            swap(a[p], a[i]);
            swap(b[p], b[i]);
        }
    }
    for(int i=1; i<=n; i++) cout<<a[i]<<" \n"[i==n];
    for(int i=1; i<=n; i++) cout<<b[i]<<" \n"[i==n];
}
```

## C

令 $|({a \oplus x}) - ({b \oplus x})|$ 最小化 , 实际上就是让 $a \oplus x$ 与 $b \oplus x$ 两个数尽量接近

设 $a_i$ 是 $a$ 的二进制中的第 $i$ 低位 $i=0,1,2,...,59$ 

设 $b_i$ 是 $b$ 的二进制中的第 $i$ 低位 $i=0,1,2,...,59$ 

同理设出 $x_i$ 。

本着让两个数尽量接近的目的, 我们尽量让每一位相同

- 如果 $a_i=b_i$ ,  无论 $x_i$ 取何值, $a_i \oplus x_i$ 一定等于 $b_i \oplus x_i$ , 此时 $x_i$ 取 $0$ , 这样可以减少 $r$ 的浪费

- 如果 $a_i\neq b_i$ , 无论 $x_i$ 取何值, $a_i \oplus x_i $ 一定不等于 $b_i \oplus x_i$ ,  因为尽量让两个数接近, 这一位 $x_i$ 取 $0$ , 此时会在 $a \oplus x$ 和 $b \oplus x$ 中产生一个较大的数 , 后面操作让较小的数尽量大就可以了

>  时间复杂度 : $O(T*60)$ 

```cpp
void solve(){
    int a, b, r;
    cin>>a>>b>>r;
    int res=0;
    for(int i=59; i>=0; i--){
        if((a>>i&1) == (b>>i&1)) continue;
        else if((a>>i&1) == 1){
            res+=(1LL<<i);
            for(int j=i-1; j>=0; j--){
                int at=(a>>j&1), bt=(b>>j&1);
                int tmp=(1LL<<j);
                if(at==1 && bt==0){
                    if(r >= tmp){
                        r -= tmp;
                        res -= tmp;
                    }
                    else{
                        res += tmp;
                    }
                }
                else if(at==0 && bt==1) res -= tmp; 
            }
            cout<<res<<'\n';
            return ; 
        }
        else if((b>>i&1) == 1){
            res+=(1LL<<i);
            for(int j=i-1; j>=0; j--){
                int at=(a>>j&1), bt=(b>>j&1);
                int tmp=(1LL<<j);
                if(at==0 && bt==1){
                    if(r >= tmp){
                        r -= tmp;
                        res -= tmp;
                    }
                    else{
                        res += tmp;
                    }
                }
                else if(at==1 && bt==0) res-=tmp;
            }
            cout<<res<<'\n';
            return ;
        }
    }
    cout<<res<<'\n';
}
```

## D

二分答案 `res`, `check(mid)`  函数的写法如下 :

$dp_i$ 表示处理到了 $i$ , 以 $i$ 为分割点的最小花费

根据上一个分割点的位置 $j$ 转移 : 

如果 $j$ 是一个可转移的位置 , 则 $sum[j+1,i-1]$ 这一段区间和不能超过 $mid$ 

双指针维护这个 $j$ 的位置 , 从 $[j,i-1]$ 这个位置都是可转移位置, 随着 $i$ 的增加, $j$ 一定也在增加, 单调队列维护 $[j,i-1]$ 区间的最小值用于 $dp$ 转移

$dp_i=a_i+\min_k (dp_k),k\in[j,i-1]$ 

>  时间复杂度 : $O(\log{10^{14}}*n)$  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[100010], s[100010], q[100010], dp[100010];
bool check(int mid){
    int head=0, tail=-1;
    q[++tail]=0; dp[0]=0; // 初始化 
    for(int i=1, j=0; i<=n+1; i++){
        if(a[i]>mid) return false; // 花费一定超过 mid 
        while(s[i-1]-s[j]>mid) j++; // [j, i-1] 可转移 
        while(q[head]<j) head ++; // 维护单调队列 
        dp[i]=dp[q[head]]+a[i];        
        while(head<=tail && dp[i]<=dp[q[tail]]) tail --;
        q[++ tail]=i; // 将 i 加入 
    }
    return (dp[n+1]<=mid);
}

void solve(){
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
        dp[i]=0;
    }
    a[n+1]=0; s[n+1]=s[n]; dp[n+1]=0;
    int l=1, r=1e14;
    while(l<r){
        int mid=l+r>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l<<'\n';
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

## E
