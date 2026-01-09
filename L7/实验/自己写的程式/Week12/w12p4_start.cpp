#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

/* UPLOAD START */

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        //按照第二个构造函数输入来写 
		T* ele_list;
		int num;
		int capacity;
		//模仿向量表的变长数组 
		void doubleListSize(){
            T * old_ele_list = ele_list;
            ele_list = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<num;i++){
                ele_list[i] = old_ele_list[i];
            }
            delete [] old_ele_list;
        }
    public:
        ASet(){
            //按照空集的定义
            num = 0; 
            capacity = 100;
			ele_list = new T[capacity];
			
        }
        ASet(T* arr, int n){ //incoming array is guaranteed not to have duplicates.
            num = n;
            capacity = 100 + 2*n;
			ele_list = new T[capacity];
            for(int i=0;i<n;i++){
                ele_list[i] = arr[i];
            }
        }
        ~ASet(){
            delete [] ele_list;
        }
        void addEle(T x){
            //注意x在集合中的反例
            //容量不够就扩容
		    if (num == capacity) {
		        doubleListSize();
		    }
            
			bool judge = 0;
			for(int i=0;i<num;i++){
				if(ele_list[i] == x){
					judge = 1;
					break;
				}
			}
			if(judge == 0){
				ele_list[num] = x;
				num++;
			} 
        }
        bool isEmpty(){
            return num==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            bool judge = 0;
            int pos = 0;
			for(int i=0;i<num;i++){
				if(ele_list[i] == x){
					judge = 1;
					pos = i;
					break;
				}
			}
			if(judge == 1){
				for(int i=pos;i<num-1;i++){
					ele_list[i] = ele_list[i+1];
				}
				num--;
				return 1;
			}
			else{
				return 0;
			}
        }
        bool hasEle(T x){
            bool judge = 0;
			for(int i=0;i<num;i++){
				if(ele_list[i] == x){
					judge = 1;
					break;
				}
			}
			if(judge == 1){
				return 1;
			}
			else{
				return 0;
			}
        }
        bool isSubsetOf(ASet<T>* S){
            bool judge = 1;
			for(int i=0;i<num;i++){
            	if(!S->hasEle(ele_list[i])){
            		judge = 0;
            		break;
				}
			}
			if(judge == 1){
				return 1;
			}
			else{
				return 0;
			}
        }
        bool containsSet(ASet<T>* S){
            //从本集合中找元素，如果temp = S中也有，就删掉，如果遍历完temp变为空集，那么S是本集合的子集 
/*
			ASet<T>* temp = new ASet<T>(*S);
            for(int i=0;i<num;i++){
            	if(temp->hasEle(ele_list[i])){
            		temp->removeEle(ele_list[i]);
				}
			}
			if(temp->isEmpty()){
				return 1;
			}
			else{
				return 0;
			}
*/
			//这种写法不太合适，很容易改动别的地方
			return S->isSubsetOf(this); 
        }
        bool isDisjointFrom(ASet<T>* S){
            //有一个在本集合又在S中 
			bool judge = 0;
			for(int i=0;i<num;i++){
            	if(S->hasEle(ele_list[i])){
            		judge = 1;
            		break;
				}
			}
			if(judge == 1){
				return 0;
			}
			else{
				return 1;
			}
        }
        int cardinality(){
            return num;
        }
        ASet<T>* setUnion(ASet<T>* S){
            //新建一个集合，在S的基础上加上本集合的元素 
/* 
			原因同上 
			ASet<T>* result = new ASet<T>(*S);
            for(int i=0;i<num;i++){
            	result->addEle(ele_list[i]);
			}
			return result;
*/
			ASet<T>* result = new ASet<T>;  
		    //先把S的元素加进去
		    for (int i = 0; i < S->num; ++i) {
		        result->addEle(S->ele_list[i]);
		    }
		    //再把this的元素加进去
		    for (int i = 0; i < num; ++i) {
		        result->addEle(ele_list[i]);
		    }
		    return result;
			
        }
        ASet<T>* intersect(ASet<T>* S){
        	//新建一个集合，如果本集合的元素也在S中，就加入集合 
            ASet<T>* result = new ASet<T> ;
            for(int i=0;i<num;i++){
            	if(S->hasEle(ele_list[i])){
            		result->addEle(ele_list[i]);
				}
			}
			return result;
        }
        ASet<T>* subtract(ASet<T>* S){
        	//新建一个集合，如果本集合的元素不在S中，就加入集合
            ASet<T>* result = new ASet<T> ;
            for(int i=0;i<num;i++){
            	if(!S->hasEle(ele_list[i])){
            		result->addEle(ele_list[i]);
				}
			}
			return result;
        }
        ASet<T>* symDiff(ASet<T>* S){
/*
			同上 
			//新建一个集合，如果本集合的元素不在S中，就加入集合
			ASet<T>* temp1 = new ASet<T>();
			ASet<T>* result = new ASet<T>;
            for(int i=0;i<num;i++){
            	if(!S->hasEle(ele_list[i])){
            		temp1->addEle(ele_list[i]);
				}
			}
			//然后把在S中而不在本集合中的元素加入，采用和判断S是不是本集合的子集的类似做法
			ASet<T>* temp2 = new ASet<T>(*S); 
			for(int i=0;i<num;i++){
            	if(temp2->hasEle(ele_list[i])){
            		temp2->removeEle(ele_list[i]);
				}
			}
			//得到的temp2应该是没有S与本集合的交集的
			//再去做并集就好了
			result = temp1->setUnion(temp2);
			return result;
*/ 
			
			ASet<T>* result = new ASet<T>;

		    //把A中不在B中的元素放进去
		    for (int i = 0; i < num; ++i) {
		        if (!S->hasEle(ele_list[i])) {
		            result->addEle(ele_list[i]);
		        }
		    }
		
		    //把B中不在A中的元素放进去
		    for (int i = 0; i < S->num; ++i) {
		        if (!this->hasEle(S->ele_list[i])) {
		            result->addEle(S->ele_list[i]);
		        }
		    }
		
		    return result;
		
        }
        void printSet(){ //print the elements of S in ascending order
            //先排序再输出
            int print[capacity];
            for(int i=0;i<capacity;i++){
            	print[i] = ele_list[i];
			}
            
			for(int i=0;i<num-1;i++){
				int min = print[i];
				int min_pos = i;
				for(int j=i+1;j<num;j++){
					if(min > print[j]){
						min = print[j];
						min_pos = j;
					}
				}
				int temp = print[i];
				print[i] = print[min_pos];
				print[min_pos] = temp;
			}
			//开始输出
			cout<<"{";
			for(int i=0;i<num;i++){
				if(i == 0){
					cout<<print[i];
					continue;
				}
				cout<<","<<print[i];
			}
			cout<<"}"<<endl; 
        }
};

