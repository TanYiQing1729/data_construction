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
        void addLChild(BinTree<T>* bt){
            left = bt;
        }
        void addLChild(T x){
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
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
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
        
        void printPreOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    cout << tmp->data << " ";
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop()->right;
                }
            }
        }
        
        void printInOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop();
                    cout << tmp->data << " ";
                    tmp = tmp->right;
                }
            }
        }
        
        void printPostOrderNR(){
            LinkStack<BinTree<T>*> s;
            BinTree<T>* tmp = this;
            while(tmp!=NULL || !s.isEmpty()){
                if(tmp!=NULL){
                    s.push(tmp);
                    tmp = tmp->left;
                }
                else if(!s.isEmpty()){
                    tmp = s.pop();
                    if(!s.isEmpty() && s.getTop()==tmp){
                        cout << s.pop()->data << " ";
                        tmp = NULL;
                    }
                    else{
                        s.push(tmp);
                        s.push(tmp);
                        tmp = tmp->right;
                    }
                }
            }
        }
};

/* Solution here */

//写一个函数来递归输出 
void print_matrix(int i, int j, int sep[50][50]){
	if(i == j){
		cout<<"("<<i<<")";
		return;    //表示不再进行 
	}
	int k = sep[i][j];
    cout << "(";
    print_matrix(i, k, sep);
    print_matrix(k+1, j, sep);
    cout << ")";
} 


// matrix chain multiplication problem
int minOpMatrixMult(int* sizes, int n){
    // n represents number of matrices
    // 0th matrix has dimensions sizes[0] x sizes[1]
    // 1st matrix has dimensions sizes[1] x sizes[2]
    // ...
    // (n-1)-th matrix has dimensions sizes[n-1] x sizes[n]
    //
    // Goal: find minimum number of operations to multiply the whole set of matrices
    // also print the parenthesis to do it.
    
    // TODO
    
    //这是动态规划问题
	//step1：确定dp数组和下标含义 
	//dp[i][j]为从第i个矩阵到第j个矩阵连乘起来所需的最少乘法次数。
	
	//step2:递归公式
	//从头到尾，考虑在i处分割，则可以表示为0到i要的dp次数加上i+1到n要的dp次数，最后再加上两个大矩阵相乘的次数 
	//dp[0][n-1] = min{dp[0][i] + dp[i+1][n-1] + sizes[0]*size[i+1]*[n]} 
	 
    //step3：初始化
	//i=j时，dp[i][j] = 0;
	
	//step4:遍历顺序
	//填表法，但是不能直接二维数组遍历，应该要从矩阵链短的到矩阵链长的来 
	
	//上述过程应该是可以解决最小乘积这个数了，接下来是怎么分割
	//很自然可以想到记录分割点，可以拿一个数组来分割 
	 
	int dp[50][50];
	int sep[50][50];
	
	for(int i=0;i<50;i++){
		for(int j=0;j<50;j++){
			if(i == j){
				dp[i][j] = 0;
			}
			else{
				dp[i][j] = -1;    //未初始化 
			}
		}
	}
	
	//按矩阵链的长度来遍历
	for(int len=2;len<=n;len++){
		for(int i=0;i+len-1<n;i++){
			int j = i + len - 1;    //矩阵链的长度是len所以j是由i确定的
			//接着按照递推公式，应该要去找分割点，满足rhs最小
			int min = 100000000;    //设成一个很大的值
			int min_pos = 0;    //这个随便初始化 
			for(int k=i;k<j;k++){ 
				if(min > dp[i][k] + dp[k+1][j] + sizes[i]*sizes[k+1]*sizes[j+1]){    
				//相等不更新，就可以让括号打在后面 
					min = dp[i][k] + dp[k+1][j] + sizes[i]*sizes[k+1]*sizes[j+1];
					min_pos = k;
				}
			}
			dp[i][j] = min;
			sep[i][j] = min_pos;
		}
	} 
	
	//接下来只要打印就好了，因为是用动态规划写的所以应该可以用递归来写
	print_matrix(0, n-1, sep);
	cout<<endl;
	
	return dp[0][n-1];
}

/* End solution */

void test1(){
    int case1[4] = {10,30,5,60};
    int case4[5] = {1,2,3,4,5};
    int case5[3] = {3,3,3};
    
    cout << "Case 1: " << endl;
    int x = minOpMatrixMult(case1,3);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 4: " << endl;
    x = minOpMatrixMult(case4,4);
    cout << "Total operations = " << x << endl << endl;
    
    cout << "Case 5: " << endl;
    x = minOpMatrixMult(case5,2);
    cout << "Total operations = " << x << endl << endl;
}

int main(){
    test1();
    return 0;
}
