#include <iostream>
#include <iomanip>
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
        void insertLast(T x){
            insertEleAtPos(length,x);
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
struct Edge{
    T start;
    T end;
    int weight;
};


template <class T>
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices
        int** adjMatrix;
        bool directed;
        
        void BFShelper(int st, bool* visited){
        	visited[st] = true;
        	cout << verList.getEleAtPos(st) << " ";
        	LinkQueue<int> q;
        	q.enQueue(st);
        	while(!q.isEmpty()){
        		int tmp = q.deQueue();
        		for(int k=0;k<numVer;k++){
        			// investigate adjMatrix[tmp][k]
        			if(adjMatrix[tmp][k]==0) continue;
        			if(visited[k]) continue;
        			visited[k] = true;
        			cout << verList.getEleAtPos(k) << " ";
        			q.enQueue(k);
				}
			}
		}
		
		void DFShelper(int st, bool* visited){
			visited[st] = true;
			cout << verList.getEleAtPos(st) << " ";
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;
				if(visited[k]) continue;
				DFShelper(k,visited);
			}
		}
    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;
			
			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;		
			}
        }
        AMGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now. 
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;
			
			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;			
			}
			
			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end,eArr[i]->weight);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end, e.weight);
        }
        void addEdge(T st, T en, int weight=1){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;
            numEdge++;
            adjMatrix[sIndex][eIndex] = weight;
            if(!directed) adjMatrix[eIndex][sIndex] = weight;
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);            
        }
        void removeEdge(T st, T en){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) return;
            numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i) << " ";
                
            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
                }
            }
        }
        int** getMatrix(){
            return adjMatrix; 
        }
        //BFS
        void printBFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
            	visited[i] = false;
            
            for(int i=0;i<numVer;i++)
            	if(!visited[i])
            		BFShelper(i,visited);
            cout << endl;
        }
        //DFS
        void printDFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
            	visited[i] = false;
            
            for(int i=0;i<numVer;i++)
            	if(!visited[i])
            		DFShelper(i,visited);
            cout << endl;
        }
    
        
        //判断是否有环：使用DFS，如果DFS过程中出现指向已经在state数组中的点的边，且不是上一个点的边，
		//那么就有环
		
		bool is_rope_helper(int v, int* state){
	        state[v] = 1; // 递归栈
	        for(int k=0;k<numVer;k++){
	            if(adjMatrix[v][k]==0){
	            	continue;
				}
	            if(state[k] == 1){
				  // 回边 -> 有环
					return 1;
				}
	            if(state[k] == 0 && is_rope_helper(k,state)){
	            	return 1;
				}
	    	}
	        state[v] = 2;
	        return 0;
	    }
		
		bool is_rope(){ // 有环返回 true
	        int state[numVer]; // 0=未访问,1=栈中,2=完成
	        for(int i=0;i<numVer;i++){
	        	state[i]=0;
			}
	        for(int i=0;i<numVer;i++){
	            if(state[i]==0){
	                if(is_rope_helper(i,state)){
	                    return 1;
	                }
	            }
	        }
	        return 0;
	    }
		
		void AOE(){
			//初始化四个重要的数组， 
			int ve[numVer] = {0};
			int vl[numVer];
			int e[numEdge];
			int l[numEdge];
			
			//统计顶点的入度
			int ins[numVer];
			for(int i=0;i<numVer;i++){
				int count1 = 0;    //统计入度 
				for(int j=0;j<numVer;j++){
					if(adjMatrix[j][i] != 0){
						count1++; 
					}
				}
				ins[i] = count1;
			} 

			
			//使用栈完成topo排序，并计算ve[k] 
			LinkStack<int> s1;
        	for(int i=0;i<numVer;i++){
        		if(ins[i] == 0){
        			s1.push(i);    //入度为0的入栈 
				}
			}
			
			while(!s1.isEmpty()){    //栈非空则进行循环 
				int temp1 = s1.pop();    //弹栈 
				//计算ve 
				int max = 0;
				for(int i=0;i<numVer;i++){
					if(adjMatrix[i][temp1] != 0){
						if(max < adjMatrix[i][temp1] + ve[i]){
							max = adjMatrix[i][temp1] + ve[i];
						}
					}
				}
				ve[temp1] = max;
				for(int i=0;i<numVer;i++){
					if(adjMatrix[temp1][i] != 0){
						ins[i]--;
						if(ins[i] == 0){
							s1.push(i);
						} 
					}
				}
			}
			
			//统计顶点的出度
			int outs[numVer];
			for(int i=0;i<numVer;i++){
				int count2 = 0;    //统计出度 
				for(int j=0;j<numVer;j++){
					if(adjMatrix[i][j] != 0){
						count2++; 
					}
				}
				outs[i] = count2;
			} 
			

			
			//使用栈完成逆topo排序，并计算vl[k] 
			for(int i=0;i<numVer;i++){
				vl[i] = ve[numVer-1];
			}
			
			LinkStack<int> s2;
        	for(int i=0;i<numVer;i++){
        		if(outs[i] == 0){
        			s2.push(i);    //出度为0的入栈 
				}
			}
			
			while(!s2.isEmpty()){    //栈非空则进行循环 
				int temp2 = s2.pop();    //弹栈 
				//计算vl 
				int min = vl[numVer-1];
				for(int i=0;i<numVer;i++){
					if(adjMatrix[temp2][i] != 0){
						if(min > vl[i] - adjMatrix[temp2][i]){
							min = vl[i] - adjMatrix[temp2][i];
						}
					}
				}
				vl[temp2] = min;
				for(int i=0;i<numVer;i++){
					if(adjMatrix[i][temp2] != 0){
						outs[i]--;
						if(outs[i] == 0){
							s2.push(i);
						} 
					}
				}
			}


			
			//计算e
			int index1 = 0;    //数组e的增量 
			for(int i=0;i<numVer;i++){
				for(int j=0;j<numVer;j++){
					if(adjMatrix[i][j] != 0){
						e[index1] = ve[i];
						index1++;
					}
				}
			}
			
			//计算l 
			int index2 = 0;    //数组l的增量 
			for(int i=0;i<numVer;i++){
				for(int j=0;j<numVer;j++){
					if(adjMatrix[i][j] != 0){
						l[index2] = vl[j] - adjMatrix[i][j];
						index2++;
					}
				}
			}
			
			//接下来开始算钱 
			int money[numVer]; 
			money[0] = 0;
			for(int i=0;i<numVer;i++){
				money[i] = ve[i];
			} 
			
			cout<<"Results:"<<endl;
			cout<<"Person    Pay"<<endl;
			cout<<left;
			for(int i=0;i<numVer;i++){
				cout<<setw(10)<<i+1<<setw(10)<<money[i]<<endl;
			}
		} 
};

