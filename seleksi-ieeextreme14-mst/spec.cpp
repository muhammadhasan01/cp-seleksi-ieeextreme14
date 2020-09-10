#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMax = 1e5;
const int MMax = 1e5;
const int WMax = 1e9;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    vector<int> U, V, W;
    vector<int> res;
    int ans_cnt;

    void InputFormat() {
        LINE(N, M);
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat() {
        LINE(ans_cnt);
        LINES(res) % SIZE(ans_cnt);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
        CONS(1 <= M && M <= MMax);
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(W, 1, WMax));
        CONS(noDoubleEdge(U, V));
        CONS(noSelfLoop(U, V));
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

    bool noDoubleEdge(const vector<int> &u, const vector<int>& v) {
  		int len = u.size();
  		set<int> st[NMax + 5];
  		for (int i = 0; i < len; i++) {
  			if (st[u[i]].find(v[i]) != st[u[i]].end()) return false;
  			st[u[i]].insert(v[i]);
  		}
  		return true;
    }

    bool noSelfLoop(const vector<int>& u, const vector<int>& v) {
    	int len = u.size();
    	for (int i = 0; i < len; i++) {
    		if (u[i] == v[i]) return false;
    	}
    	return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
    	Input({
            "3 3",
            "1 2 70",
            "1 3 70",
            "2 3 69"
    	});
    	Output({
    		"1",
            "3"
    	});
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        W.clear();
        res.clear();
    }

    void TestCases() {
    	CASE(N = 2, M = 2, randomConnectedGraph(N, M, U, V, W));
    	CASE(N = 5, M = 4, randomConnectedGraph(N, M, U, V, W));
    	CASE(N = 10, M = 9, randomConnectedGraph(N, M, U, V, W));
    	for (int i = 0; i < 2; i++) {
    		CASE(N = rnd.nextInt(6, NMax / 2), M = rnd.nextInt(N - 1, MMax), randomConnectedGraph(N, M, U, V, W));
    	}
    	for (int i = 0; i < 5; i++) {
    		CASE(N = rnd.nextInt(NMax / 2 + 1, NMax), M = rnd.nextInt(N - 1, MMax), randomConnectedGraph(N, M, U, V, W));
            CASE(N = rnd.nextInt(NMax / 2 + 1, NMax), M = rnd.nextInt(N - 1, MMax), randomConnectedGraph(N, M, U, V, W, rnd.nextInt(1000, 10000)));
    	}
        for (int i = 0; i < 5; i++) {
    		CASE(N = NMax, M = MMax, randomConnectedGraph(N, M, U, V, W));
    		CASE(N = NMax, M = MMax, randomConnectedGraph(N, M, U, V, W, rnd.nextInt(1000, 10000)));
    	}
        for (int i = 0; i < 4; i++){
    	    CASE(N = 400, M = maxx(N), completeGraph(N, M, U, V, W));
    	    CASE(N = 400, M = maxx(N), completeGraph(N, M, U, V, W, rnd.nextInt(1000, 10000)));
        }
    }

private:

    void randomWeight(int m, vector<int>& w, int bates = WMax){
        for (int i=0;i<m;i++){
            w.push_back(rnd.nextInt(1, bates));
        }
    }

    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 1; i <= n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < (int) u.size(); i++) {
            u[i] = permutation[u[i] - 1];
            v[i] = permutation[v[i] - 1];
        }
    }

    void randomGraph(int n, int m, vector<int>& u, vector<int>& v, vector<int>& w) {
    	vector<int> permutation;
    	for (int i = 0; i < n; i++) {
    		permutation.push_back(i + 1);
    	}
    	rnd.shuffle(permutation.begin(), permutation.end());
    	vector<int> idx;
    	for (int i = 0; i < n - 1; i++) {
    		idx.push_back(i);
    	}
    	rnd.shuffle(idx.begin(), idx.end());
    	for (int i = 0; i < m; i++) {
    		u.push_back(permutation[idx[i]]);
    		v.push_back(permutation[idx[i] + 1]);
    	}
        randomWeight(m, w);
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 1; i < n; i++) {
		    u.push_back(i + 1);
		    v.push_back(rnd.nextInt(1, i));
		}
		renumber(n, u, v);
	}

    void randomConnectedGraph(int n, int m, vector<int> &u, vector<int> &v, vector<int>& w, int bates = WMax) {
    	assert(m >= n - 1);
    	randomTree(n, u, v);
		map<pair<int,int>, int> udah;
		for (int i = 0; i < (int)u.size(); ++i){
			udah[{u[i], v[i]}]++;
		}
    	while (u.size() < m) {
    		int newU = rnd.nextInt(1, n);
    		int newV = rnd.nextInt(1, n);
			while (udah.find({newU, newV}) != udah.end() || (newU == newV)){
				newU = rnd.nextInt(1, n);
				newV = rnd.nextInt(1, n);
			}
			udah[{newU, newV}]++;
			u.push_back(newU);
			v.push_back(newV);
    	}
        randomWeight(m, w, bates);
    }

    void completeGraph(int n, int m, vector<int> &u, vector<int> &v, vector<int>& w, int bates = WMax) {
    	assert(m == maxx(n));
    	for (int i = 0; i < n; i++) {
    		for (int j = i+1; j < n; j++) {
    			u.push_back(i + 1);
    			v.push_back(j + 1);

				u.push_back(j+1);
				v.push_back(i+1);
    		}
    	}
        randomWeight(m, w, bates);
    }

	int maxx(int n){
		return (n*(n-1));
	}
};
