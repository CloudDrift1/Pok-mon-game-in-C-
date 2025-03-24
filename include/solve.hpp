#include <vector>
#include <set>
#include <string>
#include <functional>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;

class Challenge {

public:
    Challenge();
    bool run();
    vector<char> randomExprGenerate();
    bool answerCheck(vector<char>, int);
    int getTrueAnswer(vector<char>);
    vector<char> mid2post(vector<char>);
    int evalPostfix(vector<char>);
    int evalExpr();
    vector<string> insertAllParentheses(const string);
    int getMax(const set<string>& );
    vector<vector<char>> postfixLst(const vector<vector<char>>&);
    set<string> createInfixSet(const vector<char>&);

private:
    bool inserted[20]; 
    int maximum = -2147483647;
    int N;
    vector<char> expr;
};