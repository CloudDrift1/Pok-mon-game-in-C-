#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include "solve.hpp"

#include <string>
#include <functional>
#include <algorithm>
#include <cmath>
#include <set>
#include <utility>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;


int priority(char alpha) {
    if (alpha == '+' || alpha == '-')
        return 1;
    if (alpha == '*' || alpha == '/')
        return 2;
    if (alpha == '^')
        return 3;
    return 0;
}

int evaluate(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        default:
            return 0;
    }
}

vector<string> generateParentheses(const string expression) {
    vector<string> result;
    
    function<vector<string>(int, int)> helper = [&](int start, int end) -> vector<string> {
        if (start == end) {
            return {string(1, expression[start])};
        }
        
        vector<string> res;
        for (int i = start; i <= end; ++i) {
            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
                auto leftParts = helper(start, i - 1);
                auto rightParts = helper(i + 1, end);
                for (const auto& left : leftParts) {
                    for (const auto& right : rightParts) {
                        res.push_back("(" + left + expression[i] + right + ")");
                    }
                }
            }
        }
        return res;
    };
    
    return helper(0, expression.size() - 1);
}

vector<int> remove_outer_parentheses(const string expression) {
    vector<int> result;
    int start = 0;
    int start_prev = -1;
    bool is_prev_open = false;
    int end = expression.size() - 1;
    int end_prev = end;

    while (start < end) {
        if (expression[start] == '(') {
            int j = end_prev;
            while (j > start) {
                if (expression[j] == ')') {
                    end = j;
                    break;
                } else {
                    j -= 1;
                }
            }
            if (is_prev_open) {
                result.push_back(start_prev);
                start_prev = start;
                result.push_back(end);
                end_prev = end - 1;
            } else {
                is_prev_open = true;
                start_prev = start;
            }
        } else if (expression[start] == ')') {
            is_prev_open = false;
            start_prev = -1;
        }
        start++;
    }
    return result;
}

string remove(string expression, vector<int> remove_idx) {
    string result = "";
    bool is_successive = false;
    int idx = -1;
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == ')' && is_successive) {
            continue;
        } else if (expression[i] == ')' && !is_successive) {
            is_successive = true;
        }

        if (find(remove_idx.begin(), remove_idx.end(), i) == remove_idx.end()) {
            result += expression[i];
            if (expression[i] == '(') {
                is_successive = false;
                idx = i + 4;
            }
        }
        if (i == idx && result.back() != ')') {
            result += ')';
        }
    }
    return result;
}
vector<char> strToVec(const string& expression){

    vector<char> ans;

    for(char elem:expression){
        ans.push_back(elem);
    }
    return ans;
}

string vecToStr(const vector<char> vec){
    string ans = "";
    for(char elem: vec){
        ans += elem;
    }
    return ans;
}

void printVec(const vector<char> expression){
    for(char elem: expression){
        cout<<elem<<"";
    }
    cout<<endl;
}

vector<vector<char>> allRemover(vector<string> allPossible){
    vector<vector<char>> answer;

    for(string& elem: allPossible){
        vector<int> result = remove_outer_parentheses(elem);
        string final_result = remove(elem, result);
        vector<char> final_result_vec = strToVec(final_result);
        answer.push_back(final_result_vec);
    }
    return answer;
}

vector<vector<char>> Challenge::postfixLst(const vector<vector<char>>& infixLst){
    vector<vector<char>> ans;
    for(auto& elem: infixLst){
        ans.push_back(mid2post(elem));
    }
    return ans;
}

set<string> createSet(const vector<vector<char>>& vecVecChar) {
    set<string> resultSet;
    for (const auto& vecChar : vecVecChar) {
        string str = vecToStr(vecChar);
        resultSet.insert(str);
    }
    return resultSet;
}

pair<int, int> countParentheses(const string& str) {
    int openCount = std::count(str.begin(), str.end(), '(');
    int closeCount = std::count(str.begin(), str.end(), ')');
    return make_pair(openCount, closeCount);
}

set<string> removeOddParentheses(const set<string>& inputSet) {
    set<string> modifiedSet;
    for (const string& str : inputSet) {
        pair<int, int> counts = countParentheses(str);
        int openCount = counts.first;
        int closeCount = counts.second;
        if ((openCount == closeCount)) {
            modifiedSet.insert(str);
        }
    }
    return modifiedSet;
}

vector<string> Challenge::insertAllParentheses(const string expression){
    vector<string> result;
    function<vector<string>(int, int)> helper = [&](int start, int end) -> vector<string> {
        if (start == end) {
            return {string(1, expression[start])};
        }
        vector<string> res;
        for (int i = start; i <= end; ++i) {
            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
                auto leftParts = helper(start, i - 1);
                auto rightParts = helper(i + 1, end);
                for (const auto& left : leftParts) {
                    for (const auto& right : rightParts) {
                        res.push_back("(" + left + expression[i] + right + ")");
                    }
                }
            }
        }
        return res;
    };

    return helper(0, expression.size() - 1);
}

