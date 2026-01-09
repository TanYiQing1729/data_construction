#include <iostream>
using namespace std;

int calculate(int num){
    int a;
    int sum = 0;
    for(a=1;a<=num;a++){
        if(num%a==0){
            sum += a;
        }
    }
    return sum;
}

int abundant(int num,int sum){
    if(sum>2*num){
        return 1;
    }
    else{
        return 0;
    }
}

int perfect(int num,int sum){
    if(sum==2*num){
        return 1;
    }
    else{
        return 0;
    }
}

int deficient(int num,int sum){
    if(sum<2*num){
        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    int Max[10];
    int Min[10];

    int i,j,k,l;
    int sum = 0;
    int num_abundant[10] = {0};
    int num_perfect[10] = {0};
    int num_deficient[10] = {0};


    for(i=0;i<=9;i++){
        cin>>Min[i];
        cin>>Max[i];
        if (Max[i]<Min[i]){
            break;
        }
    }

    for(j=0;j<=i-1;j++){
            for(k=Min[j];k<=Max[j];k++)
            {
                sum = calculate(k);
                num_abundant[j] = abundant(k,sum) + num_abundant[j];
                num_perfect[j] = perfect(k,sum) + num_perfect[j];
                num_deficient[j] = deficient(k,sum) + num_deficient[j];
            }
        }

    for(l=0;l<=i-1;l++){
    cout<<"Abundant: "<<num_abundant[l]<<endl;
    cout<<"Perfect: "<<num_perfect[l]<<endl;
    cout<<"Deficient: "<<num_deficient[l]<<endl;
    }
}
