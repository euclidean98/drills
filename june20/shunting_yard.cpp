#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>

using namespace std;

set<char> ops = {'+','-','*','/','^'};
map<char, int> prec = {{'+', 1},{'-', 2},{'*', 3},{'/',4},{'^', 5}};

/**
 * Convert arithmetic expressions (using +, -, *, /, ^ in that order of precedence)
 * in infix notation to postfix notation (or, Reverse Polish Notation).
 * Using Dijkstra's Shunting Yard algorithm
 */
string toRPN(string exp){
    string result = "";
    stack<char> yardstack; //lol
    int current_prec, token_prec;
    char token, op;
    for (int i=0;i<exp.length();i++){
        token = exp[i];
        if (ops.count(token)){
            while(!yardstack.empty() && prec.count(yardstack.top())){
                current_prec = prec.find(yardstack.top())->second;
                token_prec = prec.find(token)->second;
                if (current_prec>token_prec){
                    op = yardstack.top();
                    yardstack.pop();
                    result += op;
                }else{
                    break;
                }
            }
            yardstack.push(token);
        }else if (token=='('){
            yardstack.push(token);
        }else if (token==')'){
            while(yardstack.top()!='('){
                result += yardstack.top();
                yardstack.pop();
            }
            yardstack.pop();
        }else{
            result+=token;
        }
    }
    while (!yardstack.empty()){
        result+=yardstack.top();
        yardstack.pop();
    }
    return result;
}

int main(){
    string exp;
    cin>>exp;
    cout<<toRPN(exp)<<endl;
    return 0;
}
