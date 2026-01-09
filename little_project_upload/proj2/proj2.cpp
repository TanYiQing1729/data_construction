#include <iostream>
#include <vector>
#include <string>
#include <queue> //  queue 用于优先队列
#include <iomanip>

using namespace std;

//使用的算法为YEN's算法，其中的Dijkstra算法部分将使用堆优化至复杂度为O(n^2·logn)
//为此使用邻接表(而不是邻接矩阵)，<queue> 

// 边结构体
struct Edge {
    int to;    //终点 
    int weight;    //权重 
};

// 路径结构体，包含总权重和节点序列
struct Path {
    int total_dist;    //总距离    
    vector<int> vers;    //经过的结点，用vector存储 

	//重载一下 > < == 运算符
	//这里采用引用传入path提高效率，因为只是比较所以输入和输出都是用const 
    bool operator>(const Path& another) const {
        return total_dist > another.total_dist;
    }
    bool operator==(const Path& another) const {
        return total_dist == another.total_dist;
    }
    bool operator<(const Path& another) const {
        return total_dist < another.total_dist;
    }
};

// 全局变量
int num_ver;    //顶点数 
int num_edge;    //边数 
string ver_list[200];     //顶点列表 
vector<Edge> adj[200];     //邻接表: adj[u] = {{v, weight}, ... }
bool global_banned[200];     //存禁止的结点 
int maxTransLimit = -1;    //中继限制，初始化为-1

//反转vector的辅助函数 
void reverse_vec(vector<int>& v) {
    int left = 0; 
    int right = v.size() - 1;
    while (left < right) {
        int temp = v[left];
        v[left] = v[right];
        v[right] = temp;
        left++;
        right--;
    }
} 

//查找结点辅助函数：根据名字查找索引 
int get_pos(string name) {
    for(int i=0;i<num_ver;i++){
        if(ver_list[i] == name) {
            return i;
        }
    }
    return -1;
}

//Dijkstra状态结构体 
struct State {
    int pos;    //当前顶点的索引 
    int dist;
    int num_of_edges;    //经过的边数

	//同上重载运算符 
    bool operator>(const State& another) const {
        return dist > another.dist;
    }
    bool operator<(const State& another) const {
        return dist < another.dist;
    }
    bool operator==(const State& another) const {
        return dist == another.dist;
    }
};


/*
	使用Dijkstra进行最短路搜索
	st, en: 起点终点
	temp_blocked_vers: 临时禁止的点（Yen's算法用）
	temp_blocked_edges: 临时禁止的边（Yen's算法用，二维数组）
    edge_limit_override: 本次搜索允许的最大“边”数量（包含起终点之间的所有边）
 */
Path shortest_path(int st, int en, 
                  bool temp_blocked_vers[200], 
                  bool temp_blocked_edges[200][200],
                  int edge_limit_override = -1){
    
    // 计算本次搜索允许的最大边数
    int global_limit = (maxTransLimit == -1) ? num_ver : maxTransLimit + 1; // maxTrans 是“中继数”，边数=中继+1
    int limit = (edge_limit_override == -1) ? global_limit : edge_limit_override;
    if (limit < 1) {
        Path none;
        none.total_dist = -1;
        return none;
    }
    
    //距离数组，dist[i][j]表示到达结点i经过j条边 
    vector<vector<int>> dist(num_ver, vector<int>(limit + 1));
    for(int i=0;i<num_ver;i++){
    	for(int j=0;j<limit+1;j++){
    		dist[i][j] = 100000000;    //初始化为很大的值代表不可达 
		}
	} 
	
	//前驱结构体 
	struct Prev {
	    int ver = -1;   //前驱节点索引，初始化为-1 
	    int num_of_edges = -1;   //到达前驱节点时的经过的边数，初始化为-1 
	};
	//前驱数组，用于回溯，parent[i][j]代表到达i时前j条路径的结点数和边数 
    vector<vector<Prev>> parent(num_ver, vector<Prev>(limit + 1));

	//使用<queue>里面的优先队列，
	//这是元素类型为State，比较器为greater的优先队列，会把最小值放在最顶(就是最小堆) 
    priority_queue<State, vector<State>, greater<State>> pq;

	//初始化起点，把起点状态压入优先队列 
    dist[st][0] = 0;
    pq.push({st, 0, 0});
	
	//初始化最终路径长度和边数 
    int final_dist = 100000000;
    int final_num_of_edges = -1;

    while (!pq.empty()) {
        //优先队列出队，这是当前估计距离最小的状态 
		State cur = pq.top();
        pq.pop();

        int p = cur.pos;
        int d = cur.dist;
        int n = cur.num_of_edges;

		//dist[p][n] 保存的是到达(p,n)的当前已知最短距离，如果弹出状态的d大于dist[p][n]，
    	//则说明我们之前已经找到更短的一条（同样num_of_egdes数），当前状态为旧状态，应跳过。
        if(d > dist[p][n]){
        	continue;
		}
		
		//如果当前节点就是目标节点，这是第一次遇到终点 
    	//意味着“存在一条在num_of_egdes限制内的最短路径”。
    	//记录结果并退出循环，回溯路径。
        if(p == en){
            final_dist = d;
            final_num_of_edges = n;
            break; 
        }
        
        //如果当前已用num_of_egdes已经达到允许的最大跳数limit，则不再扩展
    	//避免越界访问并满足 maxTrans 的限制
        if(n >= limit){
        	continue;
		}

		//遍历所在结点p的所有邻边（p -> v，权重 w）
        for (int i = 0; i < adj[p].size(); i++) {
            int v = adj[p][i].to;
            int w = adj[p][i].weight;

            //检查顶点全局 Ban (global_banned)和临时 Ban (temp_blocked_vers)
            //终点不能被当做中继点Ban掉
            bool is_banned = global_banned[v] || temp_blocked_vers[v];
            if(is_banned && v != en){
            	continue;	
			}

            //临时边 Ban
            if(temp_blocked_edges[p][v]){
            	continue;
			}

			//Dijkstra中的松弛操作 
			//当前已知到达(p, n)的最短距离是dist[p][n]，经过边p->v后到达的新距离为 dist[p][n] + w。
        	//如果该新距离比当前记录的 dist[v][n+1]更小，则更新并记录parent以便回溯路径。
            if (dist[p][n] + w < dist[v][n+1]) {
                dist[v][n+1] = dist[p][n] + w;
                parent[v][n+1].ver = p;
				parent[v][n+1].num_of_edges = n;
                pq.push({v, dist[v][n+1], n+1});    //进入优先队列 
            }
        }
    }

    Path result;
    //没有可达 
    if (final_dist == 100000000) {
        result.total_dist = -1;
        return result;
    }
	
	//否则记录当前结点 
    result.total_dist = final_dist;
    int cur_place = en;
    int cur_num_of_edges = final_num_of_edges;
    
	//开始回溯 
    while (cur_place != -1) {
        result.vers.push_back(cur_place);
        Prev p = parent[cur_place][cur_num_of_edges];
        cur_place = p.ver;
        cur_num_of_edges = p.num_of_edges;
    }
    //翻转vec 
    reverse_vec(result.vers);
    return result;
}


