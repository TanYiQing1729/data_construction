#include <iostream>
using namespace std;

int main(){

    int L = 0;
    cin >> L;

	int m;
    bool A[1000];
	bool *p = A;
    for(m=0;m<1000;m++){
        *p = 1;
        p++;
    }

    A[0] = 0;
    A[1] = 0;

    int i = 0;
    int j = 0;
    int k = 0;
    for(i=2;i<=37;i++)
    {
        if(A[i]==1){
            for(j=i*i;j<1000;j=j+i)
            {
                A[j] = 0;
            }
        }

    }

    int a = 0;
    int b = 0;
    int c = 0;
    int sum = 0;

    for(k=2;k<1000;k++)  //数组不能越界访问
    {
        if(A[k]==1){
            c=k%10;
            b=(k%100-c)/10;
            a=k/100;
            sum = a + b + c;
            if(sum%L!=0){
                cout<<k<<endl;
            }
        }
    }

    return 0;


}

