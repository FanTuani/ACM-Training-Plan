# Codeforces Round 929 (Div. 3)

## F

### sol1

我们认为障碍物是静止的，机器人每秒向下平移一格，那么机器人的三种操作如下 :

- 原地不动

- 向下平移两个

- 向右下移动

用 `bfs` 求得到达最右边一列的最短距离，更新答案 (注意终点也在动)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m;
int rk[1100][1100], d[1100][1100];
int dx[2]={1, 2};
int dy[2]={1, 0};
int get(int x){
    return (x%n+n)%n;
}
void bfs(){
    queue<pair<int, int> > q;
    q.push({0, 0});
    d[0][0]=0;
    while(q.size()){
        auto t=q.front(); q.pop();
        for(int i=0; i<2; i++){
            int a=get(t.first+dx[i]), b=t.second+dy[i];
            if(i){
                if(b>=0&&b<m&&d[a][b]==-1&&rk[a][b]==0&&rk[get(a-1)][b]==0){
                    d[a][b]=d[t.first][t.second]+1;
                    q.push({a, b});
                }
            }
            else{
                if(b>=0&&b<m&&d[a][b]==-1&&rk[a][b]==0){  
                    d[a][b]=d[t.first][t.second]+1;
                    q.push({a, b});
                }
            }
        }
    }
}
void solve(){
    cin>>n>>m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>rk[i][j];
            d[i][j]=-1;
        }
    }
    bfs();
    int res=2e9;
    for(int i=0; i<n; i++){
        if(d[i][m-1]!=-1){
            int tmp=d[i][m-1];
            int ed=get(n-1+tmp);
            res=min(res, tmp+min(abs(ed-i), n-abs(ed-i)));
        }
    }
    cout<<(res==2e9?-1:res)<<'\n';
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
        }
    }
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

### sol2

基于 `sol1` , 向上移动是没有意义的，我们可以 $O(1)$ 求出某个点有没有障碍物，如此一来用 `bfs` 求得到达最右边一列的距离，然后更新答案

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dx[3]={0, 1, -1};
int dy[3]={1, 0, 0};
// 0 时间, (x,y) --> t 时间, (x-t, y)
// 0 时间, (x+t,y) --> t 时间, (x, y)
set<pair<int,int> > rock;  
int n, m;
int d[1100][1100];
// 会到 {x, y} 处, 没到之前时间是 t 
// sp=0, 向右移动 ; sp=1, 向下移动 ; sp=2, 向上移动
int get(int x){
    return (x%n+n)%n;
} 
bool check(int x, int y, int t, int sp){
    if(sp==0){
        if(rock.count({get(x+t+1),y})) return false;
        return true;        
    }    
    else if(sp==1){
        if(rock.count({get(x+t),y}) || rock.count({get(x+t+1),y})) return false; 
        return true;
    }
    else{
        return true; 
    } 
}
void bfs(int x, int y){
    queue<pair<int, int> > q;
    q.push({x, y}); 
    d[x][y]=0;
    while(q.size()){
        auto t=q.front(); q.pop();
        for(int i=0; i<3; i++){
            if(i==2) continue;
            int a=get(t.first+dx[i]), b=t.second+dy[i];
        //    cout<<"coordinate: "<<a<<' '<<b<<'\n'; 
            if(b>=0&&b<m&&d[a][b]==-1&&check(a,b,d[t.first][t.second],i)==true){
                d[a][b]=d[t.first][t.second]+1;
                q.push({a, b});
            }
        }
    }
}
void solve(){
    rock.clear();
    cin>>n>>m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            d[i][j]=-1;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int x;
            cin>>x;
            if(x) rock.insert({i, j});
        }
    }
    bfs(0, 0);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
//            cout<<d[i][j]<<" \n"[j==m-1];
        }
    }
    int res=2e9;
    for(int i=0; i<n; i++){
        res=min(res, d[i][m-1]+min(n-1-i, i+1));
    }
    cout<<res<<'\n';
//    if(d[n-1][m-1]!=-1) cout<<d[n-1][m-1]<<'\n';
//    else cout<<"-1\n";
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