//辅助函数：判断两个 path 是否相同（用于去重），采用引用传入 
bool is_same_path(const Path& p1, const Path& p2) {
    //先比长短 
	if(p1.vers.size() != p2.vers.size()){
    	return 0;
	}
    for (int i=0;i<p1.vers.size();i++) {
        if (p1.vers[i] != p2.vers[i]){
        	return 0;
		}
    }
    return 1;
}

void kShortestPaths(string s1, string s2, int K) {
    int st = get_pos(s1);
    int en = get_pos(s2);
    //增强健壮性 
    if (st == -1 || en == -1){
    	return;
	}

    // 全局允许的最大边数（maxTrans是中继数，边=中继+1）
    int global_limit = (maxTransLimit == -1) ? num_ver : maxTransLimit + 1;

    vector<Path> result; // 结果集
    
    // 临时禁止数组
    bool blocked_nodes[200];
    bool blocked_edges[200][200];

    // 初始化数组为 false
    for(int i=0; i<num_ver; i++){
    	blocked_nodes[i] = 0;
	}
    for(int i=0; i<num_ver; i++){
    	for(int j=0; j<num_ver; j++){
    		blocked_edges[i][j] = 0;
		}
	} 

    // 1.第一条路径：使用Dijkstra算法寻找（受全局边数限制）
    Path p0 = shortest_path(st, en, blocked_nodes, blocked_edges, global_limit);
    //如果找到 
	if(p0.total_dist != -1) {
        result.push_back(p0);
    }

    //候选池
    priority_queue<Path, vector<Path>, greater<Path>> candidate;

    // 2. Yen's 主循环
    for(int k = 1;k<K;k++) {
        //如果目前找到的路径数不足k，则提前退出
		if(result.size() < k){
        	break;    
		}
		//取出上一个找到的最短路径
        Path prev_path = result[k-1];

        //尝试偏离
        for(int i = 0;i<prev_path.vers.size() - 1;i++){
            //偏离结点 
			int spur_node = prev_path.vers[i];
            
            //提取根路径
            vector<int> root_path;
            for(int j = 0;j<=i;j++){
            	root_path.push_back(prev_path.vers[j]);
			}

            //检查 MaxTrans (root部分已经消耗的边数)
            int current_num_of_edges = root_path.size() - 1;
            int remaining_limit = global_limit - current_num_of_edges;
            if (remaining_limit <= 0){
            	continue;
			}

            //重置临时禁止表
            for(int r=0;r<num_ver;r++){
            	blocked_nodes[r] = 0;
			}
            for(int r=0;r<num_ver;r++){
            	for(int c=0; c<num_ver; c++){
            		blocked_edges[r][c] = 0;
				}
			} 
                

            //(a)禁止根路径上的点 (除了spur_node)
            for(int j = 0;j<i;j++){
                blocked_nodes[root_path[j]] = 1;
            }

            //(b)禁止A中已有路径的下一跳
            for(int idx = 0;idx < result.size();idx++){
                const Path& path_result = result[idx];
                // 检查 pathA 是否以 root_path 开头
                if(path_result.vers.size() > i + 1){
                    bool match = 1;
                    for(int j = 0; j <= i; j++){
                        if(path_result.vers[j] != root_path[j]){
                            match = 0; 
                            break;
                        }
                    }
                    if(match){
                        int u = path_result.vers[i];
                        int v = path_result.vers[i+1];
                        blocked_edges[u][v] = 1;
                        blocked_edges[v][u] = 1; // 无向图
                    }
                }
            }

            //计算偏离路径（使用剩余可用边数作为限制）
            Path spur_path = shortest_path(spur_node, en, blocked_nodes, blocked_edges, remaining_limit);

            if(spur_path.total_dist != -1) {
                Path total_path;
                //拼接 Root
                total_path.vers = root_path;
                total_path.vers.pop_back(); // 避免重复 spur_node
                //拼接 Spur
                for(int j = 0; j < spur_path.vers.size(); j++) {
                    total_path.vers.push_back(spur_path.vers[j]);
                }
                
                //重新计算总距离
                int dist = 0;
                bool valid = 1;
                for(int j = 0; j < total_path.vers.size() - 1; j++) {
                    int u = total_path.vers[j];
                    int v = total_path.vers[j+1];
                    int w = 100000000;
                    //找边重
                    for(int ei = 0; ei < adj[u].size(); ei++) {
                        if(adj[u][ei].to == v) {
                            w = adj[u][ei].weight;
                            break;
                        }
                    }
                    if(w == 100000000){
						valid = 0; 
						break;
					}
                    dist += w;
                }
                total_path.total_dist = dist;

                if(valid) {
                    //检查MaxTrans（全局边数限制）
                    int total_edges = total_path.vers.size() - 1;
                    if(total_edges <= global_limit){
                        //简单去重：检查 candidate 中是否已有，检查 result 中是否已有
                        //由于 priority_queue 不好遍历，就把这一步去重放到从 candidate 弹出时做
                        bool exists_in_result = 0;
                        for(int result_i = 0; result_i < result.size();result_i++) {
                            if(is_same_path(result[result_i], total_path)){
								exists_in_result = true;
								break; 
							}
                        }
                        
                        if(!exists_in_result){
                            candidate.push(total_path);
                        }
                    }
                }
            }
        }

        if(candidate.empty()){
        	break;
		}

        // 从 candidate 中取出最短的，且不在 result 中的
        while(!candidate.empty()){
            Path cand = candidate.top();
            candidate.pop();
            
            bool exists = 0;
            for(int result_i = 0; result_i < result.size(); result_i++) {
                if(is_same_path(result[result_i], cand)){ 
					exists = 1; 
					break;
				}
            }
            if(!exists) {
                result.push_back(cand);
                //Yen's 算法每轮只需要增加一条最短的
                //把剩下的留在堆里给下一轮用
                break; 
            }
        }
    }

    //输出
    cout<<endl;
    cout<<"There are "<<result.size()<<" paths."<< endl;
    for(int i = 0;i < result.size();i++) {
        cout<<"Path "<<i<<": ";
        for(int j = 0;j<result[i].vers.size();j++){
            cout<<ver_list[result[i].vers[j]];
            if(j < result[i].vers.size() - 1){
            	cout<<" -> ";
			} 
        }
        cout<<", distance = "<<result[i].total_dist<<endl;
    }
}