set<string> removeUnbalancedParentheses(const set<string>& inputSet) {
    set<string> modifiedSet;
    for (const string& str : inputSet) {
        pair<int, int> counts = countParentheses(str);
        int openCount = counts.first;
        int closeCount = counts.second;
        if ((openCount == closeCount)) {
            modifiedSet.insert(str);
        }
    }
    return modifiedSet;
}
set<string> Challenge::createInfixSet(const vector<char>& infixExpr){
    string infixStr = vecToStr(infixExpr);
    vector<string> allParenthesesCases = insertAllParentheses(infixStr);
    vector<vector<char>> allInfixLst = allRemover(allParenthesesCases);
    vector<vector<char>> allpostfixLst = postfixLst(allInfixLst);
    set<string> resultSet = createSet(allpostfixLst);
    set<string> balancedSet = removeUnbalancedParentheses(resultSet);

    return balancedSet;
}

int Challenge::getMax(const set<string>& inputSet){
    int maxVal = -2147483647;
    for(string postfix: inputSet){
        int res = evalPostfix(strToVec(postfix));
        if(res >= maxVal){
            maxVal = res;
        }
    }
    return maxVal;
}


int getMaxValueUtil(vector<char>& expr, int start, int end) {
    if (start == end) {
        return expr[start] - '0'; // Operand
    }

    int maxVal =-2147483647;

    for (int i = start + 1; i < end; i += 2) {
        int left = getMaxValueUtil(expr, start, i - 1);
        int right = getMaxValueUtil(expr, i + 1, end);
        int result = evaluate(left, right, expr[i]);
        maxVal = max(maxVal, result);
    }
    return maxVal;
}

vector<char> Challenge::randomExprGenerate() {
    srand(time(NULL));
    // randomly generated odd number which is less than 20
    N = random() % 10 * 2 + 1;
    cout << "N: " << N << endl;
    // Number in 0 ~ 9 operator in +, -, *
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // generate random number in 1 ~ 9
            expr.push_back(random() % 9 + 1 + '0');
        } else {
            expr.push_back(random() % 3 == 0 ? '+' : random() % 3 == 1 ? '-' : '*');
        }
    }
    return expr;
}

bool Challenge::answerCheck(vector<char> expr, int answer) {
    int trueAnswer = getTrueAnswer(expr);
    cout << "True answer: " << trueAnswer << endl;
    return trueAnswer == answer;
}

int Challenge::getTrueAnswer(vector<char> expr) {

    set<string> modSet = createInfixSet(expr);
    int ans = getMax(modSet);
    return ans;
}

vector<char> Challenge::mid2post(vector<char> expr) {

    int i = 0;
    vector<char> postfix;
    stack<char> s;

    while (i < expr.size()) {
        if ((expr[i] >= '0' && expr[i] <= '9')) {
            postfix.push_back(expr[i]);
            i++;
        } else if (expr[i] == '(') {
            s.push(expr[i]);
            i++;
        } else if (expr[i] == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop(); 
            i++;
        } else {
            while (!s.empty() && priority(expr[i]) <= priority(s.top())) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(expr[i]);
            i++;
        }
    }
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

int Challenge::evalPostfix(vector<char> postfix) {

    stack<int> s;
    for (char c : postfix) {
        if (c >= '0' && c <= '9') {
            s.push(c - '0');
        } else {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch (c) {
                case '+':
                    s.push(operand1 + operand2);
                    break;
                case '-':
                    s.push(operand1 - operand2);
                    break;
                case '*':
                    s.push(operand1 * operand2);
                    break;
                case '/':
                    s.push(operand1 / operand2);
                    break;
                case '^':
                    s.push(pow(operand1, operand2));
                    break;
            }
        }
    }
    return s.top();
}

int Challenge::evalExpr() {
    vector<char> postfix = mid2post(expr);
    return evalPostfix(postfix);
}

bool Challenge::run() {
    cout << "Calculate the maximum value of the expression by inserting parentheses." << endl;
    cout << "No nested parentheses are allowed." << endl;
    cout << "Expr: ";
    randomExprGenerate();
    for (int i = 0; i < N; i++) {
        cout << expr[i];
    }
    cout << endl;
    cout << "Type the answer: ";
    int answer;
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    if (iss >> answer) {
        bool isCorrect = answerCheck(expr, answer);
        if (isCorrect) {
            std::cout << "Correct!" << std::endl;
        } else {
            std::cout << "Wrong!" << std::endl;
        }
        return isCorrect;
    } else {
        std::cerr << "Invalid input! Please enter a valid integer." << std::endl;
        return false;
    }

}

Challenge::Challenge() {
}