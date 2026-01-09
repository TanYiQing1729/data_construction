#include <iostream>
using namespace std;
/* 
int main(){
	int n,m;
	int count = 0;
	int current = 0;
	cin>>n;
	cin>>m;
	int save = n;
	int a[n]={0};
	for(int i=0;i<n;i++){
		a[i]=i+1;
	}
	while(save != 0){
		if (a[current] != 0) {
            count++; 
            if (count == m) {
                cout <<a[current]<<" ";
                a[current] = 0; 
                save--;
                count = 0;
            }
        }
        current = (current + 1) % n;
	}
}
*/

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
    	}
    	bool isEmpty(){
        	return length == 0;
    	}
    
    	int getLength(){
        	return length;
    	}
};


int main(){
	int n,m;
	int count = 1;
	cin>>n;
	cin>>m;
	int save = n;
	LinkQueue<int> p;
	
	for(int i=0;i<n;i++){
		p.enQueue(i+1);
	}
	
	while(!p.isEmpty()){
        int k = (m - 1) % p.getLength(); 
        for(int i = 0; i < k; i++) {
            p.enQueue(p.deQueue());
        }
        cout << p.deQueue() << " ";
    }
};
