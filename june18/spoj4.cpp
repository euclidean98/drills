#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

set<char> ops = {'+','-','*','/','^'};
map<char, int> pr = {{'+', 1},{'-', 2},{'*', 3},{'/',4},{'^', 5}};

int findOperand(string exp, int opPos,bool isLeft){
    if (isLeft){
        if (exp[opPos-1]=='}'){
            int j = opPos-1, closedCount = 1;
            while (closedCount){
                j--;
                closedCount -= exp[j]=='{';
                closedCount += exp[j]=='}';
            }
            return j;
        }else{
            return opPos-1;
        }
    }else{
        //find right operand
        if (exp[opPos+1]=='{'){
            int j = opPos+1, openCount = 1;
            while (openCount){
                j++;
                openCount -= exp[j]=='}';
                openCount += exp[j]=='{';
            }
            return j;
        }else{
            return opPos+1;
        }
    }
}

string transform(string exp){
    // cout<<exp<<endl;
    char op = ' ';
    int pos = -1;
    int maxPrecedence = 0;
    int openCurly = 0, openBraces = 0;
    for (int i = 0; i<exp.length(); i++){
        switch(exp[i]){
            case '{':
                openCurly = 1;
                while (openCurly){
                    i++;
                    openCurly -= exp[i]=='}';
                    openCurly += exp[i]=='{';
                }
                break;
            case '(':
                if (maxPrecedence>0||true){
                    //inner exp.
                    openBraces = 1;
                    int openPos = i;
                    while (openBraces){
                        i++;
                        openBraces -= exp[i]==')';
                        openBraces += exp[i]=='(';
                    }
                    string subexp = exp.substr(openPos+1, i - openPos-1);
                    subexp = transform(subexp);
                    string left = openPos>0 ? exp.substr(0,openPos):"";
                    string right = i<exp.length()-1? exp.substr(i+1, exp.length()-i-1):"";
                    return transform(left+subexp+right);
                }else{
                    return transform(exp.substr(1, exp.length()-2)); //remove surrounding parens
                }
                break;
            default:
                if (ops.count(exp[i])){
                    int pr_i = pr.find(exp[i])->second;
                    if (pr_i>maxPrecedence){
                        maxPrecedence = pr_i;
                        op = exp[i];
                        pos = i;
                    }
                }
        }
    }

    if (maxPrecedence==0){
        return exp;
    }else{
        int leftBegin = findOperand(exp, pos, true);
        int rightEnd = findOperand(exp, pos, false);
        string leftOperand = exp.substr(leftBegin, pos-leftBegin);
        string rightOperand = exp.substr(pos+1, rightEnd - pos);
        string left = leftBegin>0?exp.substr(0, leftBegin):"";
        string right = rightEnd<(exp.length()-1)?exp.substr(rightEnd+1, exp.length()-rightEnd-1):"";
        string replaceStr = left + '{' + leftOperand + rightOperand + op + '}' + right;

        return transform(replaceStr);
    }
}

int main(){

    int T;
    cin>>T;
    while (T--){
        string exp;
        cin>>exp;
        string rpnExp = transform(exp);
        rpnExp.erase(remove(rpnExp.begin(), rpnExp.end(), '{'), rpnExp.end());
        rpnExp.erase(remove(rpnExp.begin(), rpnExp.end(), '}'), rpnExp.end());
        cout<<rpnExp<<endl;
    }

}
