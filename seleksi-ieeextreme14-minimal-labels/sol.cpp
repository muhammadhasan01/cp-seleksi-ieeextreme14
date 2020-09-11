 /**
  * Author  : Firastic
  * Problem : Best Label
  * Problem Source: https://codeforces.com/problemset/problem/825/E
  */

#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n,m,a,b,ans[MAXN+5], out[MAXN+5];
vector<int> v[MAXN+5];
stack<int> st;
bool visited[MAXN+5];
set<int, greater<int> > s;

void process(int now){
    if(visited[now]){
        s.erase(now);
        return;
    }
    visited[now] = true;
    for(int i = 0; i < v[now].size(); i++){
        out[v[now][i]]--;
        if(out[v[now][i]] == 0){
            s.insert(v[now][i]);
        }
    }
    st.push(now);
    s.erase(now);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d", &a, &b);
        a--;
        b--;
        v[b].push_back(a);
        out[a]++;
    }
    for(int i = n-1; i >= 0; i--){
        if(out[i] == 0){
            s.insert(i);
        }
    }
    while(s.size()){
        process(*s.begin());
    }
    int cur = 1;
    while(!st.empty()){
        ans[st.top()] = cur;
        cur++;
        st.pop();
    }
    for(int i = 0; i < n; i++){
        printf("%d", ans[i]);
        if(i==n-1)printf("\n");
        else printf(" ");
    }
}