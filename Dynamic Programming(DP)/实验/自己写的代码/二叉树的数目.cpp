#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */

int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    
    //step1：确定dp数组和下标含义
    //dp[i]表示结点数为i时，二叉树的个数
	
	//step2：递推公式
	//用到离散数学的公式，我们可以在Catalan数与二叉树之间建立双射 
	//dp[i] = dp[0]*dp[i-1] + dp[1]*dp[i-2] + …+ dp[i-1]*dp[0] 
	
	//step3：初始化
	//定义dp[0]=1
	//dp[1]=1 
	 
	//step4:从小到大遍历
	
	//step5：懒惰了出问题再举例
	
	unsigned long long  dp[n+1] = {0};
	
	if(n==0){
		return 1;
	} 
	else if(n==1){
		return 1;
	}
	else{
		dp[0] = 1;
		dp[1] = 1;
		for(int i=2;i<=n;i++){
			unsigned long long sum = 0;
			for(int j=0;j<=i-1;j++){
				sum += (dp[j] * dp[i-1-j]);
			}
			dp[i] = sum % 30011;
		}
		return dp[n];
	}
    
}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (2*i) << ": " << numOfBinaryTrees(2*i) << endl;
    }
}

int main(){
    test();
    return 0;
}
