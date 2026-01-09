#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

void mergeIntervals(int** arr, int n){
    /* The first interval is arr[0][0] to arr[0][1]
       The 2nd interval is arr[1][0] to arr[1][1]
       ...
       The last interval is arr[n-1][0] to arr[n-1][1]
       Print the results of merging these intervals. Assume endpoints are always included.
    */
    
}

/* UPLOAD END */

void test1(){
    int** a = new int*[2];
    a[0] = new int[2];
    a[1] = new int[2];
    a[0][0] = 1;
    a[0][1] = 4;
    a[1][0] = 4;
    a[1][1] = 5;
    mergeIntervals(a,2);
    
    int** b = new int*[4];
    b[0] = new int[2]{1,3};
    b[1] = new int[2]{2,6};
    b[2] = new int[2]{8,10};
    b[3] = new int[2]{15,18};
    mergeIntervals(b,4);
}

int main()
{
    test1();
    return 0;
}