#include <iostream>
using namespace std;

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
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

int* generateRandom(int num, int min, int max){ //generate random numbers between min and max, inclusive
    int* tmp = new int[num];
    for(int i=0;i<num;i++)
        tmp[i] = rand() % (max+1-min) + min;
    return tmp;
}

template <class T>
T* dupArray(T* arr, int n){
    T* tmp = new T[n];
    for(int i=0;i<n;i++){
        tmp[i] = arr[i];
    }
    return tmp;
}

template <class T>
struct MultiKey{
    T* keys;
    int keylength;
};

/* UPLOAD START */

template <class T>
void radixDesc(MultiKey<T>** mk, int n, int keylen, int low, int high){
    // mk is an array of MultiKey<T>*
    // n = number of items in mk.
    //key[0] most important, key[1] second most important
    // low and high inclusive
    // TODO
    //我理解成先排最高位，再排次高位…… 
    //先把桶写出来，这是一个数组，每个元素是一个链队列，0-9所以是10个桶 
/*debug
	//print results
	for(int i=0;i<40;i++){
	    for(int j=0;j<5;j++){
	        cout << mk[i]->keys[j];
	    }
	    cout << " ";
	    if(i%10==9) cout << endl;
	}
	cout<<endl;
*/
    LinkQueue<MultiKey<T>*> bucket[high - low + 1];
    
    for(int i=keylen-1;i>=0;i--){
    	//排第i位
		//遍历所有mk，进桶 
		for(int j=0;j<n;j++){
			//要减去low不然对于不是0开头的就越界了 
			bucket[mk[j]->keys[i] - low].enQueue(mk[j]);
		}
		
		//按顺序重新赋值给mk
		int idx = 0;    //给mk的增量 
		for(int k=high;k>=low;k--){
			while(!bucket[k - low].isEmpty()){
				mk[idx] = bucket[k - low].deQueue();
				idx++;
			} 
		}
/*debug
		//print results
	    for(int i=0;i<40;i++){
	        for(int j=0;j<5;j++){
	            cout << mk[i]->keys[j];
	        }
	        cout << " ";
	        if(i%10==9) cout << endl;
	    }
	    cout<<endl;
*/
	}
    
}

/* UPLOAD END */

int simpleTest(){
    srand(7654321);
    MultiKey<int>** mk = new MultiKey<int>*[40];
    for(int i=0;i<40;i++){
        mk[i] = new MultiKey<int>;
        mk[i]->keys = generateRandom(5,0,9);
        mk[i]->keylength = 5;
    }
    
    radixDesc(mk,40,5,0,9);
    
    //print results
    for(int i=0;i<40;i++){
        for(int j=0;j<5;j++){
            cout << mk[i]->keys[j];
        }
        cout << " ";
        if(i%10==9) cout << endl;
    }
    
    return 0;
}

int main(){
    simpleTest();
    return 0;
}
