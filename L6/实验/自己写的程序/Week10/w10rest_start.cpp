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

/* UPLOAD START */

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
        
        AMGraph<T>* PrimMST(){
            T* tArr = new T[numVer];
            for(int i=0;i<numVer;i++){
                tArr[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* tmp = new AMGraph<T>(tArr,numVer);
            
            // that constructed a new graph. Now we need to put the edges in.
            bool* inS = new bool[numVer]; // if the vertex is in set S
            int* shortVer = new int[numVer]; // shortest vertice to point
            int count = 0; // how many vertices are in S.
            int lastIndex; // to know which edges we need to check for updates
            for(int i=0;i<numVer;i++){
                inS[i] = false;
                shortVer[i] = -1;
            }
            
            // we start Prim's algorithm now, with vertex 0 being the first one to be put into S.
            inS[0] = true;
            count = 1;
            lastIndex = 0;
            while(count < numVer){ // as long as not all vertices are in  S yet...
            
                int sIndex = -1;
                // update the shortVer array and find shortest
                for(int i=0;i<numVer;i++){
                    if(!inS[i] && adjMatrix[lastIndex][i]>0){
                        if(shortVer[i]==-1){
                            shortVer[i] = lastIndex;
                        }
                        if(adjMatrix[lastIndex][i] < adjMatrix[i][shortVer[i]])
                            shortVer[i] = lastIndex;
                    }
                    if(!inS[i] && shortVer[i]!=-1){ // valid candidate to put into S
                        if(sIndex == -1){
                            sIndex = i;
                        }
                        else if(adjMatrix[i][shortVer[i]] < adjMatrix[sIndex][shortVer[sIndex]]){
                            sIndex = i;
                        }
                            
                    }
                }
                
                inS[sIndex] = true;
                // cout << "Taking edge: (" << verList.Get(shortVer[sIndex]) << "," << verList.Get(sIndex) << "), weight = ";
                // cout << adjMatrix[shortVer[sIndex]][sIndex] << endl;
                tmp->addEdge(verList.getEleAtPos(shortVer[sIndex]),verList.getEleAtPos(sIndex),adjMatrix[shortVer[sIndex]][sIndex]);
                count++;
                lastIndex = sIndex;
            }
            return tmp;
        }
        
        // Question 2:
        void distFromAllTo(T end){
            // use the same format as our demonstration of Dijkstra
			//Dijkstra算法是从st点出发找最小路径，这里只是换成了从end结尾，所以调整一下方向就可以了 
			int dist[numVer];    //初始化距离 
            int preNode[numVer];    //初始化前一个点的下标，利用了子问题相似的特点 
            bool isInS[numVer];    //在不在S集合中 
            for(int i=0;i<numVer;i++){     
                dist[i] = -1;
                preNode[i] = -1;
                isInS[i] = false;
            }

            int sIndex = verList.locateEle(end);    //找end的下标 
            dist[sIndex] = 0;     
            isInS[sIndex] = true;    
			//preNode直接标为-1即可（已经在for循环中标过），因为没有前一个点的下标 

            int countS = 1;    //当前S集合中的顶点数量（已确定最短路的点数）
            //初始化：用终点 sIndex 的邻接边，更新其他顶点的初始 dist 和 preNode
			for(int i=0;i<numVer;i++){
                if(isInS[i]) continue;    //跳过终点 
                
				// 若 sIndex 到 i 有边（邻接矩阵中权值非 0），则用该边初始化 dist 和 preNode 
                dist[i] = (adjMatrix[i][sIndex]!=0 ? adjMatrix[i][sIndex] : -1);
                
                // 在当前已知最短路径中（邻接矩阵权值非0），i 的前驱是起点
                preNode[i] = (adjMatrix[i][sIndex]!=0 ? sIndex : -1);
            }

			//主循环：每次从“未加入 S 的点”中，选一个 dist 最小的点加进 S，然后用它去松弛其他点
            while(countS < numVer){
                int smallestDist = -1; // 当前找到的最小 dist 值，初始化为-1 
        		int corrIndex = -1;    // 与 smallestDist 对应的顶点下标

                // find smallest distance of the remaining points
                //在未加入 S 的点中寻找 dist 最小的顶点 corrIndex
                for(int i=0;i<numVer;i++){
                    if(isInS[i]) continue;   // 已在 S 中的不考虑
            		if(dist[i] == -1) continue; // 当前仍不可达的不考虑
                    if(corrIndex==-1){    //如果还没选过候选点
                        smallestDist = dist[i];
                        corrIndex = i;
                    }
                    else if(dist[i] < smallestDist){    //如果找到更小的 
                        smallestDist = dist[i];
                        corrIndex = i;
                    }
                }

                if(corrIndex==-1){    // 如果 corrIndex 仍是 -1，说明剩下的顶点都不可达，算法可以结束
                    countS = numVer;
                    continue;
                }

                isInS[corrIndex] = true;    // 将找到的这个最小 dist 的点加入 S 集合
                countS++;
                //上述干的事情都是“找一个dist最小的点，加入S中” 
                

                // update the distances
                //使用corrIndex（就是我们刚刚找到的点）作为中间点，尝试更新（松弛）其他未在 S 中的点的 dist
                for(int i=0;i<numVer;i++){
                    if(isInS[i]) continue;    // S 中的点已经确定最短路，无需更新
                    if(adjMatrix[i][corrIndex]==0) continue;    //无边，跳过 
					if(dist[i]==-1){    
                        dist[i] = dist[corrIndex] + adjMatrix[i][corrIndex];
                        preNode[i] = corrIndex;
                    }
                    // 若 i 已有距离，但通过 corrIndex 可以更短，则进行松弛，这是同理上面的 
                    else if(dist[corrIndex] + adjMatrix[i][corrIndex] < dist[i]){
                        dist[i] = dist[corrIndex] + adjMatrix[i][corrIndex];
                        preNode[i] = corrIndex;
                    }
                }
            }

            // print the results
            cout << left << setw(18) << "Vertice name" << "Path" << endl;
            for(int i=0;i<numVer;i++){
            	// 输出顶点名（verList.getEleAtPos(i) 获取下标 i 对应的顶点值）
                cout << left << setw(18) << verList.getEleAtPos(i);
                if(dist[i]==-1){ cout << "Unreachable" << endl; continue;}    // 若 dist[i] 仍为 -1，说明从起点 st 无法到达该点

				//用队列输出
				//调不出来，搞两个栈算了 
				//又跳出来了哈哈哈哈，两个方法都能用 
				LinkQueue<int> q;
				int j = i;
				q.enQueue(j);
				while(j != -1){
					j = preNode[j];
					q.enQueue(j);
				}
				
				
				bool first = true;
                while(!q.isEmpty()){
                    if(first){    //第一个顶点直接输出 
                        cout << verList.getEleAtPos(q.deQueue());
                        first = false;
                    }
					else{    //剩下加箭头 
						int temp = q.deQueue();
						if(temp == -1){
							continue;
						}
						cout << " -> " << verList.getEleAtPos(temp);
                    }
                }
                // 输出总花费（最短距离）
                cout << ", cost = " << dist[i] << endl;

/*
				//用两个栈翻转输出顺序
				 
				//利用 preNode 数组反向回溯路径，然后用栈倒过来输出 
                LinkStack<int> s1;
                int j =i;
                s1.push(j);    //栈中存顶点下标，先把终点 i 入栈
                //一直沿着 preNode 往前走，直到 j == -1（即到达起点之前的“空前驱”）
				while(j!=-1){
                    j = preNode[j];    //找到 j 的前驱，注意，这一步是在更新j的，所以可以循环的起来 
                    s1.push(j);    //把前驱也入栈（最后一次会 push(-1)）
                }
                s1.pop();    // 弹出栈顶的 -1（因为 -1 不是一个真实的顶点）

				LinkStack<int> s2;
				while(!s1.isEmpty()){
					int temp = s1.pop();
					s2.push(temp);
				}

				//从栈顶开始弹出，就可以按“起点 -> ... -> 终点”的顺序输出路径
                bool first = true;
                while(!s2.isEmpty()){
                    if(first){    //第一个顶点直接输出 
                        cout << verList.getEleAtPos(s2.pop());
                        first = false;
                    }
                    else{    //剩下加箭头 
                        cout << " -> " << verList.getEleAtPos(s2.pop());
                    }
                }
                // 输出总花费（最短距离）
                cout << ", cost = " << dist[i] << endl;
*/
            } 
        }
        
        // Question 3
        int numPathsDAG(){
            // our graph has one source and one sink
            
            //先找出源点和汇点再说 
            int source = -1;
            int sink = -1;
            int ins[numVer];    //每个点的入度 
            
            for(int i=0;i<numVer;i++){
            	int sum1 = 0;
            	int sum2 = 0;
            	for(int j=0;j<numVer;j++){
            		if(adjMatrix[i][j] == 1){
            			sum1++;
					}
					if(adjMatrix[j][i] == 1){
            			sum2++;
					}
				}
				ins[i] = sum2; 
				if(sum1 == 0){
					sink = i;    //汇点 
				}
				if(sum2 == 0){
					source = i;    //源点 
				}
			}
			 
			//这其实是一个动态规划问题
			//step1：dp[i]表示从source到某一点i的路径数量
			//step2：dp[sink] = sigma dp[sink入边总和] 
			//step3：dp[source] = 1
			//step4：从后往前遍历，带记忆的递归
			//但是我觉得这要把dp数组写在类里面，有点麻烦，就尝试从前往后遍历 
			
			int dp[numVer] = {0};
			dp[source] = 1; 
			 
			//写着会发现可以给它加一个队列——其实就有点像BFS了
			//上面的做法是不行的，比如a->b->c和d->c
			//不过原理相似，只不过要改变入队的规则 
			
			//先计算一下每个点的入度，这里我补充在前面了 
			
			//然后再是按照入度来入队 
			LinkQueue<int> q;
        	q.enQueue(source);
        	while(!q.isEmpty()){
        		int temp = q.deQueue();
				for(int i=0;i<numVer;i++){
					if(adjMatrix[temp][i] == 1){
						dp[i] += dp[temp];
						ins[i]--;
						if(ins[i] == 0){
							q.enQueue(i);
						} 
					}
				}
			}
			
			return dp[sink];
        }
        
        
        // question 4 
		//辅助函数 
        void DFS_helper(int st, bool* visited){
			visited[st] = true;    //标记为已经访问    
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;    //不邻接，跳过 
				if(visited[k]) continue;    //访问过，跳过 
				DFS_helper(k,visited);    //对下一个点递归 
			}
		} 
		       
        AMGraph<T>* criticalEdge(){
            //先新建一个图用于回传
            T* verlist = new T[numVer];
			for(int i=0;i<numVer;i++){
			    verlist[i] = verList.getEleAtPos(i);
			}
			AMGraph<T>* ans = new AMGraph<T>(verlist, numVer, 0); 
			
			//想法很简单，遍历每一条边，减掉之后不联通就是切割边，再把边添加到ans中
			for(int i=0;i<numVer;i++){
				for(int j=i+1;j<numVer;j++){
					if(adjMatrix[i][j] != 0){
						int temp = adjMatrix[i][j];
						adjMatrix[i][j] = 0;
						adjMatrix[j][i] = 0;
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
							//不联通 
							ans->addEdge(i, j, temp);
						}
						
						adjMatrix[i][j] = temp;
						adjMatrix[j][i] = temp;    //回归原样 
					}
				}
			} 
			
			return ans;
            
        }
};

