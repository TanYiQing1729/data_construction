#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */

int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    
}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (2*i) << ": " << numOfBinaryTrees(2*i) << endl;
    }
}

int main(){
    test();
    return 0;
}