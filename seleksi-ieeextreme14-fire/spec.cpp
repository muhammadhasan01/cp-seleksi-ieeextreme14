#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMAX = 100;
const int WMAX = 20;
const int HMAX = 2000;
const int VMAX = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> W, H, V;
    int res;
    void InputFormat() {
        LINE(N);
        LINES(W, H, V) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(eachElementBetween(W, 1, WMAX));
        CONS(eachElementBetween(H, 1, HMAX));
        CONS(eachElementBetween(V, 1, VMAX));
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
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
        	"3",
        	"3 7 4",
        	"2 6 5",
        	"3 4 6"
        });
        Output({
        	"11"
        });
    }

    void BeforeTestCase() {
      	W.clear(), H.clear(), V.clear();
    }

    void TestCases() {
    	CASE(N = 5, randomTreasures(N, W, H, V));
    	CASE(N = 10, randomTreasures(N, W, H, V));
    	CASE(N = 20, randomTreasures(N, W, H, V));
    	for (int it = 0; it < 5; it++) {
    		CASE(N = rnd.nextInt(20, NMAX), randomTreasures(N, W, H, V));
    	}
    	for (int it = 0; it < 5; it++) {
    		CASE(N = NMAX, randomTreasures(N, W, H, V));
    	}
    }
 
private:

	void randomTreasures(int n, vector<int>& w, vector<int>& h, vector<int>& v) {
		w.resize(n), h.resize(n), v.resize(n);
		for (int i = 0; i < n; i++) {
			w[i] = rnd.nextInt(1, WMAX);
			h[i] = rnd.nextInt(1, HMAX);
			v[i] = rnd.nextInt(1, VMAX);
		}
	}
};