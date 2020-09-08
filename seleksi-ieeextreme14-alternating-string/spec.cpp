#include <tcframe/spec.hpp>
using namespace tcframe;
#define MAXN 1000
#define MAXK 1000
#define MAXT 50

using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int T, N, K;
    string s;
    int sum;

    void MultipleTestCasesConfig() {
        Counter(T);
    }

    void InputFormat() {
        LINE(N, K);
        LINE(s);
    }

    void OutputFormat() {
        LINE(sum);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAXN);
        CONS(1 <= K && K <= N);
        CONS(s.size() == N);
    }

    void MultipleTestCasesConstraints() {
        CONS(1 <= T && T <= MAXT);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 2",
            "11010"
        });
        Output({
            "3"
        });
    }

    void SampleTestCase2() {
        Input({
            "3 3",
            "110"
        });
        Output({
            "0"
        });
    }

    void BeforeTestCase() {
        s = "";
    }

    void TestCases() {
        CASE(N = MAXN, K = rnd.nextInt(1, N), generateAllSame(s, N, '1'));
        CASE(N = MAXN, K = rnd.nextInt(1, N), generateAllSame(s, N, '0'));
        for(int i = 0; i < 18; i++){
            CASE(N = rnd.nextInt(1, MAXN), K = rnd.nextInt(1, N), generateBinaryString(s, N));
        }
        for(int i = 0; i < 30; i++){
            CASE(N = rnd.nextInt(1, MAXN), K = rnd.nextInt(1, N), generateBinaryString(s, N, rnd.nextInt(1, 100)));
        }
    }

private:
    void generateBinaryString(string &s, int N, int chanceOne=50) {
        int total = 100;
        for(int i = 0; i < N; i++){
            if(rnd.nextInt(1, total) < chanceOne){
                s += "1";
            } else {
                s += "0";
            }
        }
    }

    void generateAllSame(string &s, int N, char x){
        for(int i = 0; i < N; i++){
            s += x;
        }
    }
};