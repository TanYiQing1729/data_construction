#include <iostream>
using namespace std;

/* UPLOAD START */

class MaxMean{
    public:
        MaxMean(){
            Max = 0;
            sum = 0;
            ave = 0;
            num = 0;
        }

        void addNewInt(int x){
            if (x > Max)
            {
            	Max = x;
			}
			sum = sum + x;
			num = num + 1;
        }

        int getDataCount(){
            return num;
        }

        double getAverage(){
            ave = sum / num;
            return ave;
        }

        int getMax(){
            return Max;
        }
    private:
        int Max;
        double sum;
        double ave;
        int num;
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
