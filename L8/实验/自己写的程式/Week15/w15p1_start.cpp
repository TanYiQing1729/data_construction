#include <iostream>
#include <iomanip>
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


template <class T>
class AMinHeap{ // class T better has its comparison operators correctly overloaded
    private:
        VecList<T>* array;
        int num;
        
        //这是用于堆调整和堆构造的辅助函数
        void sift(int i){    //传入堆调整的起点(以第i个位置为根) 
        	//只需将根节点与左右子树中较小的根交换，并递归对子树调整
        	//找出左右孩子 
			int l_child = 2 * i + 1; 
			int r_child = 2 * i + 2;
			//还需要注意叶子结点，这样会更有健壮性一些，但是我估计应该不会涉及这个问题，所以我偷懒先不写 
			//找出他们之间最小的 
			while(l_child < num){
				int min = i;
				if(array->getEleAtPos(l_child) < array->getEleAtPos(min)){
					min = l_child;
				}
		        if(r_child < num && array->getEleAtPos(r_child) < array->getEleAtPos(min)){
		        	min = r_child;
				}
				//找到最小的 
		        if(min == i){
		        	break;          // 已满足堆性质
				}
				//交换
				int temp = array->getEleAtPos(i);
		        array->insertEleAtPos(i, array->getEleAtPos(min));
		        array->deleteEleAtPos(i+1);
		        array->insertEleAtPos(min, temp);
		        array->deleteEleAtPos(min+1);
		        //更新 
		        i = min;                      
		        l_child = 2 * i + 1;
		        r_child = 2 * i + 2;
			} 
			 
		}
    public:
        AMinHeap(){
        	num = 0;
            array = new VecList<T>(); 
        }
        AMinHeap(T* arr, int n){
            num = n;
            array = new VecList<T>(arr, n);
	        for(int i = num/2 - 1; i >= 0; --i){
	            sift(i);
	        }
        }
        ~AMinHeap(){
            delete array;
        }
        bool isEmpty(){
            return (num==0);
        }
		//以上都比较常规

        T getMin(){
            //小根堆回传数组第一个位置
            if(isEmpty()){
            	throw "Heap Empty";
			}
			else{
				return array->getEleAtPos(0);
			}
        }
        
        void push(T x){
            //把x加入堆里，因为看做了顺序所以先写了delMin()，现在有了辅助函数写这个已经很容易了！
			//不好辅助函数用不了……
			//先加在末尾吧
			num = num + 1;
			array->insertEleAtPos(num-1, x);
			//那就是找它的双亲
			int parent;
			if((num - 1) % 2 == 0){
				parent = (num - 1 - 2) / 2;
			} 
			else{
				parent = (num - 1 - 1) / 2;
			}
			//暂存位置 
			int idx = num - 1;
			while(parent >= 0){
				if(array->getEleAtPos(idx) < array->getEleAtPos(parent)){
					T temp = array->getEleAtPos(idx);
		            array->setEleAtPos(idx, array->getEleAtPos(parent));
		            array->setEleAtPos(parent, temp);
					idx = parent;
					if(idx % 2 == 0){
						parent = (idx - 2) / 2;
					} 
					else{
						parent = (idx - 1) / 2;
					}
				}
				else{
					break;
				}
			}
        }
        
        T delMin(){
            if(isEmpty()){
            	throw "Heap Empty";
			}
			else{
				//这里的难点是堆调整，先写个辅助函数用于堆调整和堆构造  
				//先用一个temp接住最小元素 
				T temp1 = array->getEleAtPos(0);
				//用尾元素覆盖根
		        array->setEleAtPos(0, array->getEleAtPos(num-1)); 
		        //删除最后一个元素 
				array->deleteEleAtPos(num-1);                     
		        num = num - 1;
	            if(num > 0){
	            	//整个堆都要调整 
	            	sift(0);
				}
	            return temp1;
			}
        }
        T* getLevelOrderArray(){
            //把VecList类型的array给放到数组里，再空出0位置就行
			T* result =new T[num+1];
			for(int i=0;i<num;i++){
				result[i+1] = array->getEleAtPos(i);
			}
			return result; 
        }
        int getNumData(){
            return num;
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
