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
        int height;    //新加一个高度 
        void updateHeights(){    //用于更新高度 
            int hL = (left==NULL ? 0 : left->height);
            int hR = (right==NULL ? 0 : right->height);
            height = (hL > hR ? hL : hR) + 1;    //左子树右子树取最大再加一 
            if(parent==NULL) return;
            parent->updateHeights();    //递归：让父节点也同步更新高度
        }
    public:
        BinTree(){
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
        }
        ~BinTree(){

        }
        void addLChild(BinTree<T>* bt){
            left = bt;
            updateHeights();
            if(bt==NULL) return;
            bt->parent = this;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
            updateHeights();
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
        int getHeight(){
            return height;    //访问类成员height的一个接口 
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

template <class T>
class AVLTree{
    // T better have its comparison operators overloaded.
    // we assume no duplicate elements
    // use an empty root node
    private:
        BinTree<T>* root;
        int nodeCount;

        BinTree<T>* findParent(T x){
            BinTree<T>* ptr = root;
            BinTree<T>* comp = root->getRChild();
            while(comp!=NULL){
                if(comp->getData()==x){
                    return ptr;
                }
                else if(comp->getData()<x){
                    // go to right side
                    ptr = comp;
                    comp = comp->getRChild();
                }
                else{
                    ptr = comp;
                    comp = comp->getLChild();
                }
            }
            return ptr;
        }
        
		//左旋转，以bt节点为轴
        void rotateLeft(BinTree<T>* bt){
        	//左旋转的定义是：(a)将其右子结点->新的根
            //(b)该结点->新根的左子结点
            //(c)原右子结点的左子结点->该结点的右子结点 
            BinTree<T>* btP = bt->getParent();
            BinTree<T>* btA = bt->getRChild();
            bt->addRChild(btA->getLChild());    //将它右孩子的左孩子变成它的右孩子(c)
            if(btP->getLChild()==bt){    //如果bt是左孩子 
                btA->addLChild(bt);    //把bt变成bt右孩子的左孩子(b) 
                btP->addLChild(btA);    //把(原来已存储好的)bt的右孩子变成心得根结点(bt双亲结点的左孩子) 
            }
            else{
                btA->addLChild(bt);
                btP->addRChild(btA);    //就这里左右改下 
            }
        }

		//右旋转，以bt节点为轴
        void rotateRight(BinTree<T>* bt){
        	//右旋转的定义是：(a)将其左子结点->新的根
            //(b)该结点->新根的右子结点
            //(c)原左子结点的右子结点->该结点的左子结点 
            BinTree<T>* btP = bt->getParent();
            BinTree<T>* btA = bt->getLChild();
            bt->addLChild(btA->getRChild());
            if(btP->getLChild()==bt){
                btA->addRChild(bt);
                btP->addLChild(btA);
            }
            else{
                btA->addRChild(bt);
                btP->addRChild(btA);
            }
        }

		//保证以bt为根的子树平衡，按定义旋转就行 
        void balanceTree(BinTree<T>* bt){
            if(bt==root) return;
            //cout << "Here? ";
            int hL = (bt->getLChild()==NULL ? 0 : bt->getLChild()->getHeight());
            int hR = (bt->getRChild()==NULL ? 0 : bt->getRChild()->getHeight());
            //cout << bt->getData() << " " << hL << " " << hR << endl;
            if(hL-hR >= 2){ // LL or LR 左边大 
                BinTree<T>* btL= bt->getLChild();
                int hLL = (btL->getLChild()==NULL ? 0 : btL->getLChild()->getHeight());
                int hLR = (btL->getRChild()==NULL ? 0 : btL->getRChild()->getHeight());
                if(hLL >= hLR){ // LL type
                    //cout << "LL type" << endl;
                    rotateRight(bt);
                }
                else{ // LR type
                    //cout << "LR type" << endl;
                    rotateLeft(btL);
                    rotateRight(bt);
                }
            }
            else if(hR-hL>=2){ // RR or RL
                BinTree<T>* btR= bt->getRChild();
                int hRL = (btR->getLChild()==NULL ? 0 : btR->getLChild()->getHeight());
                int hRR = (btR->getRChild()==NULL ? 0 : btR->getRChild()->getHeight());
                if(hRR >= hRL){ // RR type
                    //cout << "RR type" << endl;
                    rotateLeft(bt);
                }
                else{ // RL type
                    //cout << "RL type" << endl;
                    rotateRight(btR);
                    rotateLeft(bt);
                }
            }
            balanceTree(bt->getParent());
        }
    public:
        AVLTree(){
            nodeCount = 0;
            root = new BinTree<T>;
        }

        AVLTree(T* arr, int n){ // insert whole array
            nodeCount = 0;
            root = new BinTree<T>;

            for(int i=0;i<n;i++){
                insertData(arr[i]);
            }
        }
        ~AVLTree(){
            // LinkQueue destroying every node
            LinkQueue<BinTree<T>*> q;
            q.enQueue(root);
            while(!q.isEmpty()){
                BinTree<T>* tmp = q.deQueue();
                if(tmp->getLChild()!=NULL) q.enQueue(tmp->getLChild());
                if(tmp->getRChild()!=NULL) q.enQueue(tmp->getRChild());
                delete tmp;
            }
        }
        bool isEmpty(){
            return nodeCount==0;
        }
        void insertData(T x){
            if(searchData(x)) return;
            BinTree<T>* tmp = findParent(x);
            nodeCount++;
            if(tmp==root){
                root->addRChild(x);
                return;
            }
            if(tmp->getData() > x){
                // left side
                tmp->addLChild(x);
                balanceTree(tmp);
            }
            else{
                tmp->addRChild(x);
                balanceTree(tmp);
            }
        }
        bool searchData(T x){
            BinTree<T>* tmp = findParent(x);
            if(tmp==root){
                return tmp->getRChild()!=NULL;
            }
            if(tmp->getData() > x){
                // left side
                return tmp->getLChild()!=NULL;
            }
            else{
                return tmp->getRChild()!=NULL;
            }
        }
        bool deleteData(T x){
            if(!searchData(x)) return false;
            BinTree<T>* tmp = findParent(x);
            BinTree<T>* xNode;
            if(tmp==root){
                xNode = root->getRChild();
            }
            else if(tmp->getData() > x){
                xNode = tmp->getLChild();
            }
            else{
                xNode = tmp->getRChild();
            }
            if(xNode->getLChild()==NULL && xNode->getRChild()==NULL){
                // deleting a leaf node
                if(tmp->getLChild()==xNode) tmp->addLChild(nullptr);
                else tmp->addRChild(nullptr);
                balanceTree(tmp);
                nodeCount--;
                delete xNode;
                return true;
            }
            else if(xNode->getLChild()==NULL){
                // only has RChild
                if(tmp->getLChild()==xNode){
                    tmp->addLChild(xNode->getRChild());
                }
                else{
                    tmp->addRChild(xNode->getRChild());
                }
                balanceTree(tmp);
                nodeCount--;
                delete xNode;
                return true;
            }
            else if(xNode->getRChild()==NULL){
                // only has LChild
                if(tmp->getLChild()==xNode){
                    tmp->addLChild(xNode->getLChild());
                }
                else{
                    tmp->addRChild(xNode->getLChild());
                }
                balanceTree(tmp);
                nodeCount--;
                delete xNode;
                return true;
            }
            // have both children
            BinTree<T>* largestInLeft = xNode->getLChild();
            BinTree<T>* largestParent = xNode;
            while(largestInLeft->getRChild()!=NULL){
                largestParent = largestInLeft;
                largestInLeft = largestInLeft->getRChild();
            }
            xNode->setData(largestInLeft->getData());
            // the rest is to delete largestInLeft
            // largestInLeft only has LChild
            if(largestParent!=xNode){
                largestParent->addRChild(largestInLeft->getLChild());
            }
            else largestParent->addLChild(largestInLeft->getLChild());
            balanceTree(largestParent);
            delete largestInLeft;
            nodeCount--;
            return true;
        }
        void printInOrder(){
            cout << "In order: ";
            if(nodeCount!=0){
                root->getRChild()->printInOrderR();
            }
            cout << endl;
        }
        void printPreOrder(){
            cout << "Pre order: ";
            if(nodeCount!=0){
                root->getRChild()->printPreOrderR();
            }
            cout << endl;
        }
        void printPostOrder(){
            cout << "Post order: ";
            if(nodeCount!=0){
                root->getRChild()->printPostOrderR();
            }
            cout << endl;
        }


        void printLevelOrder(){
            cout << "Level order: ";
            if(nodeCount!=0){
                root->getRChild()->printLevelOrder();
            }
            cout << endl;
        }
};

void test0(){
    AVLTree<int> bst;
    bst.insertData(8);
    bst.insertData(3);
    bst.insertData(10);
    bst.insertData(1);
    bst.insertData(6);
    bst.insertData(4);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    bst.insertData(7);
    bst.insertData(14);
    bst.insertData(13);
    // print preorder and inorder, for uniquely looking at this BST.
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    cout << "Remove 1:" << endl;
    bst.deleteData(1);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    cout << "Remove 14:" << endl;
    bst.deleteData(14);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    cout << "Remove 8:" << endl;
    bst.deleteData(8);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    cout << "Insert 9 and remove 10: " << endl;
    bst.insertData(9);
    bst.deleteData(10);
    bst.deleteData(8);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
}

void test1(){
    int a[3] = {1,2,3};
    AVLTree<int> bst(a,3);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;

    cout << "Remove all: " << endl;
    bst.deleteData(4);
    bst.deleteData(1);
    bst.deleteData(2);
    bst.deleteData(3);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    cout << "Insert again: " << endl;
    for(int i=1;i<=7;i++){
        bst.insertData(i);
    }
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
}

int main(){
    test0();
    test1();
    return 0;
}
