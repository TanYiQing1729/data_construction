#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */

int numStepsToN_v2(int N, int mod_num){
    // calculate the number of ways to get to N
    // allowed step on each move: +1, +2, +3
    // However, no two consecutive steps are the same.
    
    //step1：确定dp数组和下标含义
	//dp是一个二维数组，dp[i][j]表示爬i层时，最后一步爬了j层楼梯的方法数
	//为了方便计数，我打算循环时给它从1起算 
	
	//step2：确定递推公式
	//dp[i][1] = dp[i-1][2] + dp[i-1][3]
	//dp[i][2] = dp[i-2][1] + dp[i-2][3]
	//dp[i][3] = dp[i-3][1] + dp[i-3][2]
    
    //step3：初始化dp数组
    //这里直接看注释 
	//dp[0]反正我用不上，所以设置为1,0,0
	//dp[i][0]也全部设置成0 
	//dp[1][1] = 1, dp[1][2] = 0, dp[1][3] = 0
	//dp[2][1] = 0, dp[2][2] = 1, dp[2][3] = 0
	//dp[3][1] = 1, dp[3][2] = 1, dp[3][3] = 1
	
	//step4：确定遍历顺序
	//我觉得这个很fibonacci数列很像，应该是从小到大遍历更好一些
	
	//step5：举例推导
	//事实上注释里已经有了
	//多做的事情就是找出sum[i] = dp[i][1] + dp[i][2] + dp[i][3]
	
	//我看它的数字很大，懒得处理所以使用这种数据类型 
	//我破防了我不知道为什么它不能动态申请，所以我直接取一个超级大的数算了 
	unsigned long long dp[10000][4] = {0};
	unsigned long long sum_of_dp[10000] = {0};
	int result = 0;
	 
	//这里可以写N+1，但是问题在于初始化就要一点一点初始化，在N较小的时候dp[3][1]是越界的 
	
	//初始化 
	dp[0][1] = 1; dp[0][2] = 0; dp[0][3] = 0; 
	dp[1][1] = 1; dp[1][2] = 0; dp[1][3] = 0;
	dp[2][1] = 0; dp[2][2] = 1; dp[2][3] = 0;
	dp[3][1] = 1; dp[3][2] = 1; dp[3][3] = 1;
	sum_of_dp[0] = 1; sum_of_dp[1] = 1; sum_of_dp[2] = 1; sum_of_dp[3] = 3;
	    
	if(N==0){
    	result = sum_of_dp[0];
    	return result;
	}
	else if(N==1){
		result = sum_of_dp[1];
    	return result;
	}
	else if(N==2){
		result = sum_of_dp[2];
    	return result;
	}
	else if(N==3){
		result = sum_of_dp[3];
    	return result;
	}    
	else{
//		return 0;
		for(unsigned long long i=4;i<=N;i++){
			dp[i][1] = dp[i-1][2] + dp[i-1][3];
			dp[i][2] = dp[i-2][1] + dp[i-2][3];
			dp[i][3] = dp[i-3][1] + dp[i-3][2];
			sum_of_dp[i] = dp[i][1] + dp[i][2] + dp[i][3];
		}
		result = sum_of_dp[N] % mod_num;
		return result;
	}
	
    
}

/* Question 1 UPLOAD END */

int main(){

    for(int i=0;i<=10;i++)
        cout << i << ": " << numStepsToN_v2(i,9999999) << endl;
    return 0;
}

/*
0: 1
1: 1
2: 1
3: 3
4: 3
5: 4
6: 8
7: 9
8: 12
9: 21
10: 27
*/
