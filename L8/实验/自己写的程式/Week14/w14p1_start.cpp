#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

void mergeIntervals(int** arr, int n){
    /* The first interval is arr[0][0] to arr[0][1]
       The 2nd interval is arr[1][0] to arr[1][1]
       ...
       The last interval is arr[n-1][0] to arr[n-1][1]
       Print the results of merging these intervals. Assume endpoints are always included.
    */
    
	// n==0：直接输出换行
    if(n == 0){
        cout << endl;
        return;
    }
	
	int temp1 = 0;    //用于排序暂存 
    int temp2 = 0; 
	//先用一个插入排序把顺序排成正序 
	for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1][0] < arr[j][0]){
                temp1 = arr[j][0];
                arr[j][0] = arr[j+1][0];
                arr[j+1][0] = temp1;
                temp2 = arr[j][1];
                arr[j][1] = arr[j+1][1];
                arr[j+1][1] = temp2;
            }
            else
                break;
        }
    }
/*
    //输出检验 
    for(int i=0;i<n;i++){
    	for(int j=0;j<2;j++){
    		cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
*/
/* 
	int idx = 0;    //用于循环的外指针
//	int temp_num = 0;    //用于检查的变量 
	while(idx < n){    //外指针不越界 
		if(idx != 0){
			cout<<",";   //除了第一次先输出“，”
//			cout<<idx;    //用于debug 
		}
		if(idx == n-1){ 
			cout<<"["<<arr[idx][0]<<","<<arr[idx][1]<<"]";
			idx++;
		}
		for(int i=idx+1;i<n;i++){
			if(arr[idx][1] >= arr[i][0] && i == n-1){ 
				cout<<"["<<arr[idx][0]<<","<<arr[i][1]<<"]";
				idx = i+1;
				break;
			}
			if(arr[idx][1] >= arr[i][0]){
				continue;
			}
			if(arr[idx][1] < arr[i][0] && i == n-1){
				cout<<"["<<arr[idx][0]<<","<<arr[i-1][1]<<"]";
				idx = i;
				break;
			}
			if(arr[idx][1] < arr[i][0]){
				cout<<"["<<arr[idx][0]<<","<<arr[i-1][1]<<"]";
				idx = i;
				break;
			}
		}
//		temp_num++;
	} 
*/

	//上面的太屎山了，大概思路不太对
	int curL = arr[0][0];    //存储输出的区间
    int curR = arr[0][1];    //存储输出的区间 
    bool first = 1;    //用于输出逗号 
    
    for(int i=1;i<n;i++){
    	int L = arr[i][0];
		int R = arr[i][1];
		if(L <= curR){    //可以吃掉，再看右端点是怎样的 
			if(R > curR){
				curR = R;	
			}
		}
		else{
			if(!first){    //不是第一个 
				cout<<",";
			}
			first = 0; 
			cout<<"["<<curL<<","<<curR<<"]";
			curL = L;
			curR = R;    //更新输出区间 
		}
	} 
	
	//如果没有吃掉区间，也要输出
	if(!first){    //不是第一个 
		cout<<",";
	}
	cout<<"["<<curL<<","<<curR<<"]";
	cout<<endl;
}

void come_one_box(int** arr, int n){
    //不要忘记小坑
    if(n == 0){
        cout << endl;
        return;
    }
    //先把所有端点放到一个数组里，并标记0和1
    int new_arr[2*n][2]; //第一列存端点，第二列存标记
    for(int i=0;i<n;i++){
        new_arr[2*i][0] = arr[i][0];
        new_arr[2*i][1] = 0; //左端点标记为0
        new_arr[2*i+1][0] = arr[i][1];
        new_arr[2*i+1][1] = 1; //右端点标记为1
    }
    //对new_arr按第一列排序
    int temp1 = 0;
    int temp2 = 0;    //用于排序暂存
    for(int i=1;i<2*n;i++){
        for(int j=i-1;j>=0;j--){
            if(new_arr[j+1][0] < new_arr[j][0]){
                temp1 = new_arr[j][0];
                new_arr[j][0] = new_arr[j+1][0];
                new_arr[j+1][0] = temp1;
                temp2 = new_arr[j][1];
                new_arr[j][1] = new_arr[j+1][1];
                new_arr[j+1][1] = temp2;
            }
            else
                break;
        }
    }
    int count0 = 0; //记录0的个数
    int count1 = 0; //记录1的个数
    //接下来的实现方法就又很多了，我就随便写一种
    int curL = new_arr[0][0];
    bool first = 1; //用于输出逗号
    for(int i=0;i<2*n;i++){
        if(new_arr[i][1] == 0){
            count0++;
        }
        else{
            count1++;
        }
        if(count0 == count1){ //可以输出一个区间
            if(new_arr[i][0] == new_arr[i+1][0]){
            	continue;
			} 
			if(!first){
                cout << ",";
            }
            first = 0;
            cout << "[" << curL << "," << new_arr[i][0] << "]";
            if(i+1 < 2*n){
                curL = new_arr[i+1][0]; //更新curL为下一个端点
            }
        }
    }
    cout << endl;
}


/* UPLOAD END */

void test1(){
    int** a = new int*[2];
    a[0] = new int[2];
    a[1] = new int[2];
    a[0][0] = 1;
    a[0][1] = 4;
    a[1][0] = 4;
    a[1][1] = 5;
    mergeIntervals(a,2);
    come_one_box(a,2); 
    
    int** b = new int*[4];
    b[0] = new int[2]{1,3};
    b[1] = new int[2]{2,6};
    b[2] = new int[2]{8,10};
    b[3] = new int[2]{15,18};
    mergeIntervals(b,4);
    come_one_box(b,4); 
}

int main()
{
    test1();
    return 0;
}
