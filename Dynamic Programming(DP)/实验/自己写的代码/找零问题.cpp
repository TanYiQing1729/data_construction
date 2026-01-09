#include <iostream>
#include <stdlib.h>

using namespace std;

/* Question 5 UPLOAD START */

class coinChanger{
    private:
        int* set;
        int length;
        int dp[1100];
    public:
        coinChanger(){
            // not used
        }
        coinChanger(int* coinValueSet, int n){
            set = new int[n];
            length = n;
            for(int i=0;i<n;i++){
            	set[i] = coinValueSet[i];
			}
			for(int i=0;i<1100;i++){
				dp[i] = -2;
			}
			dp[0] = 0;
        }
        ~coinChanger(){
            delete[] set;
        }
        int numCoinsToMakeChange(int target){
            // limit target to be <= 1000;
            // return -1 if impossible.
            
            //step1:确定dp数组和下标含义
			//dp[i]表示找i元所需的最小币数
			
			//step2：递推公式
			//dp[i] = 1 + min{dp[i-set[j]]} or -1
			
			//step3：初始化
			//我们希望dp数组能够一直被使用，而不是作为局部变量被更新，所以我们把dp数组在private里面定义
			//在构造函数中完成初始化 
			//dp[0] = 0, 用-2表示未计算，-1表示无解 
			//其他的得要看币的种类了
			
			//step4：这次是从大到小遍历 
            
            //step5：先不搞 

			if(target == 0){
				return 0;
			}
			
			if(dp[target] != -2){
				return dp[target];
			}
			
			
			//接下来采用类似递归的方式来写
			bool found = 0;
			int min_coin = target + 1;    //不可能用超过target种方法来找钱,但是要区分全是1和无解的情况 
			for(int j=0;j<length;j++){
				if(target - set[j] >= 0){
					int temp = numCoinsToMakeChange(target-set[j]);
					if(temp != -1){
						if(min_coin > temp + 1){
							min_coin = temp + 1;
							found = 1;
						}
					}
				}
			}
			 
			if(!found){
				dp[target] = -1;
			}
			else{
				dp[target] = min_coin;
			}
			return dp[target];
        }
};

/* Question 5 UPLOAD END */

void test1(){
    int coinValueSet1[4] = {1,2,5,10};
    int coinValueSet2[3] = {1,8,10};
    
    coinChanger cc(coinValueSet1,4);
    
    cout << "Using the set {1,2,5,10}, making changes for:" << endl;
    cout << "99: " << cc.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc.numCoinsToMakeChange(998) << endl;
    
    
    coinChanger cc2(coinValueSet2,3);
    cout << "Using the set {1,8,10}, making changes for: " << endl;
    cout << "16: " << cc2.numCoinsToMakeChange(16) << endl;
    cout << "24: " << cc2.numCoinsToMakeChange(24) << endl;
    cout << "32: " << cc2.numCoinsToMakeChange(32) << endl;
    cout << "99: " << cc2.numCoinsToMakeChange(99) << endl;
    cout << "98: " << cc2.numCoinsToMakeChange(98) << endl;
    cout << "579: " << cc2.numCoinsToMakeChange(579) << endl;
    cout << "998: " << cc2.numCoinsToMakeChange(998) << endl;
}

int main(){
    test1();
    return 0;
}
