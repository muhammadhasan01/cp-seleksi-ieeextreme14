#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T;
    int n, k;
    int sum;

    void InputFormat() {
        LINE(n, k);
    }

    void OutputFormat() {
        LINE(sum);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= 1000);
    }

    void Constraints() {
        CONS(2 <= n && n <= 1000000000);
        CONS(1 <= k && k <= 1000000000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "7 4"
        });
        Output({
            "4"
        });
    }
    void SampleTestCase2() {
        Input({
            "4 7"
        });
        Output({
            "9"
        });
    }
    void SampleTestCase3() {
        Input({
            "2 100"
        });
        Output({
            "199"
        });
    }
    void SampleTestCase4() {
        Input({
            "5 12"
        });
        Output({
            "14"
        });
    }
    void SampleTestCase5() {
        Input({
            "500000000 1000000000"
        });
        Output({
            "1000000002"
        });
    }

    void TestCases() {
        // random
        for (int i=1;i<=500;i++) {
            CASE(n = rnd.nextInt(2, 1000000000), k = rnd.nextInt(1, 1000000000));
        }

        // n < k
        for (int i=1;i<=500;i++) {
            int tn = rnd.nextInt(2, 1000000000), tk = rnd.nextInt(1, 1000000000);
            tn %= tk;
            if (tn < 2) tn += 2;
            CASE(n = tn, k = tk);
        }
    }
};