#include <iostream>
using namespace std;

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

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
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
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
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

/* Questions 1,2,4 UPLOAD START */

template <class T>
class BinTree{
    private:
        T data;
        BinTree<T>* left;
        BinTree<T>* right;
    public:
        BinTree(){
            left = NULL;
            right = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
        }
        ~BinTree(){
            
        }
        void addLChild(BinTree<T>* bt){      //加左孩子，直接加子树 
            left = bt;
        }
        void addLChild(T x){      //加左孩子，数据变成子树，再加子树 
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addRChild(bt);
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        //前序非递归 
        void printPreOrderNR(){
        	LinkStack<BinTree<T>*> S;
        	BinTree<T>* temp = this;
        	while(!S.isEmpty() || temp != NULL){
        		if(temp != NULL){
        			cout<<temp->data<<" ";
        			if(temp->right != NULL){
        				S.push(temp->right);
					}
					temp = temp -> left;
				}
				else{
					temp = S.pop();
				}
			}
		}
        
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printPostOrderNR(){
        	LinkStack<BinTree<T>*> Stree;
        	LinkStack<int> Ssym;
			BinTree<T>* temp = this;
        	while(!Stree.isEmpty() || temp != NULL){
        		if(temp != NULL){
        			Stree.push(temp);
        			Ssym.push(1);
        			temp = temp -> left;
				}
				else{
					temp = Stree.pop();
					int num = Ssym.pop();
					if(num == 1){
						Stree.push(temp);
						Ssym.push(2);
						temp = temp->right;
					}
					else if(num == 2){
						cout<<temp->data<<" ";
						temp = NULL;
					}
				}
			}
		}
        
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        //中序非递归 
        void printInOrderNR(){
        	LinkStack<BinTree<T>*> S;
        	BinTree<T>* temp = this;
        	while(!S.isEmpty() || temp != NULL){
        		if(temp != NULL){
        			S.push(temp);
        			temp=temp->left;
				}
				else{
					temp = S.pop();
					cout<<temp->data<<" ";
					temp = temp -> right;
				}
			}
		}
        
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmpN = q.deQueue();
                cout << tmpN->data << " ";
                if(tmpN->left!=NULL) q.enQueue(tmpN->left);
                if(tmpN->right!=NULL) q.enQueue(tmpN->right);
            }
        }
        
        
        bool isLeaf(){
            return left==NULL && right==NULL;
        }
        int leafNodeCount(){ // question 1
            //简单的，使用层序遍历，统计没有孩子的结点数量
			int num = 0;  //统计叶子结点的个数 
			LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            BinTree<T>* temp;
            while(!q.isEmpty()){
                temp = q.deQueue(); 
                if(temp->left==NULL && temp->right==NULL){
					num++;   //既没有左孩子也没有右孩子就是叶子，所以++ 
				}
				if(temp->left!=NULL){
                	q.enQueue(temp->left);
				}
                if(temp->right!=NULL){
                	q.enQueue(temp->right);
				}
            }
			return num; 
        }
        
        bool isComplete(){ // question 2
            //还是使用层序遍历，这次做的事情是只能有一个度1的结点，而且叶子在最底两层的左边
			//这个东西有点抽象，换一个判定的方法，如果：只有右孩子没有左孩子，不是完全二叉树
			//出现了只有左孩子而没有右孩子，or没有孩子，则后面只能出现叶子结点 
			//注意：空树不是二叉树
			if(this->left==NULL && this->right==NULL){
				return 0;
			}
			else{ 
				LinkQueue<BinTree<T> *> q;
	            q.enQueue(this);
	            BinTree<T>* temp;
	            while(!q.isEmpty()){
	                temp = q.deQueue(); 
	                if(temp->left==NULL && temp->right!=NULL){
						return 0; 
					}
					if(temp->left!=NULL && temp->right==NULL ||
					   temp->left==NULL && temp->right==NULL){
					   	if(temp->left!=NULL && temp->right==NULL){
					   		q.enQueue(temp->left);
						}
						while(!q.isEmpty()){
							temp = q.deQueue();
							if(temp->left!=NULL || temp->right!=NULL){
								return 0;
							}
						}
						return 1;
					}
					if(temp->left!=NULL && temp->right!=NULL){
						q.enQueue(temp->left);
						q.enQueue(temp->right);
					}
	            }
	            return 1;
			} 
        }
		
		void printSnakeLevelOrder(){ // question 4
            //想法是写两个栈，两个栈的左右孩子入栈顺序相反，两个栈轮流进行出栈
			LinkStack<BinTree<T> *> s1;
			LinkStack<BinTree<T> *> s2;
			s1.push(this);
			while(s1.isEmpty()==0 || s2.isEmpty()==0){
				while(s1.isEmpty()==0){
					BinTree<T>* temp1 = s1.pop();
					cout<<temp1->data<<" ";
					if(temp1->left!=NULL){
						s2.push(temp1->left);
					}
					if(temp1->right!=NULL){
						s2.push(temp1->right);
					}
				}
				while(s2.isEmpty()==0){
					BinTree<T>* temp2 = s2.pop();
					cout<<temp2->data<<" ";
					if(temp2->right!=NULL){
						s1.push(temp2->right);
					}
					if(temp2->left!=NULL){
						s1.push(temp2->left);
					}
				}
			}
		}
        
};

