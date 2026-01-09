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
};

/* UPLOAD START */

template <class T>
struct graphNode{
    T data;    //结点储存的数据 
    VecList<graphNode<T>*>* ins;    //入边列表 
    VecList<graphNode<T>*>* outs;    //出边列表 
};

template <class T>
class LGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    //使用邻接表实现的图 
	private:
        int numVer;    //顶点数量 
        VecList<graphNode<T>*> verList;    //顶点列表 
        bool directed;    //是否为有向图 
        
        // 在顶点列表中查找特定数据的索引位置
        int findIndex(T x){
            for(int i=0;i<numVer;i++){
                if(verList.getEleAtPos(i)->data == x)
                    return i;
            }
            return -1;
        }
        
        void BFShelper(int st, bool* visited){
        	visited[st] = true;
        	LinkQueue<int> q;
        	q.enQueue(st);
        	cout << verList.getEleAtPos(st)->data << " ";    //这里就是把数组换成了链表 
        	while(!q.isEmpty()){
        	    int tmp = q.deQueue();
        	    graphNode<T>* tmpNode = verList.getEleAtPos(tmp);
        	    for(int j=0;j<tmpNode->outs->getLength();j++){    //tmpNode->是个Veclist()去调用它的长度 
        	        int target = verList.locateEle(tmpNode->outs->getEleAtPos(j));
        	        if(visited[target]) continue;    //和之前一样 
        	        visited[target] = true;
        	        cout << verList.getEleAtPos(target)->data << " ";
        	        q.enQueue(target);
        	    }
        	}
		}
		
		void DFShelper(int st, bool* visited){
			visited[st] = true;
			graphNode<T>* tmpNode = verList.getEleAtPos(st);
			cout << verList.getEleAtPos(st)->data << " ";
			for(int j=0;j<tmpNode->outs->getLength();j++){
			    int target = verList.locateEle(tmpNode->outs->getEleAtPos(j));    //当前位置出边列表的第j个位置的指针，定位它在verList里面的位置 
			    if(visited[target]) continue;
			    DFShelper(target,visited);
			}
		}
		
    public:
        LGraph(){ // we don't want this used.
        }
        
        // 构造函数1：只创建顶点，不添加边
        LGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            
            numVer = 0;
            directed = dir;
            // 添加所有顶点
            for(int i=0;i<n;i++){
                addVertex(arr[i]);
            }
        }
        
        // 构造函数2：创建顶点并添加边
        LGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now. 
            
            numVer = 0;
            directed = dir;
            // 添加所有顶点
            for(int i=0;i<n;i++){
                addVertex(arr[i]);
            }
			// 添加所有边 
			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end);
			}
        }
        //析构函数：释放所有动态分配的内存（下面有new） 
        ~LGraph(){
            for(int i=0;i<numVer;i++){
                delete verList.getEleAtPos(i)->ins;
                delete verList.getEleAtPos(i)->outs;
                delete verList.getEleAtPos(i);
            }
        }
        //加边 
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end);
        }
        //加边 
        void addEdge(T st, T en){
            int sIndex = findIndex(st);    // 查找起始顶点索引
            int eIndex = findIndex(en);    // 查找结束顶点索引
            graphNode<T>* sNode = verList.getEleAtPos(sIndex);    //获取该点的指针 
            graphNode<T>* eNode = verList.getEleAtPos(eIndex);
            // 在起点的出边列表添加出边（sNode -> eNode）
			if(sNode->outs->locateEle(eNode)==-1)    //如果没变，就加边 
                sNode->outs->insertLast(eNode);
            // 在终点的入边列表添加入边（eNode <- sNode）
			if(eNode->ins->locateEle(sNode)==-1)
                eNode->ins->insertLast(sNode);
            if(!directed){    //无向图反向边也要添加 
                if(eNode->outs->locateEle(sNode)==-1)
                    eNode->outs->insertLast(sNode);
                if(sNode->ins->locateEle(eNode)==-1)
                    sNode->ins->insertLast(eNode);
            }
        }
        //删边 
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);            
        }
        //原理同前 
        void removeEdge(T st, T en){
            int sIndex = findIndex(st);
            int eIndex = findIndex(en);
            graphNode<T>* sNode = verList.getEleAtPos(sIndex);
            graphNode<T>* eNode = verList.getEleAtPos(eIndex);
            if(sNode->outs->locateEle(eNode)!=-1)
                sNode->outs->deleteEleAtPos(sNode->outs->locateEle(eNode));
            if(eNode->ins->locateEle(sNode)!=-1)
                eNode->ins->deleteEleAtPos(eNode->ins->locateEle(sNode));
            if(!directed){
                if(eNode->outs->locateEle(sNode)!=-1)
                    eNode->outs->deleteEleAtPos(eNode->outs->locateEle(sNode));  //无向图删除反向边 
                if(sNode->ins->locateEle(eNode)!=-1)
                    sNode->ins->deleteEleAtPos(sNode->ins->locateEle(eNode));
            }
        }
        //添加新顶点 
        void addVertex(T x){
            numVer++;
            graphNode<T>* tmpNode = new graphNode<T>;
            tmpNode->data = x;
            tmpNode->ins = new VecList<graphNode<T>*>;    //初始化新顶点的入边列表 
            tmpNode->outs = new VecList<graphNode<T>*>;    //初始化新顶点的出边列表 
            verList.insertLast(tmpNode);
        }
        // 打印图的顶点和边信息
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i)->data << " ";
            cout << endl << "Edges:" << endl;
            // 根据图类型选择边表示符号
			char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            // 遍历所有可能的边，找两遍点，有边输出边 
			for(int i=0;i<numVer;i++){     
                graphNode<T>* tmpNode = verList.getEleAtPos(i);     
                for(int j=(directed ? 0 : i+1);j<numVer;j++){    //如果有向就j=0（遍历全部），如果无向就i+1开始遍历 
                    graphNode<T>* targetNode = verList.getEleAtPos(j);
                    if(tmpNode->outs->locateEle(targetNode)!=-1)    //如果有边 
                        cout << sLeft << tmpNode->data << "," << targetNode->data << sRight << endl;
                }
            }
        }
        // 获取图的邻接矩阵表示
        int** getMatrix(){
            int** adjMatrix;
            adjMatrix = new int*[numVer];     
            for(int i=0;i<numVer;i++){
                adjMatrix[i] = new int[numVer];    //初始化
                //有边就是1，无边就是0 
				for(int j=0;j<numVer;j++){
                    if(verList.getEleAtPos(i)->outs->locateEle(verList.getEleAtPos(j))!=-1)    //顶点出边的顶点列表用locateEle找是否有元素 
                        adjMatrix[i][j] = 1;
                    else
                        adjMatrix[i][j] = 0;
                }
            }
            return adjMatrix;
        }
        //BFS
        //大函数和之前一致 
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
        //大函数和之前一致 
        void printDFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
                visited[i] = false;
            for(int i=0;i<numVer;i++)
                if(!visited[i])
                    DFShelper(i,visited);
            cout << endl;
        }
        
        // question 1
        //强连通分量就是互相可达关系的等价类。所以只要他们相互可达就可以了
		//所以只需要他们相互可达，换而言之，对每个顶点u进行一次dfs，如果u的dfs有v
		//对v进行一次dfs，如果v的dfs也有u，将v和u放在一个组里面 
        
        //辅助函数1：DFS辅助函数 
		void scc_dfs_helper(int st, bool* visited){
			visited[st] = true;
			graphNode<T>* tmpNode = verList.getEleAtPos(st);
			for(int j=0;j<tmpNode->outs->getLength();j++){
			    int target = verList.locateEle(tmpNode->outs->getEleAtPos(j));    //当前位置出边列表的第j个位置的指针，定位它在verList里面的位置 
			    if(visited[target]){
			    	continue;
				}
			    scc_dfs_helper(target,visited);
			}
		} 
		
		//辅助函数2：对任一点的DFS 
		void scc_dfs(int ver, bool* visited){
            for(int i=0;i<numVer;i++){
            	visited[i] = false;
			}
            scc_dfs_helper(ver,visited);
		}
        
        void printStrongCC(){
        	
        	int idx = 0;    //属于Component的增量 
        	bool reach[numVer][numVer] = {0};    //可达矩阵 
        	bool visited[numVer];    //visited数组，用于填写可达矩阵 
        	
            for(int i=0;i<numVer;i++){
				scc_dfs(i,visited);
				for (int j = 0; j < numVer; j++) {
            		reach[i][j] = visited[j];    //填写可达矩阵 
        		}
			}
			
			//接下来进行分组:初始化分组数组，group[i]等于几就是属于第几组 
			int group[numVer];
			for(int i=0;i<numVer;i++){
				group[i] = -1;
			} 
			
			//分组，若reach[i][j] && reach[j][i]就分到一组 
			for(int i=0;i<numVer;i++){
				if(group[i] != -1){
					continue;    //已分组直接跳过 
				}
				group[i] = idx;    //分到一个组 
				for(int j=0;j<numVer;j++){
					if(group[j] == -1){    //j未分组 
						if(reach[i][j] && reach[j][i]){
							group[j] = idx;
						}
					} 
				}
				idx++;
			}
			//按照如上算法分的组，一定满足组序数较小的里面，有较小的点序数
			 
			//输出
			for(int i=0;i<idx;i++){
				cout<<"Component "<<i<<":";
				for(int j=0;j<numVer;j++){
					if(group[j] == i){
						cout<<" "<<j+1;
					}
				}
				cout<<endl; 
			}
        }
        
        void AMGraph<T>::printStrongCC_Kosaraju(){
		    if(!directed){
		        cout << "Graph is undirected, SCC is just connected components." << endl;
		        return;
		    }
		
		    // ---------- 第一步：普通 DFS，按完成时间记录顺序 ----------
		    bool *visited = new bool[numVer];
		    for(int i=0;i<numVer;i++) visited[i] = false;
		
		    // 用一个栈（这里用简单的数组 + 栈顶指针）保存“退出递归的顺序”
		    int *stack = new int[numVer];
		    int topIndex = -1;
		
		    // 局部的 DFS 函数，用于第一次 DFS
		    std::function<void(int)> dfs1 = [&](int u){
		        visited[u] = true;
		        // 遍历所有邻接点
		        for(int v=0; v<numVer; v++){
		            if(adjMatrix[u][v] != 0 && !visited[v]){
		                dfs1(v);
		            }
		        }
		        // 递归退出时将顶点入栈
		        stack[++topIndex] = u;
		    };
		
		    // 对所有顶点做 DFS（防止图不连通）
		    for(int i=0; i<numVer; i++){
		        if(!visited[i]){
		            dfs1(i);
		        }
		    }
		
		    // ---------- 第二步：构造转置图（边反向） ----------
		    int **transpose = new int*[numVer];
		    for(int i=0;i<numVer;i++){
		        transpose[i] = new int[numVer];
		        for(int j=0;j<numVer;j++){
		            // 原图 i->j 变成转置图 j->i
		            transpose[i][j] = 0;
		        }
		    }
		
		    for(int i=0;i<numVer;i++){
		        for(int j=0;j<numVer;j++){
		            if(adjMatrix[i][j] != 0){
		                transpose[j][i] = adjMatrix[i][j];
		            }
		        }
		    }
		
		    // ---------- 第三步：在转置图上按“完成时间逆序”做 DFS ----------
		    for(int i=0;i<numVer;i++) visited[i] = false;
		
		    std::function<void(int)> dfs2 = [&](int u){
		        visited[u] = true;
		        cout << verList.getEleAtPos(u) << " "; // 输出当前 SCC 的顶点
		        for(int v=0; v<numVer; v++){
		            if(transpose[u][v] != 0 && !visited[v]){
		                dfs2(v);
		            }
		        }
		    };
		
		    cout << "Strongly Connected Components (Kosaraju):" << endl;
		    // 按照 stack 中从栈顶到栈底（即完成时间从大到小）的顺序
		    while(topIndex >= 0){
		        int u = stack[topIndex--];
		        if(!visited[u]){
		            // u 作为这次 DFS 的起点，得到一个 SCC
		            cout << "{ ";
		            dfs2(u);
		            cout << "}" << endl;
		        }
		    }
		
		    // ---------- 释放内存 ----------
		    for(int i=0;i<numVer;i++){
		        delete [] transpose[i];
		    }
		    delete [] transpose;
		    delete [] visited;
		    delete [] stack;
		}
		
		void AMGraph<T>::printStrongCC_Tarjan(){
		    if(!directed){
		        cout << "Graph is undirected, SCC is just connected components." << endl;
		        return;
		    }
		
		    // 初始化辅助数组
		    int *dfn = new int[numVer];       // dfn[u]：访问序号
		    int *low = new int[numVer];       // low[u]：能回到的最早序号
		    bool *inStack = new bool[numVer]; // 是否在栈中
		    int timeStamp = 0;                // 全局时间戳
		    int *stack = new int[numVer];     // 用数组模拟栈
		    int topIndex = -1;
		
		    for(int i=0;i<numVer;i++){
		        dfn[i] = 0;       // 0 表示还未访问
		        low[i] = 0;
		        inStack[i] = false;
		    }
		
		    cout << "Strongly Connected Components (Tarjan):" << endl;
		
		    // Tarjan 的 DFS 主过程
		    std::function<void(int)> tarjanDFS = [&](int u){
		        dfn[u] = low[u] = ++timeStamp;
		        stack[++topIndex] = u;
		        inStack[u] = true;
		
		        // 扫描 u 的所有出边
		        for(int v=0; v<numVer; v++){
		            if(adjMatrix[u][v] == 0) continue; // 无边
		
		            if(dfn[v] == 0){
		                // v 还未访问
		                tarjanDFS(v);
		                low[u] = std::min(low[u], low[v]); // 回溯时更新 low[u]
		            }
		            else if(inStack[v]){
		                // (u,v) 是一条指向栈中结点的“后向边”或“横向边”
		                low[u] = std::min(low[u], dfn[v]);
		            }
		        }
		
		        // 如果 u 是当前 SCC 的根结点（low[u] == dfn[u]）
		        if(low[u] == dfn[u]){
		            cout << "{ ";
		            while(true){
		                int x = stack[topIndex--];
		                inStack[x] = false;
		                cout << verList.getEleAtPos(x) << " ";
		                if(x == u) break; // 到达整块 SCC 的起点
		            }
		            cout << "}" << endl;
		        }
		    };
		
		    // 对所有点运行一次 DFS（避免图不连通）
		    for(int i=0; i<numVer; i++){
		        if(dfn[i] == 0){
		            tarjanDFS(i);
		        }
		    }
		
		    delete [] dfn;
		    delete [] low;
		    delete [] inStack;
		    delete [] stack;
		}
};

