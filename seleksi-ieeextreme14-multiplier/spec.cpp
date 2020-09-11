#include <tcframe/spec.hpp>
#include <cassert>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {

private:
	bool eachElementIsPrime(const vector<long long>& ve) {
		for(long long i : ve) {
			for(long long j = 2; j * j <= i; j++) {
				if(i % j == 0) return false;
			}
		}
		return true;
	} 

protected:
    int M;
    vector<long long> PRIMES;
    int ANS;

    void InputFormat() {
        LINE(M);
        LINE(PRIMES % SIZE(M));
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(2);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= M && M <= 200000);
        CONS(eachElementIsPrime(PRIMES));
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {

private:
	vector<int> primes;
	void generatePrimes() {
		bool isPrime[200000 + 69];
		for(long long i = 2; i <= 200000; i++) {
			bool ok = 1;
			for(long long j = 2; j * j <= i; j++) {
				if(i % j == 0) {
					ok = false;
					break;
				}
			}
			if(ok) { primes.push_back(i); }
		}
	}
	void randomLongPrime(int n, int lim = 0) {
    	assert(1 <= n && n <= 200000);
    	int sz = (int)primes.size();
    	if(lim == 0) { lim = sz; }
    	for(int i = 1; i <= n; i++) {
    		int pos = rnd.nextInt(0, lim - 1);
     		PRIMES.push_back(primes[pos]);
    	}
    }
    
protected:
	
    void SampleTestCase1() {
        Input({
            "1",
            "31"
        });
        Output({
            "31"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "2",
            "2 3"
        });
        Output({
            "36"
        });
    }
    
    void BeforeTestCase() {
    	primes.clear();
    	generatePrimes();
    	PRIMES.clear();
    }

    void TestCases() {
    	CASE(M = 3, PRIMES = {2, 3, 5});
		CASE(M = 4, PRIMES = {101, 2, 37, 101});
		CASE(M = 3, PRIMES = {61, 61, 61});
		CASE(M = 8, PRIMES = {2, 2, 2, 2, 2, 2, 2, 3});
		CASE(M = 10, randomLongPrime(M, 5));
		CASE(M = 2, PRIMES = {101, 101});
		CASE(M = 1, randomLongPrime(M, 5));
		CASE(M = 25, randomLongPrime(M, 5));
		CASE(M = 100, randomLongPrime(M, 5));
		CASE(M = 50, randomLongPrime(M, 5));
		CASE(M = 75, randomLongPrime(M, 5));
        
        for(int i = 0; i < 20; i++) {
        	CASE(M = rnd.nextInt(100000, 200000), randomLongPrime(M, 100));
        }
        
        CASE(M = 200000, randomLongPrime(M));
        CASE(M = 200000, randomLongPrime(M));
        CASE(M = 200000, randomLongPrime(M));
        CASE(M = 200000, randomLongPrime(M));
        CASE(M = 200000, randomLongPrime(M));
    }
};
