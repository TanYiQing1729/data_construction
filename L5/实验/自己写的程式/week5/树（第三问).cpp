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

/* Question 2, 3 UPLOAD START */

template <class T>
class LTree{
    private:
        T data;
        VecList<LTree<T> *> children;   //一个数组里有一堆指向孩子的指针  
    public:
        LTree(){
			//无需写，因为是空树 
        }
        LTree(T x){
            data = x;    //给数据赋一个数值，但是还没有孩子的信息，所以不用写孩子 
        }
        ~LTree(){
            //孩子的信息没必要删除，所以也可以不写 
            
        }
        void addChild(LTree<T>* lt){        //把子树加到一个点的一个孩子里头 
            children.insertEleAtPos(children.getLength(),lt);    //默认加在最右边 
        }
        void addChild(T x){                    //把一个数据加到一个孩子里头 
            LTree<T>* lt = new LTree<T>(x);    //建一个孩子的子树 
            addChild(lt);                      //把孩子加进去（递归） 
        }
        LTree<T>* getChild(T x){
            for(int i=0;i<children.getLength();i++){
                if(children.getEleAtPos(i)->data == x)     //拿出第i个孩子，看是不是x，如果是回传 
                    return children.getEleAtPos(i);
            }
            return NULL;
        }
        void setData(T x){
            data = x;                //根节点数据 
        }
        T getData(){
            return data;
        }
        void printPreOrder(){
            cout << data << " ";     //根节点数据 
            for(int i=0;i<children.getLength();i++){
                children.getEleAtPos(i)->printPreOrder();
            }
        }
        void printPostOrder(){
            for(int i=0;i<children.getLength();i++){
                children.getEleAtPos(i)->printPostOrder();
            }
            cout << data << " ";
        }
        void printLevelOrder(){
            //像一个队列，在输出一个元素的同时，把它所有的孩子入队放在队尾
			LinkQueue<LTree<T> *> q;
            q.enQueue(this);     //根节点入队 
            LTree<T>* tmp;
            while(!q.isEmpty()){
                tmp = q.deQueue();   //第一个元素出队并打印 
                cout << tmp->data << " ";
                for(int i=0;i<tmp->children.getLength();i++){
                    q.enQueue(tmp->children.getEleAtPos(i));          //所有孩子入队 
                }
            }
        }
        
        // problem 2
        int height(){
            //深度就是所有节点的最大层数，那就是沿着一条路走到底 
            //如何表征它的深度在增加呢，就是它有孩子才可能增加 
            //上面这个想法我觉得太难实现了
			//所以我想了一个新的，比较像整数分拆的递归，只考虑输出分拆数量的方法
			//如果这个节点没有孩子，那么它的深度是0；
			//否则，这个点的深度是它每一个子树的深度的最大值+1 
			int depth = 0;
			LTree<T>* temp = this; 
			if(temp->children.getLength() == 0){
				depth = 1;
			}
			else{
				for(int i=0;i<children.getLength();i++){
					if(depth < (temp->children.getEleAtPos(i))->height()+1){
						depth = (temp->children.getEleAtPos(i))->height()+1;
					}
				}
			}
			return depth;
        }
        int degree(){
			//想法是遍历一遍树，然后统计每个节点的度数，用层序感觉是最好写的 
			int max_node = 0;    //存储度数最大的结点的度数 
			max_node = this->children.getLength(); 
			LinkQueue<LTree<T> *> q;
            q.enQueue(this);     //根节点入队 
            LTree<T>* temp;
            while(!q.isEmpty()){
                temp = q.deQueue();   //第一个元素出队并统计它的度数
				if(temp->children.getLength()>max_node){
					max_node = temp->children.getLength();
				} 
                for(int i=0;i<temp->children.getLength();i++){
                    q.enQueue(temp->children.getEleAtPos(i));          //所有孩子入队 
                }
            }
			return max_node;
        }
        
        int countNodeWithDeg(int x){
            //想法是遍历一遍树，然后统计每个节点的度数，用层序感觉是最好写的 
			int num = 0;    //存储度数为x的结点的个数  
			LinkQueue<LTree<T> *> q;
            q.enQueue(this);     //根节点入队 
            LTree<T>* temp;
            while(!q.isEmpty()){
                temp = q.deQueue();   //第一个元素出队并统计它的度数
				if(temp->children.getLength()==x){
					num++;
				} 
                for(int i=0;i<temp->children.getLength();i++){
                    q.enQueue(temp->children.getEleAtPos(i));          //所有孩子入队 
                }
            }
			return num;
        }
        

        // problem 3
        bool isDescendentOf(LTree<T> * lt){
            //test whether the current tree is a descendent of lt.
            //直接把它所有后代给找出来
			for(int i=0;i<lt->children.getLength();i++){
                if(this == lt->children.getEleAtPos(i)){
                	return true;
				}
				if(isDescendentOf(lt->children.getEleAtPos(i)) == true){
					return true;
				}
            }
            return false;
        }
        
