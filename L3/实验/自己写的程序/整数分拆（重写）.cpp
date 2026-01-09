#include <iostream>
using namespace std;

int set[50];

void print(int n, int m, int store){
	if (n == 0){
		for(int i=0;i<store-1;i++){
			cout<<set[i]<<"+";
		}
		if (store > 0){
			cout<<set[store-1];
		}
		cout<<endl;
		return;
	}
	
	for(int i=m;i>0;i--){
		if(i<=n){
			set[store] = i;
			print(n-i,i,store+1);
		}
	}
}

int main(){
	int N=100;
	cin>>N;
	print(N,N,0);	
} 

