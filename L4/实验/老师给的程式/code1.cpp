#include <iostream>
using namespace std;

/* UPLOAD START */

template <class T>
struct TriTuple{
    int rp, cp;
    T value;
};

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};



// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        int rows, columns;
        VecList<TriTuple<T>>* true_value_list;
    public:
        SparseMatrix(){
            // default is 10 rows, 10 columns
            rows = 10;
            columns = 10;
            true_value_list = new VecList<TriTuple<T>>;
        }
        SparseMatrix(int r, int c){
            rows = r;
            columns = c;
            true_value_list = new VecList<TriTuple<T>>;
        }
        ~SparseMatrix(){
            delete true_value_list;
        }
        void setEntry(int rPos, int cPos, T x){
            TriTuple<T> new_tuple = *new TriTuple<T>;
            new_tuple.cp = cPos;
            new_tuple.rp = rPos;
            new_tuple.value = x;

            int to_set_pos = -1;
            TriTuple<T> tmp_tuple;
            for(int i=0;i<true_value_list->getLength();i++){
                tmp_tuple = true_value_list->getEleAtPos(i);
                if(tmp_tuple.rp == rPos && tmp_tuple.cp == cPos){
                    to_set_pos = i;
                    break;
                }
            }
            if(to_set_pos == -1){
                true_value_list->insertEleAtPos(0, new_tuple);
            }
            else{
                true_value_list->setEleAtPos(to_set_pos, new_tuple);
            }

        }
        T getEntry(int rPos, int cPos){
            int list_len = true_value_list->getLength();
            for(int i=0;i<list_len;i++){
                TriTuple<T> tmp_tuple = true_value_list->getEleAtPos(i);
                if(tmp_tuple.rp == rPos && tmp_tuple.cp == cPos){
                    return tmp_tuple.value;
                }
            }
            return 0;
        }
        SparseMatrix<T> * add(SparseMatrix<T> * B){

        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){

        }

        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.

        }


        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){

        }

        //This is for printing only non-zero entries
        void printNZMatrix(){

        }
};

/* UPLOAD END */

int main(){
    SparseMatrix<int> X, Y;
    X.setEntry(1,3,4);
    X.setEntry(7,8,2);
    Y.setEntry(1,6,4);
    Y.setEntry(1,3,4);
    Y.setEntry(7,7,2);
    X.printMatrix();
    cout << endl;
    Y.printMatrix();
    cout << endl;
    X.add(&Y)->printMatrix();
    cout << endl;
    X.subtract(&Y)->printMatrix();


    Y.multiply(&X)->printMatrix();
    return 0;
}
