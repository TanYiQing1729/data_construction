#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

//发现这些是全局变量都要用的 
int row;
int column;
struct pos{
	int r;
	int c;
};
string input; 
vector<string> board;

//移动向量
int dr[4] = {-1, 1,  0, 0};
int dc[4] = { 0, 0, -1, 1};

//被照亮的地方，用二维数组表示
vector< vector<int> > light;
vector< vector<char> > state; 

//将输入的一维向量变成二维的 
vector<string> cut(string s, int r, int c){
	vector<string> al_cut;
	al_cut.resize(r); 
	for(int i=0;i<r;i++){
		al_cut[i] = s.substr(i*c ,c);
	}
	return al_cut;
}

//界定棋盘范围 
bool in_boarder(int r, int c){
	if(r>=0 && r<row && c>=0 && c<column){
		return 1;
	}
	else{
		return 0;
	}
}

//判断函数:黑色格和数字格不能通过光线 
bool is_black(int r, int c){
	char grid = board[r][c];
	if(grid == '0' ||
	   grid == '1' ||
	   grid == '2' ||
	   grid == '3' ||
	   grid == '4' ||
	   grid == 'X'){
	   	return 1;
	   }
	else{
		return 0;
	}
}

//判断函数：白色格可以透过光线 
bool is_white(int r, int c){
	char grid = board[r][c];
	if(grid == '.'){
	   	return 1;
	   }
	else{
		return 0;
	}
} 

//判断函数：先讨论数字格周围的情况 
bool is_number(int r, int c){
    char grid = board[r][c];
    if(grid == '0' ||
	   grid == '1' ||
	   grid == '2' ||
	   grid == '3' ||
	   grid == '4' ) {
	   	return 1;
	   }
	else{
		return 0;
	}
}

//还需要知道数字格具体是几
int get_number(int r, int c){
	if(is_number(r,c)){
		return board[r][c] - '0';
	}
	return 0;   //不是数字格返回0 
}

//判断函数：是否会被别的灯照亮。找这个格子上下左右是否有灯，遇到黑色块停止。
//这是在这个地方可能放灯的情况下判断的，所以不用管是不是黑色块。 
bool find_lamp(int r, int c){
	for(int i=0;i<4;i++){
		int r_moved = r + dr[i];
		int c_moved = c + dc[i];    //要移动格子 
		while(in_boarder(r_moved, c_moved) == 1 && !is_black(r_moved,c_moved)){
			if(state[r_moved][c_moved] == 'L'){
				return 1;
			}
			r_moved += dr[i];
			c_moved += dc[i];
		}
	}
	return 0;
}

//更新每个点的光照情况 
void adjust(int r, int c, int delta){
	light[r][c] += delta; 
	for(int i=0;i<4;i++){
		int r_moved = r + dr[i];
		int c_moved = c + dc[i];    //要移动格子
		while(in_boarder(r_moved, c_moved)&& !is_black(r_moved, c_moved)){
			light[r_moved][c_moved] += delta;
			r_moved += dr[i];
			c_moved += dc[i];
		}
	}
} 

//操作函数：放灯
bool put_light(int r, int c){
	if(find_lamp(r,c) == 0 && state[r][c] == 'U'){    //可以放灯的条件
		state[r][c] = 'L';
		adjust(r, c, 1);
		return 1;
	}
	else{
		return 0;
	}
} 

//操作函数：撤灯
bool remove_light(int r, int c){
	if(state[r][c] == 'L'){
		state[r][c] = 'U';
		adjust(r, c, -1);
		return 1;
	}
	else{
		return 0;
	}
} 

//操作函数：更新状态（不能放灯） 
bool cannot_put_light(int r, int c){
	if(is_black(r,c)){
		return 1;
	}
	else if(state[r][c] == 'L'){
		return 0;
	}
	else{
		state[r][c] = 'B';
		return 1;
	}
}


