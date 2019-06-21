#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

/* Recursively transforming algebraic expressions into Reverse Polish Notation*/

set<char> ops = {'+','-','*','/','^'};
map<char, int> pr = {{'+', 1},{'-', 2},{'*', 3},{'/',4},{'^', 5}};

string toRPN(string c){
    bool done = false;
    string replaceStr = c;
    int openIgnore = 0;
    int openIgnorePos = -1;
    while (!done){
        bool expStarted = false;
        int maxPr = 0, maxPrPos = -1;
        bool needReplace = false;
        for (int i =0;i<c.length();i++){
            if (c[i]=='{'){
                if (!openIgnore){ openIgnorePos = i;}
                openIgnore++;
            }
            if (c[i]=='}'){
                openIgnore--;
            }
            if (openIgnore){
                continue;
            }
            if (expStarted){
                if (c[i]=='('){
                    needReplace = true;
                    int numOpen = 1;
                    int j = i+1;
                    while (1){
                        numOpen+=c[j]=='(';
                        numOpen-=c[j]==')';
                        if (numOpen==0){
                            break;
                        }
                        j++;
                    }
                    replaceStr = c.substr(0,i) + '{' +toRPN(c.substr(i, j-i+1)) + '}' + c.substr(j+1, c.length()-j-1);

                    break;
                }
            }
            if (ops.count(c[i])){
                expStarted = true;
                int pr_i = pr.find(c[i])->second;
                if (pr_i > maxPr){
                    maxPr = pr_i;
                    maxPrPos = i;
                }
            }
        }
        if (!expStarted){
            break;
        }
        if (needReplace){
            c = replaceStr;
        }else {
            string l, r;
            int open_l, close_r;
            //base case ...
            if (c[maxPrPos-1]!='}'){
                l = c.substr(maxPrPos-1,1);
                open_l = maxPrPos-1;
            }else{
                int numClosed = 1;
                int openPos = maxPrPos-1;
                while (numClosed){
                    openPos--;
                    numClosed += c[openPos]=='}';
                    numClosed -= c[openPos]=='{';
                }
                open_l = openPos;
                l = c.substr(openPos, maxPrPos-openPos);
            }

            if (c[maxPrPos+1]!='{'){
                r = c.substr(maxPrPos+1,1);
                close_r = maxPrPos+1;
            }else{
                int numOpen = 1;
                int closePos = maxPrPos+1;
                while (numOpen){
                    closePos++;
                    numOpen += c[closePos]=='{';
                    numOpen -= c[closePos]=='}';
                }
                close_r = closePos;
                r = c.substr(closePos, closePos - maxPrPos);
            }
            replaceStr = c.substr(0, open_l) + '{' + l + r + c[maxPrPos] + '}' + c.substr(close_r+1, c.length()-close_r-1);
            c = replaceStr;
        }
    }
    return c;
}

int main(){
    int T;
    cin>>T;

    while (T--){
        string c;
        cin>>c;
        cout<<toRPN(c)<<endl;
    }

}