/* UPLOAD END */

void test1(){
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    cout << "Shortest paths to vertex E: " << endl;
    amg2.distFromAllTo('E');
    
    cout << endl;
}

void test2(){
    int ver[8] = {0,1,2,3,4,5,6,7};
    AMGraph<int> amg(ver,8,true);
    amg.addEdge(0,3);
    amg.addEdge(0,4);
    amg.addEdge(3,1);
    amg.addEdge(4,1);
    amg.addEdge(0,1);
    amg.addEdge(1,5);
    amg.addEdge(1,6);
    amg.addEdge(1,7);
    amg.addEdge(5,2);
    amg.addEdge(6,2);
    amg.addEdge(7,2);
    amg.addEdge(1,2);
    cout << "Case 1: Number of ways to get from source to sink is " << amg.numPathsDAG() << endl;
    
    int ver2[5] = {1,2,3,4,5};
    AMGraph<int> amg2(ver2,5,true);
    amg2.addEdge(1,2);
    amg2.addEdge(1,3);
    amg2.addEdge(1,4);
    amg2.addEdge(1,5);
    amg2.addEdge(2,4);
    amg2.addEdge(3,4);
    amg2.addEdge(3,5);
    amg2.addEdge(4,5);
    cout << "Case 2: Number of ways to get from source to sink is " << amg2.numPathsDAG() << endl;
}

void test3(){
    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);
    amg1.addEdge(0,1,1);
    amg1.addEdge(1,2,2);
    amg1.addEdge(2,3,3);
    amg1.addEdge(3,4,4);
    amg1.addEdge(4,5,5);
    
    AMGraph<int>* tmp = amg1.criticalEdge();
    tmp->printGraph();
    
    AMGraph<int> amg2(ver, 6);
    amg2.addEdge(0,1);
    amg2.addEdge(1,2);
    amg2.addEdge(0,2);
    amg2.addEdge(2,3);
    amg2.addEdge(3,4);
    amg2.addEdge(4,5);
    tmp = amg2.criticalEdge();
    tmp->printGraph();
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}
