# [AtCoder Beginner Contest 337【题解A-E】 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/678956773)

# E

- 做法一 : 二进制分组

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N = 105;
int res=0;
int main(){
    int n, m=0;
    cin>>n;
    m=log2(n-1)+1;
    cout<<m<<'\n';
    for(int i=0; i<m; i++){
        int a[105]={0};
        int cnt=0;
        for(int j=0; j<n; j++){
            if(j>>i&1){
                a[++ cnt]=j+1;
            }
        }
        cout<<cnt<<' ';
        for(int j=1; j<=cnt; j++) cout<<a[j]<<' ';
        cout<<'\n';
    }    
    string rsp;
    cin>>rsp;
    for(int i=0; i<m; i++){
        if(rsp[i]=='1'){
            res|=(1<<i);
        }
    }
    cout<<res+1;

    return 0;
} 
// 把所有二进制最低位为 1 的给 1 喝, 根据他的反应判定饮料最低位是不是 1
// 把所有二进制第二低位为 1 的给 2 喝, 根据他的反应判定饮料最低位是不是 2  
```

- 做法二 : 折半划分 ， 依数找寻

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, m;
string str;
vector<int> a[105];
void write(int l, int r, int u){
    for(int i=l; i<=r; i++)
        a[u].push_back(i);
}

void alloc(int l, int r, int u){
    // u 是第几层, 同时也是第几个人
    if(u>m) return;
    int mid=l+(r-l+1)/2-1;
    write(l, mid, u);
    alloc(l, mid, u+1); alloc(mid+1, r, u+1);
}

int main(){
    cin>>n;
    while((1<<m)<n) m++;
    alloc(1, n, 1);
    cout<<m<<'\n';
    for(int i=1; i<=m; i++){
        cout<<a[i].size()<<' ';
        for(int j : a[i]) cout<<j<<' ';
        cout<<'\n';
    }
    fflush(stdout);
    cin>>str;
    int l=1, r=n;
    for(int i=0; i<m; i++){
        int mid=l+(r-l+1)/2-1;
        if(str[i]=='1'){
            r=mid;
        }
        else{
            l=mid+1;
        }
    }
    cout<<l;
    return 0;
} 
```
