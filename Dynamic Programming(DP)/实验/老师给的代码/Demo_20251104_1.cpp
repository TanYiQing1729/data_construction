#include <iostream>
#include <time.h>
using namespace std;

int fib_num_NR(int k){ // 下到上
    // find k-th fib number, starting with fib(1) = 1, fib(2) = 1 and fib(k) = fib(k-1) + fib(k-2)
    // assume k>=1.
    if(k<=2) return 1;
    int Fn1=1,Fn2=1;
    for(int i=3;i<=k;i++){
        int Fn = Fn1+Fn2; // F_n = F_{n-1} + F_{n-2}
        Fn2 = Fn1; // F_{n-1} 记在原本的 F_{n-2}
        Fn1 = Fn; // F_n 记在原本的F_{n-1}
    }
    return Fn1;
}

int fib_num_R(int k){
    if(k<=2) return 1;
    else return fib_num_R(k-1) + fib_num_R(k-2);
}

int x[100];
int fib_num_R_M(int k){ // 上到下
    if(k<=2) return 1;
    if(x[k]!=-1) return x[k];
    x[k] = fib_num_R_M(k-1) + fib_num_R_M(k-2);
    return x[k];
}

int main(){
    for(int i=0;i<100;i++)
        x[i] = -1;
    x[0] = 0;
    x[1] = 1;
    x[2] = 1;

    cout << fib_num_NR(40) << " " << fib_num_R(40) << " " << fib_num_R_M(40) << endl;

    cout << endl << "Calculating 40-th Fib num 10 times:" << endl << "Fib num (non-recursive): ";
    clock_t start = clock();
    for(int i=0;i<10;i++){
        fib_num_NR(40);
    }
    clock_t end = clock();
    double timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Fib num (recursive): ";
    start = clock();
    for(int i=0;i<10;i++){
        fib_num_R(40);
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Fib num (recursive + memory): ";
    start = clock();
    for(int i=0;i<10;i++){
        fib_num_R_M(40);
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << endl << "Calculating 40-th Fib num 1000000 times:" << endl << "Fib num (non-recursive): ";
    start = clock();
    for(int i=0;i<1000000;i++){
        fib_num_NR(40);
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Fib num (recursive + memory): ";
    start = clock();
    for(int i=0;i<1000000;i++){
        fib_num_R_M(40);
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;
    return 0;
}
