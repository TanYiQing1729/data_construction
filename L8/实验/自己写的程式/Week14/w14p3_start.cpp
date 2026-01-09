#include <iostream>
using namespace std;

/* UPLOAD START */

int longestSubsequenceLength(int* arr, int n){
    //动态规划问题
	//step1：dp数组的表示 
	//dp[i]表示从0到i的最长递增子序列的长度
	//step2: 递推公式
	//思考什么时候会增加，有一个比较容易注意到的条件：第i个位置比之前大就行了。但是比谁大呢
	//因为不要求连续，所以对于第i位之前的所有位置dp[j]，如果满足上述条件一定变成dp[j]+1
	//那么只要取最大就行了，即max(dp[j]+1) 
	//step3：初始化
	//长度为1的数组这个子序列长度为1，即dp[0] = 1;
	//step4：遍历顺序
	//显然从小到大
	
	//记得n == 0的情况
	if(n == 0){
		return 0;
	} 
	
	int dp[n];
	
	dp[0] = 1;    //初始化
//	cout<<dp[0]<<" ";    //debug
	
	for(int i=0;i<n;i++){     
		int max = 1;    //非常重要！dp数组最小值是1，所以max初始化成0就一堆进不了if的变成0了 
		for(int j=0;j<i;j++){
			if(arr[i] > arr[j]){    //增加条件 
				if(max < dp[j] + 1){
					max = dp[j] + 1;    //更新 
				}
			}
		} 
		dp[i] = max;
//		cout<<dp[i]<<" ";    //debug
	} 
	
	return dp[n-1];
	 
}

/* UPLOAD END */

void test1(){
    int a[8] = {10,9,2,5,3,7,101,18};
    cout << longestSubsequenceLength(a,8) << endl; //4
}

void test2(){
    int a[7] = {1,2,3,5,3,7,8};
    cout << longestSubsequenceLength(a,7) << endl; //6
}

int main(){
    test1();
    test2();
    return 0;
}
