#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */
void makePalindrome(string s){
	//单个长度直接输出 
	if(s.length() <= 1){
        cout<<s<<endl;
        return;
    }
	//赋值 
	string t;
	t = s;
	for(int i=0;i<s.length();i++){
		t[i]=s[s.length()-i-1];
	}
	
	
	//已经回文直接输出 
    if(s == t){
        cout<<s<<endl;
        return;
    }
    
    //大致思路是找出字符串中间已经是回文的部分，然后把多余的加在后面去 
    for(int i=0;i<s.length();i++){
        bool judge = 1;
        int left = i; 
		int right = s.length()-1;
        while(left < right){
            if(s[left] != s[right]){
                judge = 0;
                break;
            }
            left++;
            right--;
        }
        
        if(judge==1){
            string temp = s.substr(0, i); 
            string r = temp;
			for(int i=0;i<temp.length();i++){
				r[i]=temp[temp.length()-i-1];
			}
            cout << s + r << endl;
            return;
        }
    }
    
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1:
            makePalindrome("A");
            makePalindrome("ABA");
            break;
        case 2:
            makePalindrome("AB");
            makePalindrome("ABC");
            break;
        case 3:
            makePalindrome("ABCB");
            makePalindrome("ABCCBC");
        default: ;
    }
    return 0;
}