/* UPLOAD END */

void simpleTest(){
    ASet<int> A;
    for(int i=1;i<=4;i++){
        A.addEle(i);
    }
    cout << "Set A: ";
    A.printSet();
    cout << "Cardinality of A: " << A.cardinality() << endl << endl;
    
    int tmpB[4] = {3,6,5,4};
    ASet<int> B(tmpB,4);
    cout << "Set B: ";
    B.printSet();
    cout << "Cardinality of B: " << B.cardinality() << endl << endl;
    
    ASet<int>* C = A.intersect(&B);
    ASet<int>* D = A.subtract(&B);
    
    cout << "Intersecting A and B gets set C, ";
    C->printSet();
    cout << "Union of A and B is ";
    (A.setUnion(&B))->printSet();
	cout << "Let set D be the set of elements in A but not B. Then set D is ";
    D->printSet();
    
	cout << "Symmetric difference of A and B is ";
	(A.symDiff(&B))->printSet();
    
    cout << endl << "Checking subset relations:" << endl;
    cout << "A " << (A.containsSet(C) ? "contains" : "does not contain") << " set C" << endl;
    cout << "B " << (B.containsSet(D) ? "contains" : "does not contain") << " set D" << endl;
    cout << "C is " << (C->isSubsetOf(&A) ? "" : "not ") << "a subset of A" << endl;
    cout << "D is " << (D->isSubsetOf(&B) ? "" : "not ") << "a subset of B" << endl;
}

int main(){
    simpleTest();
    return 0;
}
