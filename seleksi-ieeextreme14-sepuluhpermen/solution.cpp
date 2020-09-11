 /**
  * Author  : Irfan Sofyana Putra
  * Problem : Sepuluh Permen
  */
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

LL permen, ans;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> permen;

    while (permen > 0) {
        ans += permen;
        permen /= 10;
    }

    cout << ans << '\n';
    return 0;
}