#include <iostream>
using namespace std;

/* Question 3 UPLOAD START */
int numOfFriendPairs(int n){
    // return the number of pairings with n people mod 10000019
    // max of n will be 150 in this problem
    
    //我感觉我可以不用写注释直接写了
	//但是这个题有个坑，1+2=2+1 
	//这个解决起来也不难，给它加上顺序就行了 
	//上面说的不对
	//每个学生是不一样的，这代表并不是重复了，而是缺少了
	//具体来说，3个人有：abc，a+bc，b+ac，c+ab 
	//所以递推公式是：dp[i] = dp[i-1] + dp[i-2]*(i-1)  后一项的意思是与其中的任意一个人组队，然后剩下i-2人的情况 
	
	
	int dp[n+1] = {0};
	
	if(n==0){
		return 1;
	}
	else if(n==1){
		return 1;
	} 
    else if(n==2){
    	return 2;
	}
	else{
		dp[0] = 1;
		dp[1] = 1;
		dp[2] = 2;
		for(int i=3;i<=n;i++){
			dp[i] = (dp[i-1] + (i-1) * dp[i-2])%10000019;
		}
		return dp[n];
	}
    
}
/* Question 3 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (3*i) << ": " << numOfFriendPairs(3*i) << endl;
    }
}

int main(){
    test();
    return 0;
}
