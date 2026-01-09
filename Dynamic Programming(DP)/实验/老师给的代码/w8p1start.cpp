#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */

int numStepsToN_v2(int N, int mod_num){
    // calculate the number of ways to get to N
    // allowed step on each move: +1, +2, +3
    // However, no two consecutive steps are the same.
    
    
}

/* Question 1 UPLOAD END */

int main(){
    for(int i=0;i<=10;i++)
        cout << i << ": " << numStepsToN_v2(i,9999999) << endl;
    return 0;
}

/*
0: 1
1: 1
2: 1
3: 3
4: 3
5: 4
6: 8
7: 9
8: 12
9: 21
10: 27
*/