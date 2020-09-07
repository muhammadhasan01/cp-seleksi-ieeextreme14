#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
private:
	bool lowercase(string str) {
		for(auto ch : str) {
			if((ch < 'a') || (ch > 'z')) {
				return false;
			}
		}
		return true;
	}
	
protected:
    string S, T;
    int ANS;

    void InputFormat() {
        LINE(S);
        LINE(T);
    }

    void OutputFormat() {
        LINE(ANS);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 <= (int)S.length() && (int)S.length() <= 200000);
        CONS(1 <= (int)T.length() && (int)T.length() <= 200000);
        CONS(lowercase(S));
        CONS(lowercase(T));
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
private:
	void randomLongStringS() {
    	S = "";
    	int j = rnd.nextInt(100000);
    	for(int i = 0; i < j + 30; i++) {
    		int rand = rnd.nextInt(20);
    		char randChar = (char) (rand + 'b');
    		S.push_back(randChar);
    	}
    	S += "ahaha";
    }
    
    void randomLongStringT() {
    	T = "";
    	int j = rnd.nextInt(100000);
    	for(int i = 0; i < j + 30; i++) {
    		int rand = rnd.nextInt(20);
    		char randChar = (char) (rand + 'b');
    		T.push_back(randChar);
    	}
    	T += "bwahahaha";
    }
    
protected:
	/**
    void SampleTestCase1() {
        Input({
            "mengapa"
            "kenapa"
        });
        Output({
            "7"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "wkwkwkkwk"
            "wwkwkwk"
        });
        Output({
            "10"
        });
    }
    **/

    void TestCases() {
        CASE(S = "test", T = "west");
        CASE(S = "codeforces", T = "yes");
        CASE(S = "a", T = "ab");
        CASE(S = "bbdab", T = "dab");
        CASE(S = "a", T = "aa");
        CASE(S = "codeforces", T = "ces");
        CASE(S = "codeforces", T = "yes");
        CASE(S = "abacabadabacaba", T = "abacabadacaba");
        CASE(S = "test", T = "yes");
        
        for(int i = 0; i < 10; i++) {
        	CASE(randomLongStringS(), randomLongStringT());
        }

        CASE(S = string(200000, 'a'), T = string(100000, 'a'));
        CASE(S = string(200000, 'z'), T = string(200000, 'z'));
        CASE(S = string(100000, 'b'), T = string(100000, 'b'));
        CASE(S = string(100000, 'b'); S.push_back('a'), T = string(100000, 'a'));
        CASE(S = string(100000, 'b'); S.push_back('a'), T = string(100000, 'b'));
        
        
    }
};
