#include <iostream>
using namespace std;
/*                         how many kinds of situation
int count(int n, int m){
	if(n == 1 || m == 1){
		return 1;
	}
	else if(n == m){
		return 1+count(n, m-1);
	}
	else if(n < m){
		return count(n, n);
	}
	else if(n > m){
		return count(n-m,m)+count(n, m-1);
	}
} 

int main(){
	int N;
	cin>>N;
	cout<<count(N,N);
}    */

int k;
int set[50];

void print(int n, int m, int temp) {
    if(n == 0) {
        for(int i = 0; i < temp-1; i++) {
            cout << set[i] << "+";
        }
        if(temp > 0) {
            cout << set[temp-1];
        }
        cout << endl;
        return;
    }
    
    
    for(int i = m; i >= 1; i--) {
        if(i <= n) { 
            set[temp] = i; 
            print(n - i, i, temp + 1); 
        }
    }
}

int main() {
    int N = 100;
//    cin >> N;
    k = N;
    print(N, N, 0);
    return 0;
}
