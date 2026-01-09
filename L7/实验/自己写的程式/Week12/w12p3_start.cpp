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
        BinTree<T>* parent;
    public:
        BinTree(){
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        ~BinTree(){
            
        }
        void addLChild(BinTree<T>* bt){
            left = bt;
            if(bt==NULL) return;
            bt->parent = this;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
            if(bt==NULL) return;
            bt->parent = this;
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
        BinTree<T>* getParent(){
            return parent;
        }
        void setParent(BinTree<T>* bt){
            parent = bt;
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
};

/* UPLOAD START */

template <class T>
class BinarySearchTree{
    // T better have its comparison operators overloaded.
    // we assume no duplicate elements
    // use an empty root node
    // 要求 T 支持比较运算符（<, >, ==）。
    // 假设不插入重复元素。
    // 使用一个“空的根节点”（dummy root），实际的树从 root->getRChild() 开始。
    private:
        BinTree<T>* root;    //指向虚拟根结点（类似于头空节点），真实根为 root->getRChild()
        int nodeCount;    //结点个数 
        
        // findParent 返回值含义：
        // - 当元素 x 存在于树中时，返回该元素节点的父节点（注意不是该元素节点本身）。
        // - 当元素 x 不存在时，返回应该成为 x 的父节点（即插入位置的父节点）。
        // - 当树为空（nodeCount==0）时返回 NULL。
        BinTree<T>* findParent(T x){
            if(nodeCount==0){
                return NULL;
            }
            // 从真实根开始搜索
            BinTree<T>* bt = root->getRChild();    
			// btParent 初始为 bt 的父节点（对于真实根，父节点是虚拟 root）
            BinTree<T>* btParent = bt->getParent();
            while(bt!=NULL){
                if(bt->getData()==x){
                    // 找到了目标，返回它的父节点（而非节点本身）
					return bt->getParent();
                }
                else if(bt->getData() > x){
                    // x 比当前节点小，向左走
					btParent = bt;
                    bt = bt->getLChild();
                }
                else{
                    // x 比当前节点大，向右走
					btParent = bt;
                    bt = bt->getRChild();
                }
            }
            return btParent;
        }
        
    public:
        BinarySearchTree(){
            // 创建虚拟根节点（空节点），真实数据存放在 root->R 子树。
			root = new BinTree<T>();
            nodeCount = 0;
        }
        
        //使用数组初始化（逐个插入）
        BinarySearchTree(T* arr, int n){ // insert whole array
            root = new BinTree<T>();
            nodeCount = 0;
            if(n==0) return;
            for(int i=0;i<n;i++){
                insertData(arr[i]);    //在下面有这个函数 
            }
        }
        // 析构层序遍历删除每个节点（包括虚拟根）
        ~BinarySearchTree(){
            // LinkQueue destroying every node
            LinkQueue<BinTree<T>*> q;
            q.enQueue(root);
            while(!q.isEmpty()){
                BinTree<T>* bt = q.deQueue();
                if(bt->getLChild()!=NULL) q.enQueue(bt->getLChild());
                if(bt->getRChild()!=NULL) q.enQueue(bt->getRChild());
                delete bt;
            }
        }
        bool isEmpty(){
            return nodeCount==0;
        }
        void insertData(T x){
            if(nodeCount==0){
                // 空树：将真实根作为 root 的右子树（约定）
				nodeCount++;
                root->addRChild(x);    // addRChild 创建并连接新的结点（实现依赖于 BinTree）
                return;
            }
            if(searchData(x)) return;
            BinTree<T>* btP = findParent(x); // 找到插入位置的父节点
            // 根据大小决定插到左子树或右子树 
            if(btP->getData()<x) btP->addRChild(x);
            if(btP->getData()>x) btP->addLChild(x);
            nodeCount++;
        }
        bool searchData(T x){
            if(nodeCount==0) return false;
            BinTree<T>* btP = findParent(x);    // btP 是找到的“父节点”，
			//注意，如果btP不在，它的父结点是它要插入位置的父结点 
            if(btP==root) return true;
            // 下面根据 btP 与 x 的大小关系判断对应方向上是否存在子节点，存在则说明 x 存在
            if(btP->getData()<x) return (btP->getRChild()!=NULL);    //如果父结点比x小，就去找父结点的右孩子，如果非空就一定是x 
            if(btP->getData()>x) return (btP->getLChild()!=NULL);    //如果父结点比x大，就去找父结点的左孩子，如果非空就一定是x
        }
        // 删除元素 x（存在则删除并返回 true，否则返回 false）
        bool deleteData(T x){
            if(nodeCount==0) return false;
            if(!searchData(x)) return false;    // 不存在则不能删除
            // there is a thing to delete
            BinTree<T>* btP = findParent(x);
            if(btP == root){
            	// 要删除的节点是虚拟根的右子（真实根）
                btP = btP->getRChild();    // btP 现在指向要删除的节点
            }
            else{
            	// 根据父节点与 x 的大小关系移动到实际的要删除节点
                if(btP->getData()<x) btP = btP->getRChild();
                else if(btP->getData()>x) btP = btP->getLChild();
            }
            // this is the node to delete.
            // we will find the number that's barely smaller than btP's number.
            //上面做的事情是让btp指向要删除的地方 
            
            // only right child exists
            // 删除策略：若左子为空，则直接用右子替代（包含右子为空的情况，即叶子）
            if(btP->getLChild()==NULL){
                if(btP->getParent()->getLChild()==btP){    //要删除的结点的双亲的左孩子是要删除的结点 
                    btP->getParent()->addLChild(btP->getRChild());    //直接把btp双亲的左孩子换成btp的右孩子 
                }
                else{    //反之 
                    btP->getParent()->addRChild(btP->getRChild());    //直接把btp双亲的右孩子换成btp的右孩子
                }
                delete btP;
            }
            else{
            	// 左子非空：找到左子子树中最大的节点（即比当前略小的前驱）
                BinTree<T>* btS = btP->getLChild();
                while(btS->getRChild()!=NULL){
                    btS = btS->getRChild();    //如果右孩子不是空的，就往右孩子跑（找到左边最大） 
                }
                // 用前驱节点的数据覆盖当前节点btP，然后删除前驱节点btS（BST 删除常用技巧）
                btP->setData(btS->getData());
                // 接着将前驱节点btS的位置由其左子替代（前驱节点不会有右子）
                // 如果前驱btS是 btP 的直接左子
                if(btS->getParent()==btP) btP->addLChild(btS->getLChild());    //直接用btS的左孩子替代掉btS 
                // 否则前驱是更深层次的右子，用其左子替代它在父亲处的位置
				else btS->getParent()->addRChild(btS->getLChild());    //把前驱btS的双亲的右孩子（也就是它自己）换成btS的左孩子 
                delete btS;
            }
            
            nodeCount--;
            return true;
        }
        void printInOrder(){
            cout << "In Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printInOrderR();
            cout << endl;
        }
        void printPreOrder(){
            cout << "PreOrder: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printPreOrderR();
            cout << endl;
        }
        void printPostOrder(){
            cout << "Post Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printPostOrderR();
            cout << endl;
        }
        
        void printLevelOrder(){
            cout << "Level Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printLevelOrder();
            cout << endl;
        }
        
        //写个辅助函数来递归 
        long long helper(BinTree<T>* bt, int mod_num){
        	if(bt == NULL){
        		return 1;
			}
			if(bt->getLChild() == NULL && bt->getRChild() == NULL){
        		return 1;
			}
			int num_of_left = 0;
			int num_of_right = 0;
			
			if(bt->getLChild() != NULL){
				num_of_left = num_of_node(bt->getLChild());
			}
			
			if(bt->getRChild() != NULL){
				num_of_right = num_of_node(bt->getRChild());
			}
			
			return (combining_helper((num_of_left + num_of_right), num_of_left, mod_num) * helper(bt->getLChild(), mod_num) * helper(bt->getRChild(), mod_num)) % mod_num; 
		}
        
        //写个辅助函数来计算求模之后的除法
		long long mod_divide_calculate(int a, int b, int mod_num){
			//先计算b在mod p意义下的逆元
			long long b_ni = 1;
			for(int i=1;i<=mod_num-2;i++){
				b_ni = (b_ni * b) % mod_num;
			}
			return (a * b_ni) % mod_num;
			 
		}
        
        //写个辅助函数来计算组合数 
        long long combining_helper(int n, int m, int mod_num){
			//这里没办法只能边算边求模 
			long long fenzi_mod = 1;
			long long fenmu_mod = 1;
			long long temp1_mod = 1;    //存m的阶乘
			long long temp2_mod = 1;    //存n-m的阶乘 
			for(int i=1;i<=n;i++){
				fenzi_mod = (fenzi_mod * i) % mod_num;
			}
			for(int i=1;i<=m;i++){
				temp1_mod = (temp1_mod * i) % mod_num; 
			} 
			for(int i=1;i<=n-m;i++){
				temp2_mod = (temp2_mod * i) % mod_num;
			}
			fenmu_mod = (temp1_mod * temp2_mod) % mod_num; 
			
			//这里求最后一步除法有问题
			//mod p之后是一个域Zp，但是它的除法计算要用费马小定理计算
			//所以再写一个辅助函数 
			//PS:也可以用帕斯卡恒等式来计算，避免这一步除法运算 
			
			int result = mod_divide_calculate(fenzi_mod, fenmu_mod, mod_num);
			
			return result;
		}
        
        //写个辅助函数来计算结点数量 
        int num_of_node(BinTree<T>* bt){
        	if(bt == NULL){
        		return 0;
			}
			if(bt->getLChild() == NULL && bt->getRChild() == NULL){
        		return 1;
			}
			int num_of_left = 0;
			int num_of_right = 0;
			if(bt->getLChild()!=NULL){
				num_of_left = num_of_node(bt->getLChild());
			}
            if(bt->getRChild()!=NULL){
            	num_of_right = num_of_node(bt->getRChild());
			}
            return num_of_left + num_of_right + 1;
		}
        
        int numWaysToGetBST(int mod_num){
            // TO DO
            //我目前认为约束是：根结点不变。剩下的元素分成“左子树的元素”和“右子树的元素”，给人一种可以递归的感觉 
			//为了在插入过程中保持左右子树的结构，左子树内部元素的相对先后顺序必须与能生成左子树的那些序列相同
			//（同理右子树）。
			//也就是说，左子树内部是一个“块”，右子树内部是一个“块”，每个块内部要保持自身允许的顺序集合。
			//因此问题变成：将左子树的 L 个元素序列和右子树的 R 个元素序列进行交错，
			//同时保留每一侧序列内部的相对顺序。有多少种交错方式？
			//正好是 C(L+R, L)（在 L+R 个位置里选 L 个位置放左侧元素，剩下放右侧元素）。 
			//然后再乘以各自子树的数量f(left)和f(right) 
			
			//实现上来说，写三个辅助函数，第一个用于递归，第二个用于计算组合数，第三个用于计算树的结点数量 
			
			long long num;    //直接暴力计数
			
			num = helper(root->getRChild(), mod_num); 
			
			return num;
        }
};

/* UPLOAD END */

void test1(){
    BinarySearchTree<int> bst;
    bst.insertData(4);
    bst.insertData(2);
    bst.insertData(1);
    bst.insertData(3);
    bst.insertData(6);
    bst.insertData(5);
    bst.insertData(7);
    cout << bst.numWaysToGetBST(10007) << endl; //80
    
    bst.insertData(10);
    bst.insertData(8);
    cout << bst.numWaysToGetBST(10007) << endl; //448
}

int main(){
    test1();
    return 0;
}
