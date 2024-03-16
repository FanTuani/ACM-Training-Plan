# P1156

## 题目描述

> 给你一个坑的高度 $D$ 和物品数量 $n$ 
> 
> 每个物品有三个属性 : $t_i,f_i,h_i$ ，分别代表垃圾扔下的时间，吃垃圾增加的生命时间和高度
> 
> 询问能否爬出陷阱，可以的话输出最早时刻；否则输出最高到达的高度

## 解法

令 $dp_{i,j}$ 表示当前处理完了第 $i$ 个物品，当前体力值恰好为 $j$ 时，堆叠的最大高度

状态转移 : 当前物品选择堆叠 / 食用

初始化 : 不可达状态初始化为 $-\infty$

将所有物品按照出现的时间排序，每次如果不会饿死或同一时间有其他物品或恰好逃出，更新堆叠的转移；中途不会饿死，更新食用的转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

// dp[i][j] 表示当前是處理完第 i 个物品, 当前体力恰好为 j 时, 堆叠的最大高度
// 划分依据 : 当前物品堆叠 / 食用
// dp[i][j] = dp[i - 1][j + t[i] - t[i - 1]] + h[i], dp[i - 1][j - f[i] + t[i] - t[i - 1]];
int D, n;
int t[110], f[110], h[110];
int dp[31000], g[31000];
struct node{
    int a, b, c, s;
    bool operator < (const node &t) const{
        return a < t.a;
    }
} Data[110];
void solve(){
    int mx = 10;
    cin >> D >> n;
    for(int i = 1; i <= n; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        Data[i] = {a, b, c};
    }
    sort(Data + 1, Data + n + 1);
    for(int i = 1; i <= n; i ++){
        t[i] = Data[i].a, f[i] = Data[i].b, h[i] = Data[i].c;
    }

    for(int j = 0; j < 31000; j ++){
        dp[j] = -2e9;
    }
    dp[10] = 0;

    for(int i = 1; i <= n; i ++){
        memcpy(g, dp, sizeof dp); 
        for(int j = 0; j < 31000; j ++){
            dp[j] = -2e9;
        }
        for(int j = 0; j <= 30000; j ++){
            int tmp = t[i] - t[i - 1];
            if(j){
                if(g[j + tmp] != -2e9){
                    dp[j] = max(dp[j], g[j + tmp] + h[i]);
                }
            }
            else{
                if(g[j + tmp] + h[i] >= D || (i + 1 <= n && t[i + 1] == t[i])){
                    if(g[j + tmp] != -2e9){
                        dp[j] = max(dp[j], g[j + tmp] + h[i]);
                    }
                }
            }

            if(j + tmp - f[i] >= 0 && g[j + tmp - f[i]] != 2e9){ // 可轉移狀態
                if(j + tmp - f[i] >= tmp){ // 中途不會餓死
                    dp[j] = max(dp[j], g[j + tmp - f[i]]);
                }
            }

            if(dp[j] >= D){
                cout << t[i] << '\n';
                return ;
            }
            if(dp[j] != -2e9) mx = max(mx, t[i] + j);
        }
    }
    cout << mx << '\n';
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
