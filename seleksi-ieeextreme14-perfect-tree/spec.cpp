#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMax = 1e5;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> VAL, U, V;
    vector<int> res;

    void InputFormat() {
        LINE(N);
        LINE(VAL % SIZE(N));
        LINES(U, V) % SIZE(N - 1);
    }

    void OutputFormat() {
        LINES(res) % SIZE(N);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMax);
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(VAL, 1, NMax));
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
            "3",
            "3 3 2",
            "1 2",
            "1 3"
    	});
    	Output({
            "1",
            "0",
            "0"
    	});
    }
    void SampleTestCase2() {
    	Input({
            "3",
            "3 1 50",
            "1 2",
            "1 3"
    	});
    	Output({
            "2",
            "0",
            "0"
    	});
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        VAL.clear();
        res.clear();
    }

    void TestCases() {
        for (int i = 0; i < 5; i++){
            CASE(N = NMax, genValue(N, VAL, N), linearTree(N, U, V));
        }
    	CASE(N = 10, genValue(N, VAL, N), randomTree(N, U, V));
        CASE(N = 15, genValue(N, VAL, N), randomTree(N, U, V));
        CASE(N = 13, genValue(N, VAL, N), randomTree(N, U, V));
        for (int i = 0; i < 2; i++){
            CASE(N = rnd.nextInt(2, NMax), genValue(N, VAL), randomTree(N, U, V));
        }
        for (int i = 0; i < 2; i++){
            CASE(N = rnd.nextInt(NMax / 2, NMax), genValue(N, VAL), randomTree(N, U, V));
            CASE(N = rnd.nextInt(NMax / 2, NMax), genValue(N, VAL, rnd.nextInt(300, N)), randomTree(N, U, V));
        }
        for (int i = 0; i < 3; i++){
            CASE(N = NMax, genValue(N, VAL), randomTree(N, U, V));
            CASE(N = NMax, genValue(N, VAL, rnd.nextInt(300, N)), randomTree(N, U, V));
        }
    }

private:
    void genValue(int n, vector<int>& val, int bates = -1){
        if (bates <= 0) bates = NMax;
        for (int i=0;i<n;i++){
            val.push_back(rnd.nextInt(1, bates));
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

    void randomTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 1; i < n; i++) {
		    u.push_back(i + 1);
		    v.push_back(rnd.nextInt(1, i));
		}
		renumber(n, u, v);
	}
    void linearTree(int n, vector<int>& u, vector<int>& v) {
		for (int i = 2; i <= n; i++) {
		    u.push_back(i);
		    v.push_back(i - 1);
		}
		renumber(n, u, v);
	}
};
