#include <iostream>
#include <string>
using namespace std;

//use BF for now
int main(){
	string S;
	cin>>S;
	int count = 0;
	while(count<S.length()){
		//初始化T 
		string T = S.substr(0,count+1);
		
		//匹配 
		if(S.length()%(count+1)==0){
			bool judge = 0;
			for(int j=0;j<S.length();j++){
				judge = 0;
				int j_t;
				j_t = j % (count+1);
				if(S[j]!=T[j_t]){
					judge = 1;
					break;
				}
			}
			//这里的匹配是建立在前面都对的情况下 
			if(judge == 0){
				cout<<count+1<<endl;
				for(int k=0;k<=count;k++){
					cout<<T[k];
				}
				break;
			}
		}
		count++;
	}
}
