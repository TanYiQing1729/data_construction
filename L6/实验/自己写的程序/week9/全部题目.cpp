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
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices    //顶点序列 
        int** adjMatrix;    //邻接矩阵 
        bool directed;
        VecList<T> not_0;    //用于第二问
        
        void BFShelper(int st, bool* visited){
        	visited[st] = true;    //标记已访问 
        	cout << verList.getEleAtPos(st) << " ";    //输出起点 
        	LinkQueue<int> q;
        	q.enQueue(st);    //顶点进队 
        	while(!q.isEmpty()){    //非空队时 
        		int tmp = q.deQueue();    //顶点出队 
        		for(int k=0;k<numVer;k++){    //考虑顶点的邻接点 
        			// investigate adjMatrix[tmp][k]
        			if(adjMatrix[tmp][k]==0) continue;    //零边跳过 
        			if(visited[k]) continue;    //访问过跳过 
        			visited[k] = true;    //邻接点已访问 
        			cout << verList.getEleAtPos(k) << " ";    //输出未被访问过的邻接点 
        			q.enQueue(k);    //邻接点进队 
				}
			}
		}
		
		void DFShelper(int st, bool* visited){
			visited[st] = true;    //标记为已经访问
			cout << verList.getEleAtPos(st) << " ";    //输出 
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;    //不邻接，跳过 
				if(visited[k]) continue;    //访问过，跳过 
				DFShelper(k,visited);    //对下一个点递归 
			}
		}
    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.    //没有输入边 
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);    //传入顶点序列 
			}
			directed = dir;    //是否有向 
			
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
            // edges to be added now.     //输入了边 
            
            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;
			
			adjMatrix = new int*[n];    //动态申请二维数组空间 
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;			
			}
			
			for(int i=0;i<e;i++){    //输入边，这里因为传入的是一个指针，所以用第二个加边的函数 
				addEdge(eArr[i]->start,eArr[i]->end);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;    //一组一组删掉 
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end);    //变为下一个函数的工作 
        }
        void addEdge(T st, T en){
            int sIndex = verList.locateEle(st);    //在顶点序列中找到起点位置 
            int eIndex = verList.locateEle(en);    //在顶点序列中找到终点位置 
            if(adjMatrix[sIndex][eIndex]!=0) return;    //邻接矩阵非零，本来有边，不处理 
            numEdge++;    //边数加一 
            adjMatrix[sIndex][eIndex] = 1;    //邻接矩阵改为1 
            if(!directed) adjMatrix[eIndex][sIndex] = 1;    //如果无向图，根据对称性，转置位置+1 
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);            //同上 
        }
        void removeEdge(T st, T en){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) return;    //原理和加边很像，1改成0 
            numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;        //输出顶点序列 
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i) << " ";
                
            cout << endl << "Edges:" << endl;    //输出边的序列 
            char sLeft = (directed ? '<' : '(');    //无向边和有向边 
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){    //无向边只用考虑上半部分 
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] == 1) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight <<endl; 
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){    //有向边考虑整个 
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] == 1) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight <<endl; 
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
            	visited[i] = false;    //初始化visited数组 
            
            for(int i=0;i<numVer;i++)
            	if(!visited[i])    //如果没被访问 
            		BFShelper(i,visited);    //就进辅助函数 
            cout << endl;
        }
        //DFS
        void printDFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
            	visited[i] = false;    //初始化visited数组 
            
            for(int i=0;i<numVer;i++)
            	if(!visited[i])    //如果没被访问 
            		DFShelper(i,visited);    //就进辅助函数 
            cout << endl;
        }
        
        // question 1
		//这是自己写的辅助函数 
        void DFS_helper(int st, bool* visited){
			visited[st] = true;    //标记为已经访问    
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;    //不邻接，跳过 
				if(visited[k]) continue;    //访问过，跳过 
				DFS_helper(k,visited);    //对下一个点递归 
			}
		} 
        
        bool isCycleGraph(){
            // assume undirected graph
            //思路：先判断度2，再判断连通。度2很简单，只要遍历adj矩阵，连通则是通过看DFS or BFS会不会更换顶点
			//上面写了一个辅助函数 
			
			//度2判断 
			for(int i=0;i<numVer;i++){
				int count = 0;
				for(int j=0;j<numVer;j++){
					if(adjMatrix[i][j] == 1){
						count++;
					}
				}
				if(count != 2){
					return 0;
				}
			} 
			
			//连通判断
			//这里手写一个DFS 
			bool visited[numVer];
            for(int i=0;i<numVer;i++){
            	visited[i] = false;    //初始化visited数组
			} 
            
            int count2 = 0;  //用于计数，看看是不是不用更换顶点 
            for(int i=0;i<numVer;i++){ 
				if(!visited[i]){    //如果没被访问 
					count2++;
					DFS_helper(i, visited);
				}
			}
			if(count2 != 1){
				return 0;
			}
			return 1;     
        }
        
        // question 2
        //修改DSF_helper，限定一下矩阵的访问范围即可 
        void DFS_helper_2(int st, bool* visited){
			visited[st] = true;    //标记为已经访问    
			for(int k=0;k<numVer;k++){
				if(not_0.locateEle(k) == -1) continue;
				if(adjMatrix[st][k]==0) continue;    //不邻接，跳过 
				if(visited[k]) continue;    //访问过，跳过 
				DFS_helper(k,visited);    //对下一个点递归 
			}
		}
        
        
        bool existsEulerianPath(){
            // assume undirected
            //Euler路径条件：图里只能有最多两个度为奇数的顶点、所有非0度的顶点在同一个连通分量里。
            //图里只能有最多两个度为奇数的顶点，简单的，实现如下：
			int count1 = 0;    //奇数点计数 
			for(int i=0;i<numVer;i++){
				int count2 = 0;    //邻接点数量
				for(int j=0;j<numVer;j++){
					if(adjMatrix[i][j] == 1){
						count2++;     
					}
				}
				if(count2 % 2 == 1){
					count1++;
				}
				if(count2 != 0){
					not_0.insertLast(i);    //取出所有的非0度的顶点，看看这个是否连通 
				}
			}
			if(count1 != 0 && count1 != 2){
				return 0; 
			}  
            
            if(not_0.isEmpty()){
            	return 1;
			}
            
            //这里用上面手写的一个DFS 
			bool visited[numVer];
            for(int i=0;i<numVer;i++){
            	visited[i] = false;    //初始化visited数组
			} 
            
            int count3 = 0;  //用于计数，看看是不是不用更换顶点 
            for(int i=0;i<numVer;i++){ 
				if(not_0.locateEle(i) == -1){
					continue;
				}
				if(!visited[i]){    //如果没被访问 
					count3++;
					DFS_helper_2(i, visited);
				}
			}
			if(count3 != 1){
				return 0;
			}
			return 1;
        }
		
		
		bool check(bool* v, int num){    //传入数组的指针和数组长度，判断是否有0 
			for(int i=0;i<num;i++){
				if(v[i] == 0){
					return 0;
				}
			}
			return 1;
		} 
		
		//returns whether it's bipartite or not, and print the two groups if it is.
        // starting graph is connected and undirected.
        bool isBipartite(){ //ques 3
            // TODO
            //如果是二分图就要打印，不是就回传false
			//先假设它是二分图，将第一个点所连接的点归类到第二个集合，再从第二个集合中找它的邻接，归类到第一个集合
			//以此类推，直到所有的都被归类 
			//如果第一个集合中，存在互相相连的，那么就回传false，否则它是二分图，打印分类 
			//在类中的私有变量补充两个向量表用于储存第一个集合和第二个集合 
			
			//写一个辅助函数check用于循环判断。 
			
			/*
				注意是要用顶点值去做判断，而不是索引!!!我debug了好久 
			*/
			
			VecList<T> list1;
			VecList<T> list2; 
			
            bool visit[numVer];
            for(int i=0;i<numVer;i++){
            	visit[i] = 0;
			}
			
			list1.insertLast(verList.getEleAtPos(0));
			visit[0] = 1;
            for(int j=0;j<numVer;j++){
            	if(adjMatrix[0][j] == 1){
					list2.insertLast(verList.getEleAtPos(j));
            		visit[j] = 1;
				}
			}
			
			while(!check(visit, numVer)){
				for(int i=0;i<numVer;i++){
	            	for(int j=0;j<numVer;j++){
	            		if(list2.locateEle(verList.getEleAtPos(i)) == -1){
	            			continue;
						}
						if(adjMatrix[i][j] == 1){
							if(list2.locateEle(verList.getEleAtPos(j)) != -1){
								return 0;
							}
							if(visit[j] == 1){
								continue;
							}
							else{
								list1.insertLast(verList.getEleAtPos(j));
								visit[j] = 1;
							}
						}
					}
				}
				for(int i=0;i<numVer;i++){
	            	for(int j=0;j<numVer;j++){
	            		if(list1.locateEle(verList.getEleAtPos(i)) == -1){
	            			continue;
						}
						if(adjMatrix[i][j] == 1){
							if(list1.locateEle(verList.getEleAtPos(j)) != -1){
								return 0;
							}
							if(visit[j] == 1){
								continue;
							}
							else{
								list2.insertLast(verList.getEleAtPos(j));
								visit[j] = 1;
							}
						}
					}
				}    
			}    
            
            for(int i=0;i<numVer;i++){
            	if(list1.locateEle(verList.getEleAtPos(i)) != -1){
            		cout<<verList.getEleAtPos(i)<<": group "<<1<<endl;
				}
				else{
					cout<<verList.getEleAtPos(i)<<": group "<<2<<endl;
				}
			}
            return 1;    
        }

		
		// question 4
		//辅助函数
		bool loopTest_helper_1(int a, int b){
			for(int j=0;j<numVer;j++){
				if(adjMatrix[b][j] == 1){
					if(adjMatrix[j][a] == 1){
						return 1;
					}
					else{
						if(loopTest_helper_1(a, j)){
							return 1;
						}
					}
				}
			}
			return 0;
		} 
		
		bool loopTest_helper_2(int a, int b, int c){  //c用于保存b的上一级 
			for(int l=0;l<numVer;l++){
				if(adjMatrix[b][l] == 1){
					if(l == c){
						continue;
					}
					if(adjMatrix[l][a] == 1){
						return 1;
					}
					else{
						if(loopTest_helper_2(a, l, b)){
							return 1;
						}
					}
				}
			}
			return 0;
		}
		
        bool loopTest(){
            //思路是递归+回溯
			//对于有向图，就是adjMatrix[i][j] = 1, 则有二者连通
			if(directed == 1){
				bool found1 = 0;
				for(int i=0;i<numVer;i++){
					for(int j=0;j<numVer;j++){
						if(adjMatrix[i][j] == 1){
							if(adjMatrix[j][i] == 1){
								return 1;
							}
							else{
								found1 = loopTest_helper_1(i,j);
								if(found1 == 1){
									return 1;
								}
							}
						}
					}
				}
				return 0;
			}
			//无向图的思路一致，但是注意没有自环，而且要保存上一级顶点，避免走重复路段 
			else{
				bool found2 = 0;
				for(int i=0;i<numVer;i++){
					for(int j=0;j<numVer;j++){
						if(adjMatrix[i][j] == 1){
							for(int k=0;k<numVer;k++){
								if(k != i && adjMatrix[j][k] == 1){
									found2 = loopTest_helper_2(i,k,j);
									if(found2 == 1){
										return 1;
									}
								}
							}
						}
					}
				}
				return 0;
			}
        }
};