//在约束条件下的一次操作, 如果返回false代表没有操作，说明有错误，代码会返回上一次single_work的时候
//这里的约束条件是基于规则的约束 
//而且这里用了引用传入，目的是能够让changed在函数内部被改动 
bool single_work(bool &changed){
	//1：数字格约束
	//对每个数字黑格，统计它四邻白格
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(is_number(i, j)){
				int need = get_number(i, j);     //统计数字格周围要多少个灯
				int num_lamp = 0;                    //初始化周围没有灯
				vector<pos> unknown;
				
				for(int k=0;k<4;k++){                //看看数字格周围情况 
					int r_moved =i + dr[k];
					int c_moved =j + dc[k];
					if(!in_boarder(r_moved, c_moved) || is_black(r_moved, c_moved)){
						continue;
					}
					if(state[r_moved][c_moved] == 'L'){
						num_lamp++;
					}
					if(state[r_moved][c_moved] == 'U'){
						pos p;
						p.r = r_moved;
						p.c = c_moved;
	                    unknown.push_back(p);
					}
				}
				
				//接下来分类讨论情况
				//已放灯 > 需要灯
				if(num_lamp > need){
					return 0;
				} 
				
				//已放灯 == 需要灯 
				//这里非常重要，已放灯 == 需要灯不代表unknown里面没东西，反例是数字格为0 
				if(num_lamp == need){
					for(int m=0;m<unknown.size();m++){
						//让它们不能放灯 
						if (state[unknown[m].r][unknown[m].c] == 'U'){    
	                        if (!cannot_put_light(unknown[m].r,unknown[m].c)){    //不准放灯的同时做是否可以不准放灯的检测 
	                        	return 0;
							}
	                        changed = 1;
	                    }
					} 
				} 
				
				//已放灯+未知 == 需要灯 
				if(num_lamp + unknown.size() == need){
					for(int m=0;m<unknown.size();m++){
						//这里开始放灯
						if (state[unknown[m].r][unknown[m].c] != 'L'){    //防止因为别的操作这里已经放灯了 
	                        if (!put_light(unknown[m].r,unknown[m].c)){    //放灯的同时做是否可以放灯的检测 
	                        	return 0;
							}
	                        changed = 1;
	                    } 
					} 
				}
				
				//已放灯+未知 < 需要灯
				//这是出现问题的 
				if (num_lamp + unknown.size() < need){
					return 0;
				}
			}	
		}
	}

	
	//2：光照约束
	//对于任意一个白格，如果它是黑暗的，那么检查它的四条线，如果有不被阻挡的灯，那么它应该得是光明的
	//如果在方向上有空白可以放灯的位置，那么那个位置是可能的灯的位置
	//如果在方向上没有可以放灯的位置，那么它那个位置必须放灯
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(light[i][j] == 0 && is_white(i, j) ==1 && state[i][j] != 'L'){
				bool ano_place = 0;   //看路径上是否有别的地方可以放灯 
				for(int k=0;k<4;k++){
					int r_moved = i + dr[k];
					int c_moved = j + dc[k];
					while(in_boarder(r_moved, c_moved)&& !is_black(r_moved, c_moved)){
						if(state[r_moved][c_moved] == 'L'){
							ano_place = 1;  //有灯也设置成1，这样方便最后判断 
							break;
						}
						if(state[r_moved][c_moved] == 'U'){
							if(!find_lamp(r_moved, c_moved)){
								ano_place = 1;
								break;
							}
						} 
						r_moved += dr[k];
						c_moved += dc[k];
					}
					if(ano_place == 1){
						break;
					}
				}
				if(ano_place == 0){
					if(state[i][j] == 'B'){
						return 0;
					}
					if(!put_light(i,j)){   //也是一样，一边放灯一边判断能不能放灯 
						return 0;
					}
					changed = 1; 
				}
			}
		}
	}

	
	//3: 不能放灯约束 
	//如果一个白格它的四条线上有没有被遮挡的灯，那么它应该是不能放灯的
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(is_white(i, j) == 1 && state[i][j] == 'U'){
				if(find_lamp(i,j) == 1){
					if(!cannot_put_light(i,j)){
						return 0;
					}
					changed = 1;
				}
			}
		}
	} 
	
	//最后一个是用于检查的，提高代码的健壮性
	//4：灯互相不可见 
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(state[i][j] == 'L'){
				if(find_lamp(i,j)==1){
					return 0;
				}
			}
		}
	} 
	return 1;
} 

//不断调用single_work 
bool work(){
	bool changed = 1;
    while(changed){
        changed = 0;
        if (!single_work(changed)){
        	return 0; 
		}  
    }
    return 1;
} 


//启动方式 
//接下来是比较重要的地方，优先从数字出发，而且是可能性较小的 
struct Choice {
    int r;
	int c; 
    bool can_put_lamp;  //是否可以放灯 
};

