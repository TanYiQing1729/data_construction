//栈的链表实现与RPN 
#include <iostream>
#include <string>
using namespace std;

template <class T>
struct DNode{
	T data;
	DNode<T>* next;
};

template <class T>
class LinkStack{
	private: 
		DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

void RPN(){
	LinkStack<int> S;
	string input;
	do {
		cin>>input;
		if(input=="+"){
			if(S.getLength()<2){
				cout<<"Wrong"<<endl;
				return;
			} 
			int pop1, pop2;
			pop2 = S.pop();
			pop1 = S.pop();
			int temp = pop1 + pop2;
			S.push(temp); 
		}
		else if(input=="-"){
			if(S.getLength()<2){
				cout<<"Wrong"<<endl;
				return;
			} 
			int pop1, pop2;
			pop2 = S.pop();
			pop1 = S.pop();
			int temp = pop1 - pop2;
			S.push(temp); 
		}
		else if(input=="*"){
			if(S.getLength()<2){
				cout<<"Wrong"<<endl;
				return;
			} 
			int pop1, pop2;
			pop2 = S.pop();
			pop1 = S.pop();
			int temp = pop1 * pop2;
			S.push(temp); 
		}
		else if(input=="/"){
			if(S.getLength()<2){
				cout<<"Wrong"<<endl;
				return;
			} 
			int pop1, pop2;
			pop2 = S.pop();
			pop1 = S.pop();
			int temp = pop1 / pop2;
			S.push(temp); 
		}
		else{
			int temp = stoi(input);
			S.push(temp);
		}
	}while(input == "=");
}

int main(){
	RPN();
} 
