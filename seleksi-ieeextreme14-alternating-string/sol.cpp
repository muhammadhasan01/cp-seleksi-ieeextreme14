 /**
  * Author  : Firastic
  * Problem : Alternating Pot
  * Problem Source: https://codeforces.com/gym/100712/
  */

#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define INF 1000000

int n,k,t;
string s;
int dp[MAXN+5][MAXN+5][2];
bool cek[MAXN+5][MAXN+5][2];

int rekur(int now, int selected, bool isAlternate){
    if(now == n){
        if(isAlternate and selected > 1) return INF;
        else return 0;
    }

    int &ret = dp[now][selected][isAlternate];
    if (cek[now][selected][isAlternate]){
        return ret;
    }
    cek[now][selected][isAlternate] = true;

    if(selected == k){
        if(isAlternate and selected > 1){
            return INF;
        } else {
            ret = rekur(now, 0, 1) + 1;
        }
    } else {
        if(selected > 0 and s[now] == s[now-1]) {
            ret = rekur(now+1, selected+1, 0);
        } else {
            ret = rekur(now+1, selected+1, isAlternate);
        }
        if(!isAlternate or selected == 1){
            ret = min(ret, rekur(now, 0, 1) + 1);
        }
        
    }
    return ret;
}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &k);
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= k; j++){
                dp[i][j][0] = dp[i][j][1] = INF;
                cek[i][j][0] = cek[i][j][1] = 0;
            }
        }
        cin >> s;
        printf("%d\n", rekur(0, 0, 1));
    }
}