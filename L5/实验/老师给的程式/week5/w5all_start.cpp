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
        VecList<LTree<T> *> children;
    public:
        LTree(){
			
        }
        LTree(T x){
            data = x;
        }
        ~LTree(){
            
        }
        void addChild(LTree<T>* lt){
            children.insertEleAtPos(children.getLength(),lt);
        }
        void addChild(T x){
            LTree<T>* lt = new LTree<T>(x);
            addChild(lt);
        }
        LTree<T>* getChild(T x){
            for(int i=0;i<children.getLength();i++){
                if(children.getEleAtPos(i)->data == x)
                    return children.getEleAtPos(i);
            }
            return NULL;
        }
        void setData(T x){
            data = x;
        }
        T getData(){
            return data;
        }
        void printPreOrder(){
            cout << data << " ";
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
            LinkQueue<LTree<T> *> q;
            q.enQueue(this);
            LTree<T>* tmp;
            while(!q.isEmpty()){
                tmp = q.deQueue();
                cout << tmp->data << " ";
                for(int i=0;i<tmp->children.getLength();i++){
                    q.enQueue(tmp->children.getEleAtPos(i));
                }
            }
        }
        
        // problem 2
        int height(){
            
        }
        int degree(){
            
        }
        
        int countNodeWithDeg(int x){
            
        }
        

        // problem 3
        bool isDescendentOf(LTree<T> * lt){
            //test whether the current tree is a descendent of lt.
            
        }
        
        bool isAncestorOf(LTree<T> * lt){
            //test whether current node is ancestor of lt.
            
        }
};

/* Question 2, 3 UPLOAD END */

/* Question 1 START */
LTree<int>* ques1(){
    // build the specified tree
    // TODO
    
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