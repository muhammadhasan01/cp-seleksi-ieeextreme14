 /**
  * Author  : Morgen Sudyanto
  * Problem : Segitiga Kayu
  */

#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define INF 1234567890
#define pii pair<int,int>
#define LL long long
using namespace std;

int main () {
    //clock_t start = clock();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int ans = 0;
    
    LL a[n+5];
    for (int i=1;i<=n;i++) cin >> a[i];

    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            for (int k=j+1;k<=n;k++) {
                if (a[i]+a[j] > a[k] && a[i]+a[k] > a[j] && a[j]+a[k] > a[i]) ans++;
            }
        }
    }

    cout << ans << endl;
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}