#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXB = 10000;

class ProblemSpec: public BaseProblemSpec {
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
        int N;
        vector<int> arr;
        long long ans;

        void InputFormat() {
            LINE(N);
            LINE(arr % SIZE(N));
        }

        void OutputFormat() {
            LINE(ans);
        }

        void GradingConfig() {
            TimeLimit(1);
            MemoryLimit(256);
        }

        void Constraints() {
            CONS(1 <= N && N <= MAXN);
            CONS(eachElementBetween(arr, -MAXB, MAXB));
        }
};

class TestSpec: public BaseTestSpec<ProblemSpec> {
    private:
        vector<int> randomArray(int N) {
            vector<int> res;
            
            for (int i = 0; i < N; ++i) {
                res.push_back(rnd.nextInt(-MAXB, MAXB));
            }

            return res;
        }

    protected:
        void SampleTestCase1() {
            Input({
                "4",
                "-2 2 -3 1"
            });
            Output({
                "3"
            });
        }

        void TestCases() {
            for (int i = 0; i < 3; ++i) {
                CASE(N = rnd.nextInt(1, 1000), arr = randomArray(N));
            }
            for (int i = 0; i < 5; ++i) {
                CASE(N = rnd.nextInt(10000, MAXN), arr = randomArray(N));
            }
        }
};