#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool isPal(string str){
    int l = str.length();
    if (l%2){
        //odd
        string left = str.substr(0, (l-1)/2);
        string right = str.substr(((l-1)/2)+1, (l-1)/2);
        reverse(right.begin(),right.end());

        return !left.compare(right);
    }else{
        string left = str.substr(0, l/2);
        string right = str.substr(l/2, l/2);
        reverse(right.begin(),right.end());

        return !left.compare(right);
    }
}

int main(){
    int num;

    while (1){
        cout<<"Enter number : ";

        cin>>num;
        if (num==0){
            break;
        }
        while (1){
            if (isPal(to_string(++num))){
                cout<<num<<endl;;
                break;
            }
        }
    }
}