/* Questions 1,2,4 UPLOAD END */

/* Question 3 UPLOAD START */
template <class T>
BinTree<T>* buildFromPreIn(T* preArr, T* inArr, int n){
    //想法：使用递归，写出第一层，然后各自的左孩子和右孩子都递归实现 
	if (n <= 0) {
        return NULL;
    }
	BinTree<T>* result = new BinTree<T>(preArr[0]);
	BinTree<T>* left = new BinTree<T>;
	BinTree<T>* right = new BinTree<T>;
	for(int i=0;i<n;i++){     //给数组赋值太麻烦了，所以合理利用第三个参数n 
		if(preArr[0]==inArr[i]){
			left = buildFromPreIn(preArr+1, inArr, i);
			right = buildFromPreIn(preArr+i+1, inArr+i+1, n-i-1);
			result->addLChild(left);
			result->addRChild(right);
		}
	}
	return result;
}
/* Question 3 UPLOAD END */

void test1(){
    BinTree<int> *treeK = new BinTree<int>(1);
    cout << treeK->leafNodeCount() << endl;
    treeK->addLChild(2);
    treeK->addRChild(3);
    cout << treeK->leafNodeCount() << endl;
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << treeK->leafNodeCount() << endl;
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << treeK->leafNodeCount() << endl;
    
}

void test2(){
    BinTree<int> *treeK = new BinTree<int>(1);
    treeK->addLChild(2);
    treeK->addRChild(3);
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getRChild()->addRChild(11);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getLChild()->getLChild()->addLChild(16);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
}

void test3(){
    BinTree<char> * tmp1, *tmp5;
    BinTree<int> *tmp2, *tmp3, *tmp4;
    
    int t2p[3] = {1,2,3};
    int t2i[3] = {2,1,3};
    
    tmp2 = buildFromPreIn(t2p,t2i,3);
    tmp2->printPreOrderR();
    cout << endl;
    tmp2->printInOrderR();
    cout << endl;
    tmp2->printPostOrderR();
    cout << endl;
    tmp2->printLevelOrder();
    cout << endl;
    
    char t1p[7] = {'A','B','D','G','C','E','F'};
    char t1i[7] = {'D','G','B','A','E','C','F'};
    
    tmp1 = buildFromPreIn(t1p,t1i,7);
    tmp1->printPreOrderR();
    cout << endl;
    tmp1->printInOrderR();
    cout << endl;
    tmp1->printPostOrderR();
    cout << endl;
    tmp1->printLevelOrder();
    cout << endl;
    
}

void test4(){
    BinTree<char> * tmp1, *tmp5;
    BinTree<int> *tmp2, *tmp3, *tmp4;
    
    int t2p[3] = {1,2,3};
    int t2i[3] = {2,1,3};
    
    tmp2 = buildFromPreIn(t2p,t2i,3);
    tmp2->printSnakeLevelOrder();
    cout << endl;
    
    char t1p[7] = {'A','B','D','G','C','E','F'};
    char t1i[7] = {'D','G','B','A','E','C','F'};
    
    tmp1 = buildFromPreIn(t1p,t1i,7);
    tmp1->printSnakeLevelOrder();
    cout << endl;
} 

int main(){
    test1();
    test2();
    test3();
    test4();
    return 0;
}
