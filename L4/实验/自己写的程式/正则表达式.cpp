#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* UPLOAD START */

int simplePatternMatch(string s, string p){
    //use BF for now
    //想法是用*分割p，每一段分别做模式匹配
	int length = p.length();
    int pos[length];
    int idx = 0;   //双增量 
    bool find = 0;   //统一有*和没*的我debug不出来了干脆写两种情况吧 
    for(int i=0;i<p.length();i++){
    	if(p[i]=='*'){
    		pos[idx] = i; 
    		idx++;
    		find = 1; 
		}
	}
	//这样把所有*位置给找出来了
	
	if(find == 0){
		int j_0 = 0;
		int k_0 = 0;
		while(k_0<s.length() && j_0<p.length()){
			if(p[j_0] == s[k_0]){
				j_0++;
				k_0++;
			}
			else{
				k_0 = k_0-j_0+1;
				j_0 = 0;
			}
		}
		if(j_0 == p.length()){
			return k_0-p.length();
		}
		else{
			return -1;
		}
	}
	else{
		int position = 0;  //存p在s的哪个位置,是用于输出的 
		int position_temp = 0;  //存每一次匹配成功的位置，下一次匹配从这里开始，管它内存多不多存就完事了 
		int temp = -1;
		bool judge = 1;   //总判断 
		for(int i=0;i<idx;i++){
			string store(pos[i]-temp-1, ' ');
			store = p.substr(temp+1, pos[i]-temp-1);
			temp = pos[i];
			//这样就把p的子串搞出来了，接下来做模式匹配
			
			//先把空段认为是匹配成功 
			if(store.length() == 0){
                if(i == 0 && position == -1){
                    position = position_temp; 
                }
                continue;
            }
			
			int j = 0;
			int k = 0;
			if(i == 0){
				k = 0;
			}
			else{
				k = position_temp;
			}
			
			while(k<s.length() && j<store.length()){
				if(store[j] == s[k]){
					j++;
					k++;
				}
				else{
					k = k-j+1;
					j = 0;
				}
			}
			if(j == store.length()){
				if(i == 0){    //如果第一个子串匹配对了，p就有可能在s中，所以先把位置存了 
					position = k - store.length(); 
				}
				position_temp = k;
			}
			else{
				judge = 0;
				break;		
			}
		}
		
		//还需要处理最后一段 
		string last = p.substr(temp+1, p.length()-temp-1);
		int j_last = 0;
		int k_last = position_temp;
		while(k_last<s.length() && j_last<last.length()){
			if(last[j_last] == s[k_last]){
				j_last++;
				k_last++;
			}
			else{
				k_last = k_last-j_last+1;
				j_last = 0;
			}
		}
		if(j_last == last.length()){
			position_temp = k_last;
		}
		else{
			judge = 0;
		}
		 
		
		//输出结果 
		if(judge == 0){
			return -1;
		}
		else{
			return position;
		}
	}
	
	
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    string s1 = "aaccdabbca";
    switch(x){
        case 1:
            cout << simplePatternMatch(s1,"abb") << endl;
            cout << simplePatternMatch(s1,"cda") << endl;
            cout << simplePatternMatch(s1,"ccdb") << endl;
            break;
        case 2:
            cout << simplePatternMatch(s1,"aa*ab") << endl;
            cout << simplePatternMatch(s1,"ad*ab") << endl;
            cout << simplePatternMatch(s1,"aa*d") << endl;
            break;
        case 3:
            cout << simplePatternMatch(s1,"e*ac*da") << endl;
            cout << simplePatternMatch(s1,"ac*cb*a") << endl;
            cout << simplePatternMatch(s1,"ac*cd*ca") << endl;
        default: ;
    }
    return 0;
}
