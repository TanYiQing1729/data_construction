#include <iostream>
#include <iomanip>
#include <stdlib.h> // for srand and rand

using namespace std;

template <class T>
class ArrayWrap{
    private:
        int length;
        T* baseArray;
        mutable int readCount; // mutable to allow modification in const functions
        //mutable 允许在 const 函数中修改
    public:
        ArrayWrap(){ // never actually used
            length = 0;
            baseArray = NULL;
            readCount = 0;
        }
        ArrayWrap(T* arr, int n){
            length = n;
            baseArray = arr;
            readCount = 0;
        }
        int getLength(){
            return length;
        }
        int getReadCount(){
            return readCount;
        }
        T& operator[](int pos){
            readCount++;
            return baseArray[pos];
        }
        const T& operator[](int pos) const{
            readCount++;
            return baseArray[pos];
        }
};

/* UPLOAD START */
// ques 1
int missingAPterm(ArrayWrap<int> &aw){
    // Requirement: runtime efficiency should be O(ln n)
    // This will be observed via readCount.
    // TODO
	 
    //初始化指针和相关量 
    int length = aw.getLength();
    int low = 0;
    int high = length - 1;
    int mid = (low + high)/2;
    int d;    //公差
	d = (aw[high] - aw[low])/length;
	
	//开始二分查找，思路是检查aw[mid]-aw[low]是否为d的mid-low的倍数，
	//是的话就去找>mid，不是就找<mid 
	while(low + 1 != high){
		if(aw[mid] - aw[low] == d * (mid - low)){
			low = mid;
			mid = (low + high)/2;
		}
		else{
			high = mid;
			mid = (low + high)/2;
		} 
	}
	
	//现在low指向缺失值的前一位，high指向缺失值的后一位
	return aw[low] + d; 
	
}
/* UPLOAD END */

/* UPLOAD START */
// ques 2
int maxEleBitonic(ArrayWrap<int> &aw){
    // Requirement: runtime efficiency should be O(ln n)
    // This will be observed via readCount.
    // TODO
    
    //我感觉我的思路可能比较邪修，我先搞清楚数据的分布情况
	//在这之前先做一些初始化 
	//初始化指针和相关量 
    int length = aw.getLength();
    int low = 0;
    int high = length - 1;
    int mid = (low + high)/2;
    
    //严格降序 
	if(aw[0] - aw[1] > 0 && aw[length-2] - aw[length-1] > 0){
		return aw[0];
	} 
	//严格升序
	else if(aw[0] - aw[1] < 0 && aw[length-2] - aw[length-1] < 0){
		return aw[length-1];
	}  
    //先降再升 
	else if(aw[0] - aw[1] > 0 && aw[length-2] - aw[length-1] < 0){
		if(aw[0] > aw[length-1]){
			return aw[0];
		}
		else{
			return aw[length-1];
		}
	}
    //最难写的，先升再降
    //判断标准就是看mid的左右两边的增长情况
	//同增找右边，同减找左边，增减就找到了 
	else{
		while(low + 1 != high){
			if(aw[mid-1] - aw[mid] < 0 && aw[mid] - aw[mid+1] > 0){
				return aw[mid]; 
			}
			else if(aw[mid-1] - aw[mid] < 0 && aw[mid] - aw[mid+1] < 0){
				low = mid;
				mid = (low + high)/2; 
			}
			else{
				high = mid;
				mid = (low + high)/2;
			} 
		}
	}
	
}
/* UPLOAD END */

void test0(){
    // demonstrates usage of the class ArrayWrap
    int a[10];
    for(int i=0;i<10;i++){
        a[i] = i;
    }
    ArrayWrap<int> aw(a,10);
    int sum = 0;
    for(int i=0;i<aw.getLength();i++){
        sum += aw[i];
        aw[i] += 10;
    }
    cout << "Sum is " << sum << ", readCount is " << aw.getReadCount() << endl;
    for(int i=0;i<aw.getLength();i++){
        cout << aw[i] << " ";
    }
    cout << endl << "New readCount is " << aw.getReadCount() << endl;
}

void test1(){ // ques 1 test
    int a[10] = {1,3,5,7,9,13,15,17,19,21};
    int b[70];
    b[0] = 4;
    b[1] = 18;
    for(int i=2;i<70;i++){
        b[i] = b[i-1]+7;
    }
    
    ArrayWrap<int> aw1(a,10);
    ArrayWrap<int> aw2(b,70);
    
    cout << "Missing term for first sequence: " << missingAPterm(aw1);
    cout << ", readCount = " << aw1.getReadCount() << endl;
    cout << "Missing term for second sequence: " << missingAPterm(aw2);
    cout << ", readCount = " << aw2.getReadCount() << endl;
}

void test2(){ // ques 2 test
    int a[10] = {1,3,7,9,11,10,9,7,4,-1};
    int b[50];
    for(int i=0;i<50;i++){
        b[i] = i;
    }
    
    ArrayWrap<int> aw1(a,10);
    ArrayWrap<int> aw2(b,50);
    
    int d[1000];
    d[0] = 0;
    for(int i=1;i<1000;i++){
        d[i] = d[i-1] + 15;
        if(i==300) d[i]+= 15;
    }
    
    ArrayWrap<int> aw4(d,1000);
    
    cout << "Max term in first sequence: " << maxEleBitonic(aw1);
    cout << ", readCount = " << aw1.getReadCount() << endl;
    cout << "Max term in second sequence: " << maxEleBitonic(aw2);
    cout << ", readCount = " << aw2.getReadCount() << endl;
    
    // Stress Test
    cout << "Max term in third sequence: " << maxEleBitonic(aw4);
    cout << ", readCount = " << aw4.getReadCount() << endl;
    cout << (aw4.getReadCount() == 0 ? "Cheater " : "") << (aw4.getReadCount() < 150 ? "Passed" : "Failed") << endl;
}

int main(){
    //test0(); // test the use of class ArrayWrap
    test1();
    cout << endl;
    test2();
    
    return 0;
}