/* UPLOAD END */

void printMatrix(int ** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void test0(){
    int ver[9] = {1,2,3,4,5,6,7,8,9};
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{1,2};
    edges[1] = new Edge<int>{1,3};
    edges[2] = new Edge<int>{1,4};
    edges[3] = new Edge<int>{2,3};
    edges[4] = new Edge<int>{2,4};
    edges[5] = new Edge<int>{3,4};
    edges[6] = new Edge<int>{5,8};
    edges[7] = new Edge<int>{5,9};
    edges[8] = new Edge<int>{6,8};
    edges[9] = new Edge<int>{9,6};
    
    LGraph<int> amg1(ver,9,edges,10);
    LGraph<int> amg2(ver,9,edges,10,true);
    
    amg1.addEdge(7,3);
    amg1.addEdge(7,4);
    
    amg2.addEdge(3,7);
    amg2.addEdge(7,9);
    amg2.removeEdge(6,8);
    amg2.addVertex(10);
    amg2.addEdge(10,5);
    amg2.addVertex(11);
    amg2.addEdge(5,11);
    
    cout << "Graph 1: " << endl;
    amg1.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg1.getMatrix(),9);
    cout << "BFS:" << endl;
    amg1.printBFS();
    cout << "DFS:" << endl;
    amg1.printDFS();
    
    cout << "Graph 2: " << endl;
    amg2.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg2.getMatrix(),11);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();
    
}

void test1(){
    int ver[6] = {1,2,3,4,5,6};
    
    LGraph<int> lg1(ver,6,true);
    lg1.addEdge(1,2);
    lg1.addEdge(2,3);
    lg1.addEdge(3,4);
    lg1.addEdge(4,5);
    lg1.addEdge(5,6);
    
    lg1.printStrongCC();
    cout << endl;
    
    lg1.addEdge(3,1);
    lg1.addEdge(6,4);
    
    lg1.printStrongCC();
    cout << endl;
}



int main(){
    //test0();
    test1();
    return 0;
}
