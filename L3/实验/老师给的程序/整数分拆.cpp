#include <iostream>
using namespace std;

void print_partition(int* a){
	int i = 1;
	cout<<a[0];
	while(a[i]!=0){
		cout<< "+" <<a[i];
		i++
	}
	cout<<endl;
}

void next_partition(int* a){
	int i=19;
	int count_one = 0;
	while(a[i]==0){
		i--;
	}
	while(a[i]==1){
		a[i]--;
		count_one++;
		i--;
	}
	a[i]--;
	int parts = a[i];
	count_one++;
	i++;
	while(count_one > parts){
		a[i] = parts;
		i++;
		count_one -= parts;
	}
	a[i] = count_one;
}

void dfs(int remaining, int largest_usable, string parts_so_far){
	if(remaining == 0){
		cout<<part_so_far<<endl;
		return;
	}
	if(largest_usable>remaining){
		largest_usable = remaining;
	}
	for(int i=largest_usable;i>=1;i--){
		dfs(remaining-i,i,parts_so_far+(parts_so_far=="?"":""+")+to_string(i))
	}
	
}

void parts(int N){
	dfs(N,N,"")
}

int main(){
	int N;
	cin>>N;
	parts()
}

int main(){
	int N;
	cin>>N;
	int* a = new int[20];
	for(int i=0;i<20;i++){
		a[i]=0;
	}
	a[0]=N;
	print_partition(a); 
	while(a[0]!=1){
		next_partition(a);
		print_partition(a);
	}
	return 0;
}
