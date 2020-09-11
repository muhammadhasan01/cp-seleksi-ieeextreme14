#include <tcframe/spec.hpp>
using namespace tcframe;
#define MAXN 100000
#define MAXM 100000

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    vector<int> A, B;
    vector<int> ans;

    void InputFormat() {
        LINE(N, M);
        LINES(A, B) % SIZE(M);
    }

    void OutputFormat() {
        LINE(ans % SIZE(N));
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= M && M <= MAXM);
        CONS(noLoop(A, B, N, M));
        CONS(noMultipleEdges(A, B, N, M));
        CONS(A.size() == M and B.size() == M);
        CONS(eachElementBetween(A, 1, N));
        CONS(eachElementBetween(B, 1, N));
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

    bool noMultipleEdges(vector<int> A, vector<int> B, int N, int M){
        vector<vector<int> > v = edgesTo2DVector(A, B, N);
        for(int i = 0; i < v.size(); i++){
            sort(v[i].begin(), v[i].end());
            for(int j = 0; j < (int)v[i].size()-1; j++){
                if(v[i][j] == v[i][j+1]){
                    return false;
                }
            }
        }
        return true;
    }

    bool noLoop(const vector<int> &A, const vector<int> &B, int N, int M){
        vector<int> visited;
        vector<vector<int> > v = edgesTo2DVector(A, B, N);
        visited.resize(N);

        bool res = false;
        for(int i = 0; i < v.size(); i++){
            if(!visited[i]){
                res |= isCycle(v, visited, i);
            }
        }
        return !res;
    }

    bool isCycle(const vector<vector<int> > &v, vector<int> &visited, int now){
        if(visited[now] == 1){
            return true;
        } else if(visited[now] == 2){
            return false;
        }

        visited[now] = 1;

        bool res = false;
        for(int i = 0; i < v[now].size(); i++){
            res |= isCycle(v, visited, v[now][i]);
        }
        visited[now] = 2;

        return res;
    }

    vector<vector<int> > edgesTo2DVector(const vector<int> &A, const vector<int> &B, int N){
        vector<vector<int> > v;
        v.resize(N);
        for(int i = 0; i < A.size(); i++){
            v[A[i] - 1].push_back(B[i] - 1);
        }
        return v;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 4",
            "3 1",
            "2 1",
            "2 3",
            "4 5"
        });
        Output({
            "3 1 2 4 5"
        });
    }

    void BeforeTestCase() {
        A.clear();
        B.clear();
    }    

    void TestCases() {
        for(int i = 0; i < 2; i++){
            CASE(N = MAXN, M = MAXN, randomTree(N, M, A, B));
        }

        for(int i = 0; i < 2; i++){
            CASE(N = MAXN/2, M = MAXN, randomTree(N, M, A, B));
        }
        for(int i = 0; i < 5; i++){
            CASE(N = rnd.nextInt(1, MAXN/100), M = rnd.nextInt(1, min((long long)MAXN, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
            CASE(N = rnd.nextInt(1, MAXN/100), M = rnd.nextInt(N, min((long long)MAXM, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
        }
        for(int i = 0; i < 5; i++){
            CASE(N = rnd.nextInt(MAXN/100, MAXN/10), M = rnd.nextInt(1, min((long long)MAXN, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
            CASE(N = rnd.nextInt(MAXN/100, MAXN/10), M = rnd.nextInt(N, min((long long)MAXM, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
        }
        for(int i = 0; i < 3; i++){
            CASE(N = rnd.nextInt(MAXN/10, MAXN), M = rnd.nextInt(1, min((long long)MAXN, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
            CASE(N = rnd.nextInt(MAXN/10, MAXN), M = rnd.nextInt(N, min((long long)MAXM, (long long)N*(N-1)/2)), randomTree(N, M, A, B));
        }
    }

private:
    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 0; i < n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < u.size(); i++) {
            u[i] = permutation[u[i]];
            v[i] = permutation[v[i]];
        }
    }

    void randomTree(int n, int m, vector<int>& u, vector<int>& v) {
        map<int, bool> cek[n+5];
        while(m){
            for (int i = 1; i < n && m; i++) {
                int x = i;
                int y = rnd.nextInt(0, i-1);
                if(cek[x][y])continue;

                u.push_back(x);
                v.push_back(y);
                cek[x][y] = true;
                m--;
            }
        }
        renumber(n, u, v);
        for(int i = 0; i < u.size(); i++){
            u[i]++;
            v[i]++;
        }
    }
};