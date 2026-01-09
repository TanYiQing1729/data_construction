#include <iostream>
using namespace std;

int main(){

    int i,j;
    int N;

    cin>>N;

    bool A[N+1];
    for(i=0;i<N+1;i++){
        A[i] = 1;
    }
    A[0] = 0;
    A[1] = 0;

    for(i=2;i*i<=N+1;i++){
        for(j=i*i;j<N+1;j+=i){
            A[j] = 0;
        }
    }
//以上步骤是在选出素数

	
    int count = 0;
    for (int i = 2; i <= N; i++) {
        if (A[i]) {
            count++;
        }
    }


	int p[count];
    int k = 0;
    for (int i = 2; i <= N; i++) {
        if (A[i]) {
            p[k++] = i;
        }
    }

    bool B[N+1] = {0};

    // 生成半素数
    for (int i = 0; i < count; i++) {
        for (int j = i; j < count; j++) {
            int product = p[i] * p[j]; 
            if (product > N) {
                break; 
            }
            B[product] = true;
        }
    }
    
    for (int i = 2; i <= N; i++) {
        if (B[i]==1) {
            A[i] = 1;
        }
    }


    for (int i = 2; i <= N; i++) {
        if (A[i]==1) {
            cout << i << endl;
        }
    }
}
