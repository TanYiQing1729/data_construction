#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

class PancakeStack{
    private:
        int* stacksizes;
        int numCakes;
    public:
        PancakeStack(){
            stacksizes = NULL;
            numCakes = 0;
        }
        PancakeStack(int* sizes, int n){
            stacksizes = NULL;
            setStackSizes(sizes,n);
        }
        ~PancakeStack(){
            if(stacksizes!=NULL) delete [] stacksizes;
        }
        void setStackSizes(int* sizes, int n){
            if(stacksizes!=NULL) delete [] stacksizes;
            stacksizes = new int[n];
            numCakes = n;
            for(int i=0;i<n;i++){
                stacksizes[i] = sizes[i];
            }
        }
        void printsizes(){
            for(int i=0;i<numCakes;i++){
                cout << left << setw(6) << stacksizes[i];
                if(i%10==9) cout << endl;
            }
            cout << endl;
        }
        int getStackSize(){
            return numCakes;
        }
        int getSizeAtPos(int x){
            return stacksizes[x];
        }
        void flip(int k){
            // flip the cakes from stacksizes[0] through stacksizes[k] around.
            // (0,1,2,3,4,5,...,k,k+1,...,n) -> (k,k-1,...,1,0,k+1,...,n)
            int tmp = 0;
            for(int i=0;i<k-i;i++){
                tmp = stacksizes[i];
                stacksizes[i] = stacksizes[k-i];
                stacksizes[k-i] = tmp;
            }
        }
};

/* UPLOAD START */

void sortCakes(PancakeStack &x){
    // TODO
    // arrange cakes from small to large.
    int num;
    num = x.getStackSize();
    //从大往小排，也就是最大的先排好 
    int try_num = 0;//尝试次数 
    while(try_num<num){
    	int max = x.getSizeAtPos(0);
    	int max_pos = 0;
    	for(int i=0;i<num-try_num;i++){
    		if(x.getSizeAtPos(i)>max){
    			max = x.getSizeAtPos(i);
    			max_pos = i;
			}
		}
		//这样我们把最大值找出来了，接着把它翻上去
		if(max_pos == num-try_num-1){
			//如果最大的已经在它要去的位置上
			try_num++;
			continue; 
		}
		if(max_pos != num-try_num-1){
			//如果不再最顶上
			x.flip(max_pos);
			//先翻到最底下 
		} 
		x.flip(num-try_num-1); 
		try_num++;
	} 
}

/* UPLOAD END */

void test1(){
    int cakes[10] = {9,7,3,2,10,1,5,6,8,4};
    PancakeStack pcs(cakes,10);
    
    sortCakes(pcs);
    pcs.printsizes();
}

int main(){
    test1();
    return 0;
}
