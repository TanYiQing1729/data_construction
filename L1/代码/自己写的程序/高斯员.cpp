#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int r;
    cin>>r;

    int a;
    int b;
    double d_s;

    int n1 = 0;
    int n2 = 0;
    int n = 0;

    for(a=1;a<=r;a++){
        b = sqrt(r*r-a*a);
		n1 += b; 
    }

    n2 = r;

    n = 4*n1 + 4*n2 +1;
    cout<<n;
    return 0;
}
