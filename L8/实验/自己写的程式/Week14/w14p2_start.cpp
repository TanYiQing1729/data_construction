#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */

int maxQuadProduct(int* arr, int n){
    // TODO
    int temp1 = 0;    //用于排序暂存 
    int temp2 = 0; 
	//先用一个插入排序把顺序排成正序 
	for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] < arr[j]){
                temp1 = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp1;
            }
            else
                break;
        }
    }
/*
    //检验排序
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	} 
*/
	//可能有负负得正
	int pre1 = arr[0] * arr[1] * arr[n-1] * arr[n-2];
	int pre2 = arr[0] * arr[1] * arr[2] * arr[3];    //艹之前0123写成0134了 
	int pre3 = arr[n-1] * arr[n-2] * arr[n-3] * arr[n-4];
	int result;
	if(pre1 > pre2){
		if(pre1 > pre3){
			result = pre1;
		}
		else{
			result = pre3;
		}
	}
	else{
		if(pre2 > pre3){
			result = pre2;
		}
		else{
			result = pre3;
		}
	}
	return result;
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
