//整数分拆final 

#include <iostream>
using namespace std;

//法一：递归
/*
int set[50];    //储存某一个节点前已经拆出来的数 

//这个函数是用来计算的，指的是对n用不大于m的数字进行拆分，并用store表示set已经存储了多少位数 

void print(int n, int m, int store){
	if (n == 0){                          //终止条件，n=0，此时进行输出与换行 
		for(int i=0;i<store-1;i++){
			cout<<set[i]<<"+";
		}
		if (store > 0){
			cout<<set[store-1];
		}
		cout<<endl;
		return;
	}
	
	for(int i=m;i>0;i--){                //从m开始，依次递减，用不小大i的数字去拆 
		if(i<=n){						 //对n先拆出一个i，再递归到(n-i, i)的情况 
			set[store] = i;				 //注意它其实是有两条递归路径的，还有个是(n, i-1)
			print(n-i,i,store+1);        //但是已经在外层循环遍历 
		}
	}
}

int main(){
	int N=100;
	cin>>N;
	print(N,N,0);	
} 
*/ 

//法二：非递归
/*
总得来说，它应该是至少有两层循环的，最外层的终止条件就是拆出来的数字全是1
剩下的逻辑就是，从后往前找到第一个＞1的数字，将它减1分给后面，后面求和再重新分配 
*/

int main(){
	int n=100;
	int length = 1;
//	cin>>n;
	int set[n];
	set[0]=n;     //初始化
	
	while(true){
		for(int i=0;i<length;i++){
			if(i>0)
				cout<<"+";
			cout<<set[i];
        }                                    //输出 
        cout<<endl;
		
		if(set[0]==1)
			break;       //外层循环的终止条件 
		
		int sum = 1;
		for(int i=length-1;i>=0;i--){
			if(set[i]!=1){
				set[i] -= 1;                   //找到第一个＞1的数字，将它减1                 
				for(int j=i+1;j<length;j++){
					sum += set[j];             //计算在它后面可以重新调整的量 
				}
				//开始重新分配，逻辑是递减且第i位小于等于第i-1位，
				//且该方法是在所有方法中可分配的首位的数字最大的 
				length = i + 1;
				while(sum>0){
					if(sum>=set[i]){        //大于等于直接给seti 
						set[length] = set[i];
						sum -= set[i];
					}
					else{				   //小于给sum全部 
						set[length] = sum;
						sum = 0;
					}
					length++;
				}
				break;
			}
		}
		
	} 
} 
 