/* UPLOAD END */

void test1(){
    int tmp[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(tmp,6);
    for(int i=0;i<6;i++){
        amg1.addEdge(i,((i+1) % 6));
    }
    cout << "Graph 1 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;
    
    amg1.removeEdge(4,5);
    amg1.addEdge(4,0);
    cout << "Graph 3 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;
}

void test4(){
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B');
    amg2.addEdge('A','D');
    amg2.addEdge('A','E');
    amg2.addEdge('B','C');
    amg2.addEdge('C','E');
    amg2.addEdge('D','C');
    amg2.addEdge('D','E');
    
    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;
    
    amg2.addEdge('E','A');
    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;
    
    int ver[9] = {5,6,7,8,9,1,2,3,4};
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
    
    AMGraph<int> amg1(ver,9,edges,10);
    cout << "Are there loops in this graph? " << (amg1.loopTest() ? "Yes" : "No") << endl;
    
}

void test2(){
    int ver[9] = {5,6,7,8,9,1,2,3,4};
    AMGraph<int> amg0(ver,9);
    cout << "Eulerian path? " << (amg0.existsEulerianPath() ? "Yes" : "No") << endl;
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
    AMGraph<int> amg05(ver,9, edges, 5);
    cout << "Eulerian path? " << (amg05.existsEulerianPath() ? "Yes" : "No") << endl;
    
    AMGraph<int> amg1(ver,9,edges,10);
    cout << "Eulerian path? " << (amg1.existsEulerianPath() ? "Yes" : "No") << endl;    
}

int test3(){
    int ver[5] = {1,2,3,4,5};
    AMGraph<int> amg1(ver,5);
    amg1.addEdge(3,4);
    amg1.addEdge(3,5);
    amg1.addEdge(1,3);
    amg1.addEdge(2,4);
    amg1.addEdge(2,5);
    cout << (amg1.isBipartite() ? "Bipartite" : "Not bipartite") << endl;
    
    amg1.addEdge(1,4);
    cout << (amg1.isBipartite() ? "Bipartite" : "Not bipartite") << endl;
    
    return 0;
}

int main(){
    test1();
    test2();
	test3();
	test4();
    return 0;
}
