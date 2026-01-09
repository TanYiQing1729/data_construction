#include <iostream>
using namespace std;

/* UPLOAD START */

class MaxMean{
    public:
        MaxMean(){
            
        }
        
        void addNewInt(int x){
            
        }
        
        int getDataCount(){
            
        }
        
        double getAverage(){
            
        }
        
        int getMax(){
            
        }
    private:
        
};

/* UPLOAD END */

#include <stdlib.h>     /* srand, rand */

int main(){
    srand(7777);
    MaxMean mm;
    for(int i=0;i<300;i++){ //generate random numbers between -200 to 200
        mm.addNewInt(rand() % 401 - 200);
    }
    cout << "Count: " << mm.getDataCount() << endl;
    cout << "Max: " << mm.getMax() << endl;
    cout << "Average: " << mm.getAverage() << endl << endl;
    
    MaxMean mm2;
    for(int i=0;i<200;i++){
        mm2.addNewInt(i);
    }
    cout << "Count: " << mm2.getDataCount() << endl;
    cout << "Max: " << mm2.getMax() << endl;
    cout << "Average: " << mm2.getAverage() << endl << endl;
    
    return 0;
}