        bool isAncestorOf(LTree<T> * lt){
            //test whether current node is ancestor of lt.
            //把上面那个代码翻一下就能写，因为他们是互为后代和子孙的
			LTree<T>* temp = this;
			for(int i=0;i<temp->children.getLength();i++){
                if(lt == temp->children.getEleAtPos(i)){
                	return true;
				}
				if((temp->children.getEleAtPos(i))->isAncestorOf(lt) == true){
					return true;
				}
            }
            return false;
        }
};

/* Question 2, 3 UPLOAD END */

/* Question 1 START */
LTree<int>* ques1(){
    // build the specified tree
    // TODO
    //逻辑是和int里面一样的 
    LTree<int>* Tree1 = new LTree<int>(25);
    Tree1->addChild(15);
    LTree<int>* tempTree1 = Tree1->getChild(15);
    tempTree1->addChild(10);
    tempTree1->addChild(22);
    LTree<int>* temptempTree1 = tempTree1->getChild(10);
	temptempTree1->addChild(12);
	LTree<int>* Tree2 = new LTree<int>(50);
	Tree2->addChild(70);
	LTree<int>* tempTree2 = Tree2->getChild(70);
	tempTree2->addChild(66);
	tempTree2->addChild(90);
    Tree1->addChild(Tree2);
    return Tree1;
}
/* Question 1 END */

void test1(){
    LTree<int>* r = ques1();
    r->printPreOrder();
    cout << endl;
    r->printPostOrder();
    cout << endl;
    r->printLevelOrder();
    cout << endl;
}

void test2(){
    LTree<char> testTree('A');
    testTree.addChild('B');
    LTree<char> testTree2('C');
    testTree2.addChild('G');
    testTree.addChild(&testTree2);
    LTree<char> * tmpTreeB = testTree.getChild('B');
    tmpTreeB->addChild('D');
    tmpTreeB->addChild('E');
    tmpTreeB->addChild('F');
    LTree<char> * tmpTreeE = tmpTreeB->getChild('E');
    tmpTreeE->addChild('H');
    tmpTreeE->addChild('I');
    //print trees now
    testTree.printPreOrder();
    cout << endl;
    testTree.printPostOrder();
    cout << endl;
    testTree.printLevelOrder();
    cout << endl;
    cout << "Height of the whole tree: " << testTree.height() << endl;
    cout << "Height of the B subtree: " << tmpTreeB->height() << endl;
    cout << "Degree of the whole tree: " << testTree.degree() << endl;
    cout << "Degree of the C subtree: " << testTree2.degree() << endl;
    cout << "Num of nodes with degree 0: " << testTree.countNodeWithDeg(0) << endl;
    cout << "Num of nodes with degree 1: " << testTree.countNodeWithDeg(1) << endl;
    cout << "Num of nodes with degree 2: " << testTree.countNodeWithDeg(2) << endl;
    cout << "Num of nodes with degree 3: " << testTree.countNodeWithDeg(3) << endl;
    cout << "Num of nodes with degree 4: " << testTree.countNodeWithDeg(4) << endl;
}

void test3(){
    LTree<char> testTree('A');
    testTree.addChild('B');
    LTree<char> testTree2('C');
    testTree2.addChild('G');
    testTree.addChild(&testTree2);
    LTree<char> * tmpTreeB = testTree.getChild('B');
    tmpTreeB->addChild('D');
    tmpTreeB->addChild('E');
    tmpTreeB->addChild('F');
    LTree<char> * tmpTreeE = tmpTreeB->getChild('E');
    tmpTreeE->addChild('H');
    tmpTreeE->addChild('I');
    //print tree now
    testTree.printPreOrder();
    cout << endl;
    testTree.printPostOrder();
    cout << endl;
    testTree.printLevelOrder();
    cout << endl;
    LTree<char> * tmpTreeI = tmpTreeE->getChild('I');
    cout << "Is I a descendent of B? " << (tmpTreeI->isDescendentOf(tmpTreeB) ? "Yes" : "No") << endl;
    cout << "Is I a descendent of C? " << (tmpTreeI->isDescendentOf(&testTree2) ? "Yes" : "No") << endl; 
    cout << "Is I a descendent of A? " << (tmpTreeI->isDescendentOf(&testTree) ? "Yes" : "No") << endl;
    cout << "Is I a descendent of I? " << (tmpTreeI->isDescendentOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B a descendent of I? " << (tmpTreeB->isDescendentOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of B? " << (tmpTreeB->isAncestorOf(tmpTreeB) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of A? " << (tmpTreeB->isAncestorOf(&testTree) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of C? " << (tmpTreeB->isAncestorOf(&testTree2) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of I? " << (tmpTreeB->isAncestorOf(tmpTreeI) ? "Yes" : "No") << endl;
    cout << "Is B an ancestor of E? " << (tmpTreeB->isAncestorOf(tmpTreeE) ? "Yes" : "No") << endl;
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}
