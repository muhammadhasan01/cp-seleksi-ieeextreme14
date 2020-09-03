#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> A;
    int ans;

    void InputFormat() {
        LINE(N);
        LINE(A % SIZE(N));
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= 200000);
        CONS(eachElementBetween(A, 1, 1000000000));
    }

private:
    bool eachElementBetween(const vector<int>& X, int lo, int hi) {
        for (int x : X) {
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
            "1 3 5"
        });
        Output({
            "4"
        });
    }

    void BeforeTestCase() {
        A.clear();
    }

    void TestCases() {
        // Very small
        for (int i = 1; i < 5; i++) {
            CASE(N = i, randomArray(1, 1e9));
        }
        // Small
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(1, 1000), randomArray(1, 1e9));
        }
        // Big
        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(1001, 200000), randomArray(1, 1e9));
        }
        // Very big
        CASE(N = 199999, randomArray(1e8, 1e9));
        CASE(N = 200000, randomArray(1e8, 1e9));
        // Idk maybe corner?
        CASE(N = 1, randomArray(1, 1));

    }

private:
    void randomArray(int MinEl, int MaxEl) {
        for (int i = 0; i < N; i++) {
            A.push_back(rnd.nextInt(MinEl, MaxEl));
        }
    }
};