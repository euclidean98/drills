//Transform into RPN (Reverse Polish Notation)

#include <string>
#include <iostream>
#include <set>

using namespace std;

int main(){
    set<char> ops = {'+','-','*','/','^'};
    string c;
    int T;
    cin>>T;
    while (T--){
        cin>>c;
        //FIXME : Add brackets. 
        bool complete= false;
        while(!complete){
            complete = true;
            int numOpen = 0;
            int left = 0, right = 0, op=0, leftmost= -1;

            string nC="";
            for(int i =0;i<c.size();i++){
                if (ops.count(c[i])){
                    if (numOpen==1){
                        op = i;
                    }
                }
                if (c[i]=='('){
                    if (++numOpen==1){
                        left = i;
                        leftmost = leftmost<0?left: leftmost;
                    }else{
                        complete = false;
                    }
                }
                if (c[i]==')'){
                    if (--numOpen==0){
                        right = i;
                        string first = c.substr(left+1, op-left-1);
                        string second = c.substr(op+1, right-op-1);
                        nC += first + second +c[op];
                    }
                }
            }
            nC = c.substr(0,leftmost) + nC + c.substr(right+1, c.length()-right-1);
            c = nC;
        }
        cout<<c<<endl;
    }
}
