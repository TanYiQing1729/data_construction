#include <iostream>
using namespace std;

/* UPLOAD START */

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
        int row;
        int column;
        VecList<int> a_row;
        VecList<int> a_column;
        VecList<T> a_data;
    public:
        SparseMatrix(){
            // default is 10 rows, 10 columns
            row = 10;
            column = 10;
        }
        SparseMatrix(int r, int c){
            row = r;
            column = c;
        }
        ~SparseMatrix(){
        }
        void setEntry(int rPos, int cPos, T x){
            bool find = 0;
            int pos = -1;   //储存i 
			for(int i=0;i<a_row.getLength();i++){
            	if(a_row.getEleAtPos(i)==rPos && a_column.getEleAtPos(i)==cPos){
					pos = i;
					find = 1;
					break;
				}
			}
			if(find == 1){
				if(x != 0){
					a_data.setEleAtPos(pos, x);
				}
				else{
					a_row.deleteEleAtPos(pos);
					a_column.deleteEleAtPos(pos);
					a_data.deleteEleAtPos(pos);
				}
			}
			else{
				if(x != 0){
					a_row.insertEleAtPos(0, rPos);
					a_column.insertEleAtPos(0, cPos);
					a_data.insertEleAtPos(0, x);
				}
			}
        }
        T getEntry(int rPos, int cPos){
            for(int i=0;i<a_row.getLength();i++){
            	if(a_row.getEleAtPos(i)==rPos && a_column.getEleAtPos(i)==cPos){
					return a_data.getEleAtPos(i);
				}
        	}
        	return 0;
    	}
        SparseMatrix<T> * add(SparseMatrix<T> * B){
            if(row==B->row && column==B->column){
            	int result_row = row;
            	int result_column = column;
            	SparseMatrix* result = new SparseMatrix(result_row, result_column);
				bool change = 0;
				
				//初始化 
				for(int i=0;i<a_row.getLength();i++){
					result->setEntry(a_row.getEleAtPos(i), a_column.getEleAtPos(i), a_data.getEleAtPos(i));
				}
				
				for(int j=0;j<B->a_row.getLength();j++){
            		change = 0;
					for(int i=0;i<a_row.getLength();i++){
						if(a_row.getEleAtPos(i)==B->a_row.getEleAtPos(j) && 
						   a_column.getEleAtPos(i)==B->a_column.getEleAtPos(j)){
						   	T result_data = a_data.getEleAtPos(i) + B->a_data.getEleAtPos(j);
							result->setEntry(a_row.getEleAtPos(i), a_column.getEleAtPos(i), result_data);
							change = 1;
							break;
						   }
					}
					if(change == 0){
						result->setEntry(B->a_row.getEleAtPos(j), B->a_column.getEleAtPos(j), B->a_data.getEleAtPos(j));
					}
				}
				return result;
			}
			else{
				throw "Matrices have incompatible sizes";
			}
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){
            if(row==B->row && column==B->column){
            	int result_row = row;
            	int result_column = column;
            	SparseMatrix* result = new SparseMatrix(result_row, result_column);
				bool change = 0;
				
				//初始化 
				for(int i=0;i<a_row.getLength();i++){
					result->setEntry(a_row.getEleAtPos(i), a_column.getEleAtPos(i), a_data.getEleAtPos(i));
				}
				
				for(int j=0;j<B->a_row.getLength();j++){
            		change = 0;
					for(int i=0;i<a_row.getLength();i++){
						if(a_row.getEleAtPos(i)==B->a_row.getEleAtPos(j) && 
						   a_column.getEleAtPos(i)==B->a_column.getEleAtPos(j)){
						   	T result_data = a_data.getEleAtPos(i) - B->a_data.getEleAtPos(j);
							result->setEntry(a_row.getEleAtPos(i), a_column.getEleAtPos(i), result_data);
							change = 1;
							break;
						   }
					}
					if(change == 0){
						result->setEntry(B->a_row.getEleAtPos(j), B->a_column.getEleAtPos(j), -B->a_data.getEleAtPos(j));
					}
				}
				return result;
			}
			else{
				throw "Matrices have incompatible sizes";
			}
        }
        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
            if (column != B->row) {
            	throw "Matrices have incompatible sizes";
        	}
        	int result_row = row;
            int result_column = B->column;
            SparseMatrix* result = new SparseMatrix(result_row, result_column);
            
            //考虑A的每个元素会对矩阵的哪些位置做出贡献，如果A的一个元素位置是(1,2)，
			//那么它对result矩阵的第1行都有贡献，即相同行都有贡献
			//如何贡献的呢，靠与B的第2行的元素相乘 
            
            for(int i=0;i<a_row.getLength();i++){
            	for(int j=0;j<B->a_column.getLength();j++){
            		if(a_column.getEleAtPos(i)==B->a_row.getEleAtPos(j)){
            			T temp = a_data.getEleAtPos(i)*B->a_data.getEleAtPos(j);
            			T current = result->getEntry(a_row.getEleAtPos(i),B->a_column.getEleAtPos(j));
            			result->setEntry(a_row.getEleAtPos(i), B->a_column.getEleAtPos(j), current + temp);
					} 
				}
			}
			
			return result;
        }
        
        
        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
            for(int i=0;i<row;i++){
            	for(int j=0;j<column;j++){
            		T value = 0;
            		for(int k=0;k<a_row.getLength();k++){
            			if(a_row.getEleAtPos(k) == i && a_column.getEleAtPos(k) == j){
                    		value = a_data.getEleAtPos(k);
                    		break;
                    	}
					}
					cout<<value<<" ";
				}
				cout<<endl;
			}
        }
        
        //This is for printing only non-zero entries
        void printNZMatrix(){
            //先从小到大排序
			int n = a_row.getLength();
			for(int i=0;i<n-1;i++){
				for(int j=0;j<n-i-1;j++){
					if(a_row.getEleAtPos(j)>a_row.getEleAtPos(j+1) ||
					(a_row.getEleAtPos(j) == a_row.getEleAtPos(j+1) && a_column.getEleAtPos(j) > a_column.getEleAtPos(j+1))
					){
						int temp1 = 0;
						temp1 = a_row.getEleAtPos(j);
						a_row.setEleAtPos(j, a_row.getEleAtPos(j+1));
						a_row.setEleAtPos(j+1, temp1);
						int temp2 = 0;
						temp2 = a_column.getEleAtPos(j);
						a_column.setEleAtPos(j, a_column.getEleAtPos(j+1));
						a_column.setEleAtPos(j+1, temp2);
						T temp3 = 0;
						temp3 = a_data.getEleAtPos(j);
						a_data.setEleAtPos(j, a_data.getEleAtPos(j+1));
						a_data.setEleAtPos(j+1, temp3);
					}
				}
			}
			
			for(int i=0;i<a_row.getLength();i++){
				cout<<a_row.getEleAtPos(i)<<" "<<a_column.getEleAtPos(i)<<" "<<a_data.getEleAtPos(i)<<endl;
			}  
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
    cout << endl;
    
    Y.multiply(&X)->printMatrix();
    return 0;
}
