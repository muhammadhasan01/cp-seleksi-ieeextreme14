#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

typedef long long LL;

const LL MAXP = (LL)1e18;

class ProblemSpec: public BaseProblemSpec {
    protected:
        LL permen, ans;

        void InputFormat() {
            LINE(permen);
        }

        void OutputFormat() {
            LINE(ans);
        }

        void GradingConfig() {
            TimeLimit(1);
            MemoryLimit(256);
        }

        void Constraints() {
            CONS(1 <= permen && permen <= MAXP);
        }
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
    protected:
        void SampleTestCase1() {
            Input({
                "100"
            });
            Output({
                "111"
            });
        }

        void TestCases() {
            for (int i = 0; i < 3; ++i) {
                CASE(permen = rnd.nextLongLong(1, 1000));
            }
            for (int i = 0; i < 2; ++i) {
                CASE(permen = rnd.nextLongLong(1000 + 1, 1000000));
            }
            for (int i = 0; i < 10; ++i) {
                CASE(permen = rnd.nextLongLong(100000000, MAXP));
            }
            CASE(permen = MAXP);
            CASE(permen = MAXP-1);
        }

};