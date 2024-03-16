# Sol

相当于对完美二叉树进行填充，第一次给出一半的结点, 把他们全部填充到偶数位置, $a_{i,j}$ 维护第 $i$ 层的输入并在输入结束后更新为子树的最大值，左子树根节点是 $a_{i-1,j<<1}$ ，右子树根节点是 $a_{i-1,j<<1|1}$ , $ne_{i,j}$ 维护击败 $\{i,j\}$ 之后应该填充到答案的位置，如果击败左子树，填充到对应位置，下次击败 $a_{i,j}$ 之后填充到右子树，保证均衡。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k, a[20][1 << 20], ne[20][1 << 20], res[1 << 20];
int main(){
	cin >> k;
	for(int i = 1; i <= k; i ++){
		int s = (1 << (k - i));
		for(int j = 0; j < s; j ++){
			cin >> a[i][j];
			if(i == 1){
				res[j << 1] = a[i][j];
				ne[i][j] = j << 1 | 1;
				continue;
			}
			int mx = max({a[i][j], a[i - 1][j << 1], a[i - 1][j << 1 | 1]});
			if(a[i][j] >= a[i - 1][j << 1]){
				res[ne[i - 1][j << 1]] = a[i][j];
				ne[i][j] = ne[i - 1][j << 1 | 1];
			}
			else if(a[i][j] >= a[i - 1][j << 1 | 1]){
				res[ne[i - 1][j << 1 | 1]] = a[i][j];
				ne[i][j] = ne[i - 1][j << 1];
			}
			else{
				cout << "No Solution";
				return 0;
			}
			a[i][j] = mx; 
		}
	}
	int w;
	cin >> w;
	if(w >= a[k][0]){
		res[ne[k][0]] = w;
		for(int i = 0; i < (1 << k); i ++) cout << res[i] << ' ';
	}
	else{
		cout << "No Solution";
	}
	return 0;
} 
```


