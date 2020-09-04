 /**
  * Author  : Kamal Shafi
  * Problem : Negara INF dan Kota Baru
  */

// problem source: https://csacademy.com/contest/ieeextreme-practice/task/bearcity-renting

#pragma gcc optimize ("O2")
#pragma gcc optimize ("unroll-loops")

#include <bits/stdc++.h>


#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10, M = 1e4 + 10;
const int INF = 1e9;

int n, m;
vector<pair<pii, int>> edges[M];

int par[N], sz[N];

void init(){
    for (int i=1;i<=n;i++){
        par[i] = i;
        sz[i] = 1;
    }
}
int find(int a){
    return (par[a] == a ? a : par[a] = find(par[a]));
}
void make(int a, int b){
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
}

map<int, int> getid;

vector<int> adj[N]; 
int comp[N], csz[N];
int compNum;
int low[N], tin[N], timer;
bool onStack[N];
stack<int> st;

unordered_map<int, int> cnt[N];

vector<int> ans;
vector<int> nada;

void dfs_scc(int node, int p){
    low[node] = tin[node] = ++timer;
    st.push(node);
    onStack[node] = 1;
    for (auto x : adj[node]){
        if (x == p && cnt[node][x] == 1) continue;  // add parent as parameter and add this line for directed graph
        if (tin[x] == 0){
            dfs_scc(x, node);
            low[node] = min(low[node], low[x]);
        } else if (onStack[x]){
            low[node] = min(low[node], tin[x]);
        }
    }
    if (low[node] == tin[node]){
        ++compNum;
        while (1){
            auto temp = st.top();
            st.pop();
            comp[temp] = compNum;
            csz[temp]++;
            onStack[temp] = 0;
            if (temp == node || st.empty()) break;
        }
    }
}

void tarjan(){
    compNum = timer = 0;
    for (auto x : nada){
        low[x] = 0;
        tin[x] = 0;
        onStack[x] = 0;
        csz[x] = 0;
        comp[x] = 0;
    }
    while (!st.empty()) st.pop();

    for (auto i : nada){
        if (tin[i] == 0) dfs_scc(i, adj[i][0]);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    {
        int tempid = 0;
        vector<pair<int, pii>> temp;
        for (int i=1;i<=m;i++){
            int a, b;
            int w;
            cin >> a >> b >> w;
            getid[w] = 1;
            temp.pb(mp(w, mp(a, b)));
        }
        for (auto& x : getid){
            x.se = ++tempid;
        }
        for (int i=0;i<m;i++){
            int a, b;
            int w;
            a = temp[i].se.fi, b = temp[i].se.se;
            w = getid[temp[i].fi];
            edges[w].pb(mp(mp(a, b), i + 1));
        }
    }
    init();
    for (int i=1;i<M;i++){
        for (auto x : edges[i]){
            int a = find(x.fi.fi);
            int b = find(x.fi.se);
            if (a == b) continue;
            cnt[a][b]++;
            cnt[b][a]++;
            nada.pb(a);
            nada.pb(b);
            adj[a].pb(b);
            adj[b].pb(a);
        }
        tarjan();
        for (auto x : nada){
            adj[x].clear();
            cnt[x].clear();
        }
        nada.clear();
        for (auto x : edges[i]){
            int a = x.fi.fi, b = x.fi.se;
            if (comp[find(a)] != comp[find(b)]) ans.pb(x.se);
        }

        for (auto x : edges[i]){
            make(x.fi.fi, x.fi.se);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << el;
    for (auto x : ans){
        cout << x << el;
    }

    return 0;
}