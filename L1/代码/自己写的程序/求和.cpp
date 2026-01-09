#include <iostream>
using namespace std;

int main(){
    int a = 1;
    int sum = 0;
    while(a=!0){
        cin>>a;
        sum += a;
        if (a == 0){
            break;
        }

    }
    cout<<sum;
    return 0;
}
