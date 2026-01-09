#include <iostream>
#include <iomanip>
using namespace std;

/* UPLOAD START */

template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        
    public:
        AMinHeap(){
            
        }
        AMinHeap(T* arr, int n){
            
        }
        ~AMinHeap(){
            
        }
        bool isEmpty(){
            
        }
        T getMin(){
            
        }
        void push(T x){
            
        }
        T delMin(){
            
        }
        T* getLevelOrderArray(){
            
        }
        int getNumData(){
            
        }
};

/* UPLOAD END */

template <class T>
void printLevelOrder(T* data, int numItems){ //assumes class T has an overloaded ostream << operator.
    for(int i=1;i<=numItems;i++){
        cout << data[i] << " ";
    }
}

int test1(){ // normal test
    AMinHeap<int> amh;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    amh.push(10);
    amh.push(8);
    amh.push(6);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    amh.push(4);
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    cout << (amh.isEmpty() ? "Empty" : "Non-Empty") << " Heap" << endl;
    
    cout << "Top: " << amh.getMin() << endl;
    printLevelOrder(amh.getLevelOrderArray(),amh.getNumData());
    cout << endl;
    
    cout << "Popping:" << endl;
    while(!amh.isEmpty()){
        cout << "Current Min: " << amh.delMin() << endl;
        cout << endl;
    }
    return 0;
}

int main(){
    //unit test for Heap.
    test1();
    return 0;
}