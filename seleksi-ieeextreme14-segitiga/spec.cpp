#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
private:
    bool eachElementBetween(const vector<long long>& X, long long lo, long long hi) {
        for (long long x : X) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

protected:
    int n;
    vector<long long> N;
    long long sum;

    void InputFormat() {
        LINE(n);
        LINE(N % SIZE(n));
    }

    void OutputFormat() {
        LINE(sum);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= n && n <= 500);
        CONS(eachElementBetween(N, 1, 2000000000));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5",
            "1 3 5 7 9"
        });
        Output({
            "3"
        });
    }

    void SampleTestCase2() {
        Input({
            "4",
            "2 2 2 2"
        });
        Output({
            "4"
        });
    }

    void BeforeTestCase() {
        N.clear();
    }

    void TestCases() {
        for (int i=1;i<=3;i++) {
            CASE(n = 10, randomElements(1, 1000));
        }
        for (int i=1;i<=3;i++) {
            CASE(n = 500, randomElements(1, 100000));
        }
        for (int i=1;i<=3;i++) {
            CASE(n = 10, randomElements(1000000000, 2000000000));
        }
        for (int i=1;i<=3;i++) {
            CASE(n = 500, randomElements(1000000000, 2000000000));
        }
    }

private:
    void randomElements(long long l, long long r) {
        for (int i = 0; i < n; i++) {
            N.push_back(rnd.nextLongLong(l, r));
        }

        rnd.shuffle(N.begin(), N.end());
    }
};