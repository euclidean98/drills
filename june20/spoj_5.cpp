#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string mirror(string s, int starting){
    string left = s.substr(0, starting);
    int num_mirror = s.length() - starting;
    string mirror = s.substr(0, num_mirror);
    reverse(mirror.begin(), mirror.end());
    return left + mirror;
}

string nextPal(string s){
    if (s.length()%2){
        int center = s.length()/2;
        string c = string(1,s[center]);
        int left = 0, right = 0;

        //assume s[center]<9.
        for (int i=0; i<=center;i++){
            left = stoi(string(1,s[center-i]));
            right = stoi(string(1,s[center+i]));
            if (left>right){
                //must mirror starting right.
                return mirror(s, center+i);
            }else if (left<right){
                //must increase (center? leftmost changeable.) and mirror left completely.
                int j = 0;
                while (s[center-j]=='9' && j<=center){
                    s[center-j] = s[center+j] = '0';
                    j++;
                }
                if (j>center){
                    return '1' + s.substr(0,s.length()-1) + '1';
                }else{
                    s[center-j]++;
                    return mirror(s, center+j);
                }
            }else{
                continue;
            }
        }
        //not changed ?? so it is already palindrome.
        //increase center.
        int j = 0;
        while (s[center-j]=='9' && j<=center){
            s[center-j] = s[center+j] = '0';
            j++;
        }
        if (j>center){
            return '1' + s.substr(0, s.length()-1)+ '1';
        }else{
            s[center-j]++;
            return mirror(s, center+j);
        }
    }else{ //even.
        int r = s.length()/2;
        int l = r - 1;

        int left = 0, right = 0;
        for (int i =0;i<=l;i++){
            left = stoi(string(1, s[l-i]));
            right = stoi(string(1, s[r+i]));
            if (left>right){
                //must mirror starting right.
                return mirror(s, r);
            }else if (left<right){
                //must increase leftmost increasable index (currently r) and mirror starting r.
                //if this happened at i!=0, that means there is some searching to do.
                if (i!=0){
                    int j=0;
                    bool allNines = true;
                    while(j<=l){
                        if (stoi(string(1,s[l-j]))<9){
                            allNines = false;
                            break;
                        }
                        j++;
                    }
                    if (allNines){
                        return "1" + string(s.length()-1, '0') + "1";
                    }else{
                        //increase s[l-j] by 1. zero everything until s[r+j-1]. mirror from s[r+j].
                        s[l-j]++;
                        string mirror_str = s.substr(0, l-j+1);
                        reverse(mirror_str.begin(), mirror_str.end());
                        string pal = s.substr(0,l-j+1) + string(j*2, '0') + mirror_str;
                        return pal;
                    }

                }else{
                    //happened right at i==0. Just increase s[l] by 1 and mirror.
                    s[l]++;
                    return mirror(s, r);
                }
            }else{
                continue;
            }
        }

        //already palindrome.
        int j=0;
        bool allNines = true;
        while(j<=l){
            if (stoi(string(1,s[l-j]))<9){
                allNines = false;
                break;
            }
            j++;
        }
        if (allNines){
            return "1" + string(s.length()-1, '0') + "1";
        }else{
            //increase s[l-j] by 1. zero everything until s[r+j-1]. mirror from s[r+j].
            s[l-j]++;
            string mirror_str = s.substr(0, l-j+1);
            reverse(mirror_str.begin(), mirror_str.end());
            string pal = s.substr(0,l-j+1) + string(j*2, '0') + mirror_str;
            return pal;
        }
    }
}

int main(){
    int t;
    cin>>t;
    string s;
    while (cin>>s){
        cout<<nextPal(s)<<endl;
    }
}