int main(){
	//输入顶点数和边数 
	cin>>num_ver>>num_edge;
	//输入顶点
    for(int i=0;i<num_ver;i++) {
        cin>>ver_list[i];
        global_banned[i] = 0;
    }
	//输入边 
    for(int i=0;i<num_edge;i++) {
        string s1;
		string s2;
        int w;
        cin>>s1>>s2>>w;
        int u = get_pos(s1);
        int v = get_pos(s2);
        if(u != -1 && v != -1){
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

	cout<<endl;
	cout<<"Please enter your next request."<<endl;
    cout<<"Options include: ban X, unban X, maxTrans Y, paths A B k, quit."<<endl<<endl;
	
    string cmd;
    while(cin>>cmd) {
        if(cmd == "quit"){
        	break;
		}
        if(cmd == "ban"){
            string s;
			cin>>s;
            int pos = get_pos(s);
            if(pos != -1){
            	global_banned[pos] = 1;
			}
        }
        else if (cmd == "unban") {
            string s;
			cin>>s;
            int pos = get_pos(s);
            if(pos != -1){
            	global_banned[pos] = 0;
			}
        }
        else if(cmd == "maxTrans") {
            cin>>maxTransLimit;
        }
        else if(cmd == "paths") {
            string s1, s2;
            int k;
            cin>>s1>>s2>>k;
            //调用YEN's函数 
            kShortestPaths(s1, s2, k);
        }
        
        cout<<endl;
        cout<<"Please enter your next request."<<endl;
    	cout<<"Options include: ban X, unban X, maxTrans Y, paths A B k, quit."<<endl<<endl;
    }
}