//如何类比AOE和这个题目？
//其实最少的钱就是最少的时间
//如果不出现无解的情况，那么直接套用AOE的算法
//何时会无解呢，不是DAG

int main(){
	int m;    //员工数 
	int n;    //比较表现数
	cin>>m;
	cin>>n;
	
	//初始化顶点列表 
	int ver[m];
	for(int i=0;i<m;i++){
		ver[i] = i+1;
	}
	
	//初始化图
	AMGraph<int> amg(ver, m, true); 
	
	//接下来给它加边，这里接收到的n就有用了 
	for(int i=0;i<n;i++){
		int st;    //起点 
		int en;    //终点 
		int w;    //权重 
		cin>>st>>en>>w;
		amg.addEdge(st, en, w); 
	}
	
/*
	//检查：图初始化是否正确
	amg.printGraph(); 
	//没有问题
*/
	
	//先判断是否有环：相关函数写在类里，这里直接调用 
 	if(amg.is_rope()){
 		cout<<"No possible solution!"<<endl;
 		return 0;
	 }
	 else{
/*
	 	//检查：判断环的函数是否有用 
	 	cout<<1;
		//有用
*/

		//准备工作已经就绪，接下来开始写AOE
		//这个也把它写成一个函数，写在类里面
		amg.AOE();
		
	 	return 0;
	 }
	 
}



