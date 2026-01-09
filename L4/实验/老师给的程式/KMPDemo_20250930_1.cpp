#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*
    int a[3][5]; // 3 x 5 matrix

    // static vs dynamic
    int a[5]; <-> int* a = new int[5];

    // m x n matrix
    int** a = new int*[m];
    for(int i=0;i<m;i++)
        a[i] = new int[n];
    a[i][j] <--- position (i,j) of matrix
*/

int* getNext(string T){
    int tLen = T.length();
    int* next = new int[tLen];
    if(tLen==0) return next;
    next[0] = -1;
    if(tLen==1) return next;
    next[1] = 0;
    for(int j=2;j<tLen;j++){
        // calculate next[i]
        int k = next[j-1];
        while(k!=-1 && T[k]!=T[j-1]){
            k = next[k];
        }
        next[j] = k+1;

        /*if(T[k]==T[j-1]){
            next[j] = k+1;
        }
        else{
            while(k!=-1 && T[k]!=T[j-1]){
                k = next[k];
            }
            next[j] = k+1;
        }*/
    }
    return next;
}

int KMP(string S, string T){
    int i=0, j=0; // i points to S, j points to T
    int sLen = S.length();
    int tLen = T.length();
    int* next = getNext(T);
    if(tLen==0) return 0;
    if(sLen==0) return -1;
    while(i < sLen && j < tLen){
        if(j==-1||S[i]==T[j]){
            cout << "Matched " << i << " and " << j << endl;
            i++;
            j++;
        }
        else{
            cout << "Mismatched " << i << " and " << j << endl;
            j = next[j];
        }
    }
    if(j==tLen){
        return i-j;
    }
    else
        return -1;
}

int main(){
    string longTxt, pTxt;
    cin >> longTxt >> pTxt;
    int* n = getNext(pTxt);
    cout << setw(5) << right << " ";
    for(int i=0;i<pTxt.length();i++){
        cout << setw(5) << right << pTxt[i];
    }
    cout << endl;
    cout << setw(5) << right << "Next:";
    for(int i=0;i<pTxt.length();i++){
        cout << setw(5) << right << n[i];
    }
    cout << endl << endl;
    cout << "String matched at position " << KMP(longTxt, pTxt) << endl;
    return 0;
}
