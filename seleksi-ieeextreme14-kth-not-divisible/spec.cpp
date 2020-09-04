#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
private:
    bool eachElementBetween(const vector<int>& X, int lo, int hi) {
        for (int x : X) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

protected:
    int T;
    vector<int> N, K;
    vector<int> sum;

    void InputFormat() {
        LINE(T);
        LINES(N, K) % SIZE(T);
    }

    void OutputFormat() {
        LINES(sum) % SIZE(T);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= T && T <= 1000);
        CONS(eachElementBetween(N, 2, 1000000000));
        CONS(eachElementBetween(K, 1, 1000000000));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5",
            "7 4",
            "4 7",
            "2 100",
            "5 12",
            "500000000 1000000000"
        });
        Output({
            "4",
            "9",
            "199",
            "14",
            "1000000002"
        });
    }

    void TestCases() {
        vector<int> N1, K1;
        // random
        for (int i=1;i<=500;i++) {
            N1.push_back(rnd.nextInt(2, 1000));
            K1.push_back(rnd.nextInt(1, 1000));
        }

        // n < k
        for (int i=1;i<=500;i++) {
            int tn = rnd.nextInt(2, 1000), tk = rnd.nextInt(1, 1000);
            tn %= tk;
            if (tn < 2) tn += 2;
            N1.push_back(tn);
            K1.push_back(tk);
        }
        CASE(T = 1000, N = N1, K = K1);

        vector<int> N2, K2;
        // random
        for (int i=1;i<=500;i++) {
            N2.push_back(rnd.nextInt(2, 1000000000));
            K2.push_back(rnd.nextInt(1, 1000000000));
        }

        // n < k
        for (int i=1;i<=500;i++) {
            int tn = rnd.nextInt(2, 1000000000), tk = rnd.nextInt(1, 1000000000);
            tn %= tk;
            if (tn < 2) tn += 2;
            N2.push_back(tn);
            K2.push_back(tk);
        }
        CASE(T = 1000, N = N2, K = K2);
    }
};