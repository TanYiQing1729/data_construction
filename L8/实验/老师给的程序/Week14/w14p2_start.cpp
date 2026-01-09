#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */

int maxQuadProduct(int* arr, int n){
    // TODO
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
