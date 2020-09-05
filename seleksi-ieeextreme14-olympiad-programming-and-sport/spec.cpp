#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int NMAX = 3000;
const int VMAX = 100000;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, X, Y;
    vector<int> A, B;
    int res;
    void InputFormat() {
        LINE(N, X, Y);
        LINES(A, B) % SIZE(N);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(512);
    }

    void Constraints() {
        CONS(1 <= N && N <= NMAX);
        CONS(0 <= X && X <= NMAX);
        CONS(0 <= Y && Y <= NMAX);
        CONS(checkTroops(N, X, Y));
        CONS(eachElementBetween(A, 1, VMAX));
        CONS(eachElementBetween(B, 1, VMAX));
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

    bool checkTroops(int n, int x, int y) {
    	return (x + y <= n);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
			"5 2 2",
			"1 5",
			"3 3",
			"4 2",
			"5 1",
			"2 4"
        });
        Output({
        	"18"
        });
    }

    void BeforeTestCase() {
      	A.clear(), B.clear();
    }

    void TestCases() {
    	CASE(N = 5, randomAttackDefense(N, X, Y), randomTroops(N, A, B, 1, 100));
    	CASE(N = 10, randomAttackDefense(N, X, Y), randomTroops(N, A, B, 1, 1000));
    	for (int it = 0; it < 5; it++) {
    		CASE(N = rnd.nextInt(10, 3000), randomAttackDefense(N, X, Y), randomTroops(N, A, B, 1, VMAX));
    	}
    	for (int it = 0; it < 10; it++) {
    		CASE(N = NMAX, randomAttackDefense(N, X, Y), randomTroops(N, A, B, 1, VMAX));
    	}
    }
 
private:
	void randomAttackDefense(int n, int& x, int &y) {
		x = rnd.nextInt(0, n);
		y = n - x;
	}

	void randomTroops(int n, vector<int>& a, vector<int>& b, int lo, int hi) {
		a.resize(n), b.resize(n);
		for (int i = 0; i < n; i++) {
			a[i] = rnd.nextInt(lo, hi);
			b[i] = rnd.nextInt(lo, hi);
		}
	}
};