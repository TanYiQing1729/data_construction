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
    int weight;    //加了全值 
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
				addEdge(eArr[i]->start,eArr[i]->end, eArr[i]->weight);    //第三个参数加权值 
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
        void addEdge(T st, T en, int weight){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;    //将邻接矩阵的值设为权值，否则设为0 
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
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight=" << adjMatrix[i][j] <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight=" << adjMatrix[i][j] <<endl;
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

        AMGraph<T>* PrimMST(){ // all edges have positive weight
            //先拷贝顶点表，构造一个“空图”amg，用来存最小生成树
			T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);    //从原图的顶点表取出顶点值
            }
            AMGraph<T>* amg = new AMGraph<T>(vers,numVer);

			//初始化Prim算法需要的三个数组
            bool isInU[numVer];    // isInU[i]：顶点 i 是否已经在集合 U 中（U 为当前生成树的顶点集合）
            int dist[numVer];     // dist[i]：从“U中的某个点”到“顶点i（不在 U）”的最小边权
			// minimal distance from some point of U to a vertex outside U
            int fromWhichU[numVer];    //fromWhichU[i]：上面这条最小边是从U中的哪个顶点连过来的

			//初始化：从顶点0开始构造生成树
            isInU[0] = true;  //顶点 0 先放入 U
    		dist[0] = 0;      //自己到自己不需要边，这里设为 0
            for(int i=1;i<numVer;i++){
                isInU[i] = false;    // 其他顶点一开始都不在 U 里
                // 如果0到i有边，则初始 dist[i] 就是这条边的权值；
        		// 否则，用-1表示目前 U 中没有边能连到它（不可达）
                dist[i] = (adjMatrix[0][i]!=0 ? adjMatrix[0][i] : -1);
                // 对应的"来自 U 的哪个点"：
                fromWhichU[i] = (adjMatrix[0][i]!=0 ? 0 : -1);
            }

            int countU = 1;    // U 中当前顶点数（目前只有顶点 0）

			//不断扩展 U，直到包含所有顶点
            while(countU < numVer){
                // find minimal weight edge
                //在所有“还没在 U 中的顶点”里，找到 dist 最小的那个
                int tmpW = -1; // minimal weight  当前找到的最小边权
                int tmpV = -1; // corresponding vertex    与这条最小边相连、尚未在U中的顶点下标
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;    //只考虑还不在U的顶点
                    if(tmpW==-1){    //还没选过候选(也就是第一次) 
                        tmpW = dist[i];
                        tmpV = i;
                    }
                    else{
                    	//dist[i] != -1：必须保证 i 能从 U 被连过去
                		//并且找到更小的边权，就更新
                        if(dist[i]!=-1 && dist[i] < tmpW){
                            tmpW = dist[i];
                            tmpV = i;
                        }
                    }
                }

                // now we have minimal weight, and vertex
                // add it into U.
                //把这条最小边连进生成树，把对应的顶点 tmpV 加入 U
                isInU[tmpV] = true; // 顶点 tmpV 现在属于 U
		        // 在 MST 图 amg 中加入这条边：
		        // 这条边是 fromWhichU[tmpV]——tmpV，权值为 tmpW
                amg->addEdge(verList.getEleAtPos(tmpV),verList.getEleAtPos(fromWhichU[tmpV]),tmpW);
                countU++;

				//4.3用新加入U的顶点 tmpV 去“松弛”其他未在 U 中的顶点，
				//看看通过 tmpV 能不能用更小边连接它们
                // update dist, fromWhichU
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    //如果i和tmpV之间有边
                    if(adjMatrix[i][tmpV]!=0){
                    	//若 i 之前完全连不到 U（dist[i] == -1），
                		//现在通过 tmpV 可以连上，就直接用这条边初始化它
                        if(dist[i]==-1){
                            dist[i] = adjMatrix[i][tmpV];
                            fromWhichU[i] = tmpV;
                        }
                        // 否则，如果通过 tmpV 的这条边更短，就更新
                        else if(dist[i] > adjMatrix[i][tmpV]){
                            dist[i] = adjMatrix[i][tmpV];
                            fromWhichU[i] = tmpV;
                        }
                    }
                }
                // 打印当前生成树 amg 的状态，方便调试 / 观察过程
                cout << "At step " << countU-1 << endl;
                amg->printGraph();
            }

            return amg;
        }

        AMGraph<T>* KruskalMST(){
            //先把顶点拷贝出来，构造一个“空图” amg，用来存 MST
			T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* amg = new AMGraph<T>(vers,numVer);

            //用三个数组存图中所有边：起点下标、终点下标、权值
		    int edgeSt[numEdge];   // edgeSt[k]：第 k 条边的起点下标
		    int edgeEn[numEdge];   // edgeEn[k]：第 k 条边的终点下标
		    int weight[numEdge];   // weight[k]：第 k 条边的权值

            int index = 0;    //当前已存了多少条边
            //枚举邻接矩阵上半部分 (i < j)，收集每一条无向边
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j]==0) continue;
                    edgeSt[index] = i;
                    edgeEn[index] = j;
                    weight[index] = adjMatrix[i][j];
                    index++;
                }
            }

			// 3. 按边的权值从小到大对所有边排序（这里用的是简单的冒泡排序）
            for(int i=0;i<numEdge;i++){
                for(int j=0;j+1<numEdge;j++){
                    if(weight[j] > weight[j+1]){
                        int tmp = weight[j];
                        weight[j] = weight[j+1];
                        weight[j+1] = tmp;
                        tmp = edgeSt[j];
                        edgeSt[j] = edgeSt[j+1];
                        edgeSt[j+1] = tmp;
                        tmp = edgeEn[j];
                        edgeEn[j] = edgeEn[j+1];
                        edgeEn[j+1] = tmp;
                    }
                }
            }

            // edges arranged in increasing order.
			// 至此，所有边已经按权值非递减顺序排好：
    		// weight[0] <= weight[1] <= ... <= weight[numEdge-1]
			
			//使用“并查集”思想（这里是用数组模拟的连通分量标号）
            // add edges from smallest to largest, ensuring not forming loops
            int componentNum[numVer];    // componentNum[v]：顶点 v 当前属于哪个连通分量（用一个编号表示）
            for(int i=0;i<numVer;i++){
                componentNum[i] = i;    // 初始时，每个顶点自成一个连通分量
            }
            int compNum = numVer; //当前连通分量的个数（MST 完成时应该变成 1）
    		index = 0;            //从最小权值的边开始一条条考察

			//从最小的边开始，依次尝试加入 MST，直到只剩一个连通分量
            while(compNum > 1){
                // look at edge, at index.
                // examine if edgeSt[index] and edgeEn[index] is in the same component
                // 当前考虑第 index 条边：edgeSt[index] -- edgeEn[index]，权值为 weight[index]
                // 如果这条边的两个端点已经在同一个连通分量里，说明加上会形成环，不能选
                if(componentNum[edgeSt[index]] == componentNum[edgeEn[index]]){
                    //跳过这条边，看下一条
					index++;
                    continue;
                }

                // add Edge
                // 否则，这条边可以安全加入 MST（不会形成环）
                amg->addEdge(verList.getEleAtPos(edgeSt[index]), verList.getEleAtPos(edgeEn[index]), weight[index]);

                // put things into the same component
                // 现在需要把这两个端点所在的连通分量“合并”起来
                int numToSetTo = componentNum[edgeSt[index]];   // 合并后统一采用的分量编号
        		int numNeedingChange = componentNum[edgeEn[index]]; // 要被合并掉的分量编号
                //遍历所有顶点，把属于 numNeedingChange 的都改成 numToSetTo
				for(int i=0;i<numVer;i++){
                    if(componentNum[i]==numNeedingChange)
                        componentNum[i] = numToSetTo;
                }
                // 连通分量数量减少 1
                compNum--;
                index++;

                cout << "At step " << index << ":" << endl;
                amg->printGraph();
            }
            return amg;
        }

        void printDijkstra(T st){ // positive weights  权值为正数 
            int dist[numVer];    //初始化距离 
            int preNode[numVer];    //初始化前一个点的下标，利用了子问题相似的特点 
            bool isInS[numVer];    //在不在S集合中 
            for(int i=0;i<numVer;i++){    //初始化上述三个 
                dist[i] = -1;
                preNode[i] = -1;
                isInS[i] = false;
            }

            int sIndex = verList.locateEle(st);    //找st的下标 
            dist[sIndex] = 0;    //起点到起点的距离为0 
            isInS[sIndex] = true;    //肯定在S里头
			//preNode直接标为-1即可（已经在for循环中标过），因为没有前一个点的下标 

            int countS = 1;    //当前S集合中的顶点数量（已确定最短路的点数）
            //初始化：用起点 sIndex 的邻接边，更新其他顶点的初始 dist 和 preNode
			for(int i=0;i<numVer;i++){
                if(isInS[i]) continue;    //跳过起点
                
				// 若 sIndex 到 i 有边（邻接矩阵中权值非 0），则用该边初始化 dist 和 preNode 
                dist[i] = (adjMatrix[sIndex][i]!=0 ? adjMatrix[sIndex][i] : -1);
                
                // 在当前已知最短路径中（邻接矩阵权值非0），i 的前驱是起点
                preNode[i] = (adjMatrix[sIndex][i]!=0 ? sIndex : -1);
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
                    if(adjMatrix[corrIndex][i]==0) continue;    //无边，跳过 
                    //若i目前不可达，则直接用“到 corrIndex 的最短路 + corrIndex->i 的边”来更新
                    //dist[corrIndex]这是路径，即不是直接从st到corrIndex，而是从st到corrIndex的最小路径 
					if(dist[i]==-1){    
                        dist[i] = dist[corrIndex] + adjMatrix[corrIndex][i];
                        preNode[i] = corrIndex;
                    }
                    // 若 i 已有距离，但通过 corrIndex 可以更短，则进行松弛，这是同理上面的 
                    else if(dist[corrIndex] + adjMatrix[corrIndex][i] < dist[i]){
                        dist[i] = dist[corrIndex] + adjMatrix[corrIndex][i];
                        preNode[i] = corrIndex;
                    }
                }
            }

            // print the results
            //输出结果：打印从起点 st 到所有顶点的最短路径和总花费
            cout << left << setw(18) << "Vertice name" << "Path" << endl;
            for(int i=0;i<numVer;i++){
            	// 输出顶点名（verList.getEleAtPos(i) 获取下标 i 对应的顶点值）
                cout << left << setw(18) << verList.getEleAtPos(i);
                if(dist[i]==-1){ cout << "Unreachable" << endl; continue;}    // 若 dist[i] 仍为 -1，说明从起点 st 无法到达该点

				//利用 preNode 数组反向回溯路径，然后用栈倒过来输出
                LinkStack<int> s;
                int j =i;
                s.push(j);    //栈中存顶点下标，先把终点 i 入栈
                //一直沿着 preNode 往前走，直到 j == -1（即到达起点之前的“空前驱”）
				while(j!=-1){
                    j = preNode[j];    //找到 j 的前驱，注意，这一步是在更新j的，所以可以循环的起来 
                    s.push(j);    //把前驱也入栈（最后一次会 push(-1)）
                }
                s.pop();    // 弹出栈顶的 -1（因为 -1 不是一个真实的顶点）

				//从栈顶开始弹出，就可以按“起点 -> ... -> 终点”的顺序输出路径
                bool first = true;
                while(!s.isEmpty()){
                    if(first){    //第一个顶点直接输出 
                        cout << verList.getEleAtPos(s.pop());
                        first = false;
                    }
                    else{    //剩下加箭头 
                        cout << " -> " << verList.getEleAtPos(s.pop());
                    }
                }
                // 输出总花费（最短距离）
                cout << ", cost = " << dist[i] << endl;
            }

        }

		//用一个二维矩阵 dists[i][j] 来保存当前“认为的”从 i 到 j 的最短路径长度；
		//不断枚举一个“允许作为中转的点” k，在考虑 i -> j 的路径时，判断：
		//是否通过 k（即 i -> k -> j）会比当前的 i -> j 更短？

		//用 Floyd 算法计算任意两点之间的最短距离，返回一个二维数组 dists，表示两点间的最短路径 
        int** distances(){
            // compute distance between any 2 nodes
            // Floyd's version
            // positive weights

            // 创建距离矩阵 dists，大小为 numVer × numVer
		    int** dists = new int*[numVer];
		    for(int i = 0; i < numVer; i++){
		        dists[i] = new int[numVer];
		        for(int j = 0; j < numVer; j++){
		            // 如果 i 到 j 有直接边，则初始距离为这条边的权值
		            if(adjMatrix[i][j] != 0){
		                dists[i][j] = adjMatrix[i][j];
		            }
		            // 否则认为目前不可达，用 -1 表示
		            else{
		                dists[i][j] = -1;
		            }
		            // 自己到自己，距离为 0
		            if(i == j) dists[i][j] = 0;
		        }
		    }
		
		    // 核心 Floyd 三重循环
		    // k 表示当前允许作为“中转点”的顶点
		    for(int k = 0; k < numVer; k++){
		        // i 为起点
		        for(int i = 0; i < numVer; i++){
		            // j 为终点
		            for(int j = 0; j < numVer; j++){
		                // 如果 i→k 或 k→j 目前不可达，则无法通过 k 组成一条 i→k→j 的路径
		                if(dists[i][k] == -1 || dists[k][j] == -1) continue;
		
		                // 情况 1：i→j 之前认为不可达
		                if(dists[i][j] == -1){
		                    // 现在发现通过 k 可以从 i 走到 j，于是记录这条路径的距离
		                    dists[i][j] = dists[i][k] + dists[k][j];
		                }
		                // 情况 2：i→j 已经有一条路径，但通过 k 可以得到更短的路径
		                else if(dists[i][k] + dists[k][j] < dists[i][j]){
		                    // 做“松弛”：更新成更短的距离
		                    dists[i][j] = dists[i][k] + dists[k][j];
		                }
		            }
		        }
		    }
		    // 返回最终的全源最短路径距离矩阵
		    return dists;
        }

		//同样用 Floyd 算法，同时计算任意两点之间的最短距离和一条对应的路径信息，但：
		//函数最终返回的是一个二维数组 preNodes，
		//preNodes[i][j]：表示在某条 i -> j 的最短路径中，一个中间点（k）。
		//初始值都是 bad，表示“当前没有中间点”。 
        T** preNodeDist(T bad){
            // compute distance between any 2 nodes
            // Floyd's version
            // positive weights

            // preNodes[i][j]：记录 i->j 的中间顶点（类型为 T）
		    T** preNodes = new T*[numVer];
		    // dists[i][j]：记录 i->j 的当前最短距离
		    int** dists = new int*[numVer];
		
		    for(int i = 0; i < numVer; i++){
		        dists[i] = new int[numVer];
		        preNodes[i] = new T[numVer];
		        for(int j = 0; j < numVer; j++){
		            // 初始化距离：有边就用边权，没有边就用 -1 代表不可达
		            if(adjMatrix[i][j] != 0){
		                dists[i][j] = adjMatrix[i][j];
		            }
		            else{
		                dists[i][j] = -1;
		            }
		            // 自己到自己距离为 0
		            if(i == j) dists[i][j] = 0;
		
		            // 初始化中间点表：一开始都没有中间点，用 bad 作为占位
		            preNodes[i][j] = bad;
		        }
		    }
		
		    // Floyd 三重循环
		    for(int k = 0; k < numVer; k++){
		        for(int i = 0; i < numVer; i++){
		            for(int j = 0; j < numVer; j++){
		                // 如果 i→k 或 k→j 不可达，则无法通过 k 连接 i 和 j
		                if(dists[i][k] == -1 || dists[k][j] == -1) continue;
		
		                // 情况 1：i→j 之前不可达
		                if(dists[i][j] == -1){
		                    // 通过 k 发现了一条新路径 i→k→j
		                    dists[i][j] = dists[i][k] + dists[k][j];
		                    // 记录：这条最短路径是“经由顶点 k”中转的
		                    preNodes[i][j] = verList.getEleAtPos(k);
		                }
		                // 情况 2：i→j 原本有路径，但通过 k 可以更短
		                else if(dists[i][k] + dists[k][j] < dists[i][j]){
		                    // 更新成更短的长度
		                    dists[i][j] = dists[i][k] + dists[k][j];
		                    // 同时更新中间点：现在认为“经由 k 是最优的”
		                    preNodes[i][j] = verList.getEleAtPos(k);
		                }
		            }
		        }
		    }
		    // 返回中间结点矩阵（距离矩阵 dists 如果要用，最好在外面也一并返回或保存起来）
		    return preNodes;
        }
};

// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
template <class T>
void printMatrix(T** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// multiply 2 square matrices
int** mulMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = 0;
            for(int k=0;k<n;k++){
                tmp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return tmp;
}

int** addMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
    return tmp;
}

void test(){
    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);
    amg1.addEdge(0,1,34);
    amg1.addEdge(0,5,19);
    amg1.addEdge(0,2,46);
    amg1.addEdge(5,2,25);
    amg1.addEdge(5,3,25);
    amg1.addEdge(5,4,26);
    amg1.addEdge(2,3,17);
    amg1.addEdge(3,4,38);
    amg1.addEdge(1,4,12);

    cout << endl << "Dijkstra starting at vertex 0: " << endl;
    amg1.printDijkstra(0);

    cout << endl << "All distances:" << endl;
    printMatrix(amg1.distances(),6);

    cout << endl << "All prev node:" << endl;
    printMatrix(amg1.preNodeDist(-1),6);

    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    cout << endl << "Dijkstra starting at vertex A: " << endl;
    amg2.printDijkstra('A');

    cout << endl << "All distances:" << endl;
    printMatrix(amg2.distances(),5);

    cout << endl << "All prev node:" << endl;
    printMatrix(amg2.preNodeDist(' '),5);
}

int main(){
    test();
    return 0;
}
