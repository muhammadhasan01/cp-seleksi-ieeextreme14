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

const int N = 1e5 + 10;
const int INF = 1e9;
struct Mst{
    int n;
    int par[N], sz[N];

    Mst(){
        for (int i=1;i<N;i++){
            par[i] = i;
            sz[i] = 1;
        }
        n = N - 1;
    }
    Mst(int n) : n(n) {
        for (int i=1;i<=n;i++){
            par[i] = i;
            sz[i] = 1;
        }
    }
    int find(int a){
        return (par[a] == a ? a : par[a] = find(par[a]));
    }
    bool make(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b) return 0;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        return 1;
    }
    vector<pair<int, pii>> find_mst(vector<vector<pii>> const& adj){
        vector<pair<int, pii>> edges;
        for (int i=1;i<=n;i++){
            for (auto x : adj[i]){
                if (x.fi > i) edges.pb(mp(x.se, mp(i, x.fi)));
            }
        }
        vector<pair<int, pii>> ret;
        sort(edges.begin(), edges.end());
        for (auto edge : edges){
            auto x = edge.se;
            if (make(x.fi, x.se)){
                ret.pb(edge);
            }
        }
        return ret; 
    }
};

int n, m;
vector<vector<pii>> radj, adj; // real adj, (mst) adj
vector<pair<int, pii>> edges;

int head[N], heavy[N], pos[N], par[N];
int dep[N], timer;

int t[4 * N], lazy[4 * N];
int lasthead[N];

int dfs_heavy(int node, int p){
    if (node != p) dep[node] = dep[p] + 1;
    par[node] = p;

    int ret = 1, mx = 0;
    for (auto x : adj[node]){
        if (x.fi == p) continue;
        int temp = dfs_heavy(x.fi, node);
        ret += temp;
        if (temp > mx){
            heavy[node] = x.fi;
        }
    }
    return ret;
}
void decompose(int node, int h){
    head[node] = h;
    pos[node] = ++timer;
    if (heavy[node]){
        decompose(heavy[node], h);
    }
    for (auto x : adj[node]){
        if (x.fi == par[node] || x.fi == heavy[node]) continue;
        decompose(x.fi, x.fi);
    }
}
void push(int v){
    t[v * 2] = min(t[v * 2], lazy[v]);
    lazy[v * 2] = min(lazy[v * 2], lazy[v]);
    t[v * 2 + 1] = min(t[v * 2 + 1], lazy[v]);
    lazy[v * 2 + 1] = min(lazy[v * 2 + 1], lazy[v]);
}
void update(int v, int tl, int tr, int l, int r, int val){
    if (l > r || r < tl || tr < l) return;
    if (l <= tl && tr <= r){
        t[v] = min(t[v], val);
        lazy[v] = min(lazy[v], val);
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, r, val);
    update(v * 2 + 1, tm + 1, tr, l, r, val);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}
int ask(int v, int tl, int tr, int l, int r){
    if (l > r || r < tl || tr < l) return INF;
    if (l <= tl && tr <= r) return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return min(ask(v * 2, tl, tm, l, r), ask(v * 2 + 1, tm + 1, tr, l, r));
}
int query(int a, int b){
    int ret = INF;
    for (; head[a] != head[b]; b = par[head[b]]){
        if (dep[head[a]] > dep[head[b]]) swap(a, b);
        ret = min(ret, ask(1, 1, n, pos[head[b]], pos[b]));
    }
    if (pos[a] == pos[b]) return ret;
    if (dep[a] > dep[b]) swap(a, b);
    ret = min(ret, ask(1, 1, n, pos[a] + 1, pos[b]));
    return ret;
}
void upd(int a, int b, int val){
    for (; head[a] != head[b]; b = par[head[b]]){
        if (dep[head[a]] > dep[head[b]]) swap(a, b);
        if (dep[b] > lasthead[head[b]]){
            update(1, 1, n, pos[head[b]], pos[b], val);
            lasthead[b] = dep[b];
        }
    }
    if (pos[a] == pos[b]) return;
    if (dep[a] > dep[b]) swap(a, b);
    update(1, 1, n, pos[a] + 1, pos[b], val);
}

void init(){
    dfs_heavy(1, 1);
    decompose(1, 1);
    fill(t, t + 4 * N, INF);
    fill(lazy, lazy + 4 * N, INF);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    radj.resize(n + 2);
    adj.resize(n + 2);
    for (int i=1;i<=m;i++){
        int a, b;
        int w;
        cin >> a >> b >> w;
        radj[a].pb(mp(b, w));
        radj[b].pb(mp(a, w));
        edges.pb(mp(w, mp(a, b)));
    }
    {
        Mst mst(n);
        auto temp = mst.find_mst(radj);
        for (auto x : temp){
            int a = x.se.fi, b = x.se.se;
            int w = x.fi;
            adj[a].pb(mp(b, w));
            adj[b].pb(mp(a, w));
        }
    }
    init();
    {   
        vector<pair<int, pii>> temp;
        for (auto x : edges){
            int a = x.se.fi, b = x.se.se;
            if (dep[a] > dep[b]) swap(a, b);
            if (dep[a] + 1 == dep[b] && par[b] == a) continue;
            temp.pb(x);
        }
        sort(temp.begin(), temp.end());
        for (auto x : temp){
            int a = x.se.fi, b = x.se.se;
            int w = x.fi;
            if (dep[a] > dep[b]) swap(a, b);
            if (dep[a] + 1 == dep[b] && par[b] == a) continue;
            upd(a, b, w);
        }
    }
    vector<int> ans;
    for (int i=0;i<m;i++){
        auto x = edges[i];
        int a = x.se.fi, b = x.se.se;
        int w = x.fi;
        if (dep[a] > dep[b]) swap(a, b);
        if (dep[a] + 1 != dep[b] || par[b] != a) continue;
        int temp = ask(1, 1, n, pos[b], pos[b]);
        if (temp > w) ans.pb(i + 1);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << el;
    for (auto x : ans){
        cout << x << el;
    }

    return 0;
}