bool num_first(Choice &ch){
	int best_score = 100000;
	bool found = 0;
	//这些和前面一样的 
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(is_number(i, j)){
				int need = get_number(i, j);     //统计数字格周围要多少个灯
				int num_lamp = 0;                    //初始化周围没有灯
				vector<pos> unknown;
				
				for(int k=0;k<4;k++){                //看看数字格周围情况 
					int r_moved =i + dr[k];
					int c_moved =j + dc[k];
					if(!in_boarder(r_moved, c_moved) || is_black(r_moved, c_moved)){
						continue;
					}
					if(state[r_moved][c_moved] == 'L'){
						num_lamp++;
					}
					if(state[r_moved][c_moved] == 'U'){
						pos p;
						p.r = r_moved;
						p.c = c_moved;
	                    unknown.push_back(p);
					}
				}
				
				//分类讨论
				int residual = need - num_lamp; // 还需要多少盏灯
				if (unknown.empty() || residual <= 0 || residual >= unknown.size()){
					continue;
				}
				
				for(int k=0;k<unknown.size();k++){
					bool can_put_lamp = !find_lamp(unknown[k].r,unknown[k].c);
					int score = residual * 1000 + unknown.size() * 100 + (can_put_lamp?0:10) + ((light[unknown[k].r][unknown[k].c] == 0)?0:1);
					if(score < best_score){
						best_score = score;
						ch.r = unknown[k].r;
						ch.c = unknown[k].c;
						ch.can_put_lamp = can_put_lamp;
						found = 1;
					}
				}
			}
		}
	}
	return found;
} 

//这是没有办法从数字出发的 
bool no_number_first(Choice &ch){
	int best_score = 100000;
	bool found = 0;
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(!is_white(i,j) || state[i][j] != 'U'){
				continue;
			}
			bool can_put_lamp = !find_lamp(i,j);
			int score = 1000 * (can_put_lamp?1:0) + 100 * ((light[i][j] == 0)?0:1);
			if(score < best_score){
				best_score = score;
				ch.r = i;
				ch.c = j;
				ch.can_put_lamp = can_put_lamp;					
				found = 1;
			}
		}
	}
	return found;
}

//检查是否填完 
bool check(){
	//检查白色格都得被点亮 
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(is_white(i,j) == 1){
				if(light[i][j] <= 0){
					return 0;
				}
			}
		}
	}
	
	//检查数字格周围灯是否满足
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(is_number(i,j) == 1){
				int need = get_number(i,j);
        		int num_lamp = 0;
        		for(int k=0;k<4;k++){
        			int r_moved = i + dr[k];
        			int c_moved = j + dc[k];
        			if(!in_boarder(r_moved, c_moved)|| is_black(r_moved, c_moved)){
						continue;
					}
					if(state[r_moved][c_moved] == 'L'){
						num_lamp++;
					}
				}
				if (num_lamp != need){
					return 0;
				}
			}
		}
	} 
	
	//检查灯是否有相互照亮
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			if(state[i][j] == 'L'){
				if(find_lamp(i,j)==1){
					return 0;
				}
			}
		}
	}
	return 1; 
}


//dfs
bool dfs(){
	if(!work()){
		return 0;
	}
	if(check()){
		return 1;
	}
	Choice ch;
	if(!num_first(ch)){
		if(!no_number_first(ch)){
			return 0;
		}
	}
	
	int r = ch.r;
	int c = ch.c;
	
	//先看这个地方能不能放灯 
	if(ch.can_put_lamp){
		vector<vector<char> > temp_state1 = state;
        vector<vector<int> > temp_light1 = light;
        if(put_light(r,c)) {
            if (dfs()){
            	return 1;
			}
        }
        //回溯 
        state = temp_state1;
        light = temp_light1;
	}
	
	//再分析不能放灯的情况
	vector<vector<char> > temp_state2 = state;
    vector<vector<int> > temp_light2 = light;
    if(cannot_put_light(r,c)) {
        if (dfs()){
           	return 1;
		}
    }
    //回溯 
	state = temp_state2;
    light = temp_light2;
    
    return 0;
}


int main(){
	//数据读取 
	cin >> row;
	cin >> column;
	cin >> input;
	
	//数据转换：将输入的一维向量变成二维的
	board = cut(input, row, column); 

	state.assign(row, vector<char>(column, 'B')); 		//先默认都不可放
    light.assign(row, vector<int>(column, 0));		//初始照明计数为 0
	
	// 计时开始（仅求解阶段）
	/*
    auto t0 = std::chrono::steady_clock::now();
	*/
	
	//初始化白格
    for (int i=0;i<row;i++) {
        for (int j=0;j<column;j++) {
            if (is_white(i,j)){
            	state[i][j] = 'U';
			}
        }
    }
    
    // 求解
    bool success = dfs();
    
    // 计时结束并打印
    /*
	auto t1 = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cerr << "Solve time: " << ms << " ms\n";
    */
    
    if (!success) {
        cout <<"No solution"<<endl;
        return 0;
    }
    
    // 输出：对白格输出 L 或 .，墙/数字保持原样
    for(int i=0;i<row;i++){
        string output = board[i]; // 先拷贝原始行，保留墙与数字
        for(int j=0;j<column;j++){
            if(is_white(i,j)) {
                output[j] = (state[i][j] == 'L') ? 'L' : '.';
            }
        }
        cout<<output;
    }
    return 0;
}
