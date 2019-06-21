#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main(){
    int T,k;
    cin >> T;
    unsigned long m, n,i;
    bool isPrime;
    while (T--){
        cin>>m>>n;
        m = 1==m?2:m;
        for (i=m; i<=n; i++){
            k = ceil(sqrt(i));
            isPrime = true;

            for (unsigned int j = 2 ; j<=k; j++){
                if (i%j==0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime||i==2){
                cout<<i<<endl;
            }
        }
        cout<<"\n";
    }

}
