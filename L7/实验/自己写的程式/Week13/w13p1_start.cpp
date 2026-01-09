#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>
using namespace std;

int hash1(int x, int hashMax){
    return x % hashMax;
}

int hash2(int x, int hashMax){
    // Here, hashMax needs to be 2 mod 3.
    int tmp1 = x%hashMax;
    int tmp2 = (tmp1 * tmp1) % hashMax;
    tmp2 = (tmp2 * tmp1) % hashMax;
    return tmp2;
}

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
        void insertLast(T x){
            insertEleAtPos(length,x);
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

/* UPLOAD START */

template <class T>
class OpenHashTable{
    private:
		// other variables?
		//开散列表的意思是hashEntries中的每个元素是一个向量表 
		int tableSize;  // 哈希表大小，最好选质数以降低冲突
        int numData;   // 当前表中元素个数
        VecList<T>* hashEntries; // 存放元素的数组
        bool* inUse;    // 当前单元是否被占用（有效元素）
        int (*hashfn)(T,int); // 哈希函数指针
        int collisions = 0; // 统计插入时发生的冲突次数
    public:
        OpenHashTable(){
            //default table size set as 47
            //默认构造函数
			numData = 0;
            collisions = 0;
            tableSize = 47;    //初始为47 
            hashEntries = new VecList<T>[47];
            inUse = new bool[47];
            for(int i=0;i<47;i++){
                inUse[i] = false;
            }
            hashfn = NULL;
        }
        OpenHashTable(int table_size){
            // pray that whatever's given to us is a prime. or else things can get real ugly.
            //可指定表大小的构造函数
			numData = 0;
            collisions = 0;
            tableSize = table_size;
            hashEntries = new VecList<T>[table_size];
            inUse = new bool[table_size];
            for(int i=0;i<table_size;i++){
                inUse[i] = false;
            }
            hashfn = NULL;
        }
        ~OpenHashTable(){
            delete [] hashEntries;
            delete [] inUse;
        }
        void setHashFn(int (*f)(T, int)){
            if(hashfn==NULL)
                hashfn = f;
            else{
                cout << "Cannot reset hash function." << endl;
            }
        }
        //这些比较常规 
        bool isEmpty(){
            return (numData==0);
        }
        bool searchData(T x){
        	//先算地址 
            int address = hashfn(x,tableSize);
            //这里使用引用的方式，就不用重载运算符 
            VecList<T>& temp = hashEntries[address];
            //再在那条链里面找这个元素 
            int pos = temp.locateEle(x);
			return(!(pos == -1));
        }
        void insertData(T x){
			//先算地址 
            int address = hashfn(x,tableSize);
            //这里使用引用的方式，就不用重载运算符
            inUse[address] = 1;
            VecList<T>& temp = hashEntries[address];
            if(!temp.isEmpty()){
            	collisions++;
			}
            //最后在末尾加上元素
			temp.insertLast(x); 
			numData++;
        }
        void deleteData(T x){
            if(searchData(x)){
            	//先算地址 
	            int address = hashfn(x,tableSize);
	            //这里使用引用的方式，就不用重载运算符 
	            VecList<T>& temp = hashEntries[address];
	            //最后在末尾减去元素
				temp.deleteEleAtPos(temp.locateEle(x));
				if(temp.isEmpty()){
					inUse[address] = 0;
				}
				numData--;
			} 
        }
		void printTable(){
            for(int i=0;i<tableSize;i++){
                if(inUse[i]){
					cout << "Cell " << i << ": ";
					VecList<T>& temp = hashEntries[i];
					temp.printList();
					cout << endl;
				}
            }
        }
        int getCollisionCount(){
            return collisions;
        }
};

/* UPLOAD END */

void test1(int (*h)(int, int)){
    OpenHashTable<int> ht(23); //the table with 23 entries should be fine.
    ht.setHashFn(h);
    int randomNums[20];
    for(int i=0;i<20;i++)
        randomNums[i] = rand() % 10000;
    for(int i=0;i<20;i++){
        ht.insertData(randomNums[i]);
    }
    ht.printTable();
    cout << "Collision count: " << ht.getCollisionCount() << endl;
    cout << endl;
}

int main()
{
    srand(123456);
    test1(hash1);
	
    return 0;
}
