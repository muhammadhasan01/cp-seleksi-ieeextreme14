#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
 
typedef long long ll;
 
ll n,i,j;
ll arr[100005];
ll dp[100005][2];
 
ll cari(ll idx,ll sum){
	if (idx == n && sum == 0) return 0;
	if (idx == n) return -10000000000000000;
	if (dp[idx][sum] != -1) return dp[idx][sum];
	//ambil :
	ll ambil = 0;
	if (abs(arr[idx]) % 2 == 0) 
		ambil = cari(idx + 1, sum) + arr[idx];
	else ambil = cari(idx + 1, 1-sum) + arr[idx];
 
	return dp[idx][sum] = max(ambil, cari(idx + 1, sum));
}
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (i = 0 ; i < n ; i++) 
		cin >> arr[i];
	memset(dp, -1, sizeof dp);
	cout << cari(0,1) << '\n';
	return 0;	
}