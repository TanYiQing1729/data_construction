#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    //初始分拆：只有N本身
    vector<int> partition(N, 1);
    partition[0] = N;
    int length = 1;  // 当前分拆的长度
    
    while (true) {
        // 输出当前分拆
        for (int i = 0; i < length; i++) {
            if (i > 0) cout << "+";
            cout << partition[i];
        }
        cout << endl;
        
        // 如果当前分拆全是1，说明已经生成所有分拆
        if (partition[0] == 1) {
            break;
        }
        
        // 寻找需要减少的位置
        int i = length - 1;
        while (i > 0 && partition[i] == 1) {
            i--;
        }
        
        // 减少当前位置的值
        partition[i]--;
        
        // 计算剩余需要分配的值
        int remaining = 1;
        for (int j = i + 1; j < length; j++) {
            remaining += partition[j];
        }
        
        // 重新分配剩余的值，保持非递增
        length = i + 1;
        while (remaining > 0) {
            if (remaining >= partition[i]) {
                partition[length] = partition[i];
                remaining -= partition[i];
            } else {
                partition[length] = remaining;
                remaining = 0;
            }
            length++;
        }
    }
    
    return 0;
}
