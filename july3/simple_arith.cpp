#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;
typedef string::reverse_iterator rit;


void add(string x, string y){
    rit x_rit = x.rbegin();
    rit y_rit = y.rbegin();
    int x_c=0, y_c=0, carry=0;
    stack<int> result;
    while (x_rit!=x.rend() || y_rit!=y.rend()){
        x_c = x_rit!=x.rend()?(*x_rit) - '0':0;
        y_c = y_rit!=y.rend()?(*y_rit) - '0':0;

        result.push((x_c+y_c+carry)%10);
        carry = (x_c+y_c+carry)/10;

        if (x_rit!=x.rend()){
            x_rit++;
        }

        if (y_rit!=y.rend()){
            y_rit++;
        }
    }
    if (carry){
        result.push(carry);
    }
    string ans="";
    int maxlen = max(result.size(), y.length()+1);

    while (!result.empty()){
        ans+=to_string(result.top());
        result.pop();
    }

    // vector<string> printout;
    // printout.push_back(x);
    // printout.push_back('+'+y);
    // printout.push_back(string('-', maxlen));
    // printout.push_back(ans);
    // print(printout);
    string line(maxlen,'-');
    cout<<x<<endl<<'+'<<y<<endl<<line<<endl<<ans<<endl;
}

void subtract(string x, string y){

}

void multiply(string x, string y){

}

int main(){
    string query, x, y;
    cin>>query;
    int i=0;
    while (i<query.size()){
        if (!isdigit(query[i])){
            break;
        }
        i++;
    }
    x = query.substr(0, i);
    y = query.substr(i+1, query.size()-i-1);
    if (query[i]=='+'){
        add(x, y);
    }else if (query[i]=='-'){
        subtract(x,y);
    }else{
        multiply(x,y);
    }
    return 0;
}
