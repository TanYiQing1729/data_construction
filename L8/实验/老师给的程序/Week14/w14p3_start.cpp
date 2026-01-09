#include <iostream>
using namespace std;

/* UPLOAD START */

int longestSubsequenceLength(int* arr, int n){
    
}

/* UPLOAD END */

void test1(){
    int a[8] = {10,9,2,5,3,7,101,18};
    cout << longestSubsequenceLength(a,8) << endl; //4
}

void test2(){
    int a[7] = {1,2,3,5,3,7,8};
    cout << longestSubsequenceLength(a,7) << endl; //6
}

int main(){
    test1();
    test2();
    return 0;
}