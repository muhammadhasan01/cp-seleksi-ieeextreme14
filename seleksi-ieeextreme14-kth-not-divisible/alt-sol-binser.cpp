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
    int tc;
    cin >> tc;
    while (tc--) {
        LL n, k;
        cin >> n >> k;
        LL l = 0, h = 2000000000, ans = 0;
        while (l <= h) {
            LL m = (l + h) / 2;
            if ((m - (m / n)) == k) {
                if (m % n > 0) {
                    ans = m;
                    break;
                } else {
                    h = m-1;
                }
            } else if ((m - (m / n)) > k) {
                h = m-1;
            } else {
                l = m+1;
            }
        }
        cout << ans << endl;
    }
    //cerr << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}