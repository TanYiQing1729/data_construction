#include <iostream>
#include <stdlib.h>

using namespace std;

/* Question 5 UPLOAD START */

class coinChanger{
    private:
        
    public:
        coinChanger(){
            // not used
        }
        coinChanger(int* coinValueSet, int n){
            
        }
        ~coinChanger(){
            
        }
        int numCoinsToMakeChange(int target){
            // limit target to be <= 1000;
            // return -1 if impossible.
            
            
        }
};

/* Question 5 UPLOAD END */

void test1(){
    int coinValueSet1[4] = {1,2,5,10};
    int coinValueSet2[3] = {1,8,10};
    
    coinChanger cc(coinValueSet1,4);
    
    cout << "Using the set {1,2,5,10}, making changes for:" << endl;
    cout << "99: " << cc.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc.numCoinsToMakeChange(998) << endl;
    
    
    coinChanger cc2(coinValueSet2,3);
    cout << "Using the set {1,8,10}, making changes for: " << endl;
    cout << "16: " << cc2.numCoinsToMakeChange(16) << endl;
    cout << "24: " << cc2.numCoinsToMakeChange(24) << endl;
    cout << "32: " << cc2.numCoinsToMakeChange(32) << endl;
    cout << "99: " << cc2.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc2.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc2.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc2.numCoinsToMakeChange(998) << endl;
}

int main(){
    test1();
    return 0;
}