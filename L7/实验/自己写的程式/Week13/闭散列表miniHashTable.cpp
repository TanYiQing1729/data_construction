#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

/*
  闭散列（开放寻址）的一些探测函数实现和哈希函数实现。
  本文件实现了一个小型模板哈希表 miniHashTable，支持线性探测与二次探测，
  并提供了插入、删除、查找、打印表项和统计冲突次数的功能。
*/

/* 二次探测函数（quadratic probing）
   st: 起始位置（在使用中我们会把 hashCell + tableSize 作为 st 传入以避免负数）
   tryNum: 当前是第几次探测（从0或1开始视调用者而定）
   该实现采用交替正负平方的序列：+1^2, -1^2, +2^2, -2^2, ...
   注意：这里的 tryNum 从 1 开始时按代码逻辑交替增加偏移。
*/

int quad_probe_next(int st, int tryNum){
    //quadratic probing scheme
    if(tryNum%2==1) return st+((tryNum+1)/2)*((tryNum+1)/2);    //巧妙实现随着trynum++，((tryNum+1)/2)*((tryNum+1)/2)就是正负1,4,9 
    else return st - (tryNum/2) * (tryNum/2);
}

/* 线性探测函数（linear probing）
   st: 起始位置（同上）
   tryNum: 探测次数（会把 tryNum 累加到 st 上）
   等价于传统的 st + i。
*/

int linear_probe_next(int st, int tryNum){
    return st + tryNum;
}

/* 
	最简单的哈希函数：取模 
	其实就是我们说的散列函数 
*/

int hash1(int x, int hashMax){
    return x % hashMax;
}

/* 
	较“复杂”但任意的哈希函数示例（演示用途）
	这里做了三次乘方再取模：tmp1^3 % hashMax
	注：hashMax 建议满足一定条件（注释中提到 2 mod 3），但示例中未强依赖。
*/

int hash2(int x, int hashMax){
    // Here, hashMax needs to be 2 mod 3.
    int tmp1 = x%hashMax;
    int tmp2 = (tmp1 * tmp1) % hashMax;
    tmp2 = (tmp2 * tmp1) % hashMax;
    return tmp2;
}

/* 模板类：miniHashTable
   - 使用开放寻址法（closed hashing / open addressing），数组为底层存储
   - inUse[i] 表示当前 i 单元是否被占用（当前有效元素）
   - onceUsed[i] 表示 i 单元是否曾经被使用过（被占用过或者被删除过），用于查找终止条件
   - hashfn: 指向哈希函数（签名 int f(T,int)）
   - probefn: 指向探测函数（签名 int f(int,int)），探测函数将返回下一个候选索引（或相对位置）
   - collisions: 插入时遇到已被占用而继续探测的次数统计
*/


template <class T>
class miniHashTable{
    private:
        int tableSize; // hashtable size better be a prime that is 11 mod 12.
        // 哈希表大小，最好选质数以降低冲突
        int numData;   // 当前表中元素个数
        T* hashEntries; // 存放元素的数组
        bool* inUse;    // 当前单元是否被占用（有效元素）
        bool* onceUsed; // 单元是否曾经被使用过（用于在查找时决定是否继续）
        int (*hashfn)(T,int); // 哈希函数指针
        int (*probefn)(int,int); // 探测函数指针
        //probefn 指向函数，参数为 (int, int)，返回 int。用于返回下一个候选索引/位置的计算结果。
        /*
			上述两行仔细讲讲
			一般形式：返回类型 (*指针名)(参数类型列表)
			例如：int (*f)(double, char) 表示 f 是一个指向函数的指针，该函数接收 (double, char)，返回 int。
			在使用中，我们可以让它指向我们想要使用的函数，如hash1,
			eg：hashfn = NULL，hashfn = f等等 
		*/ 
        int collisions = 0; // 统计插入时发生的冲突次数
    public:
        miniHashTable(){
            //default table size set as 47
            //默认47 
            numData = 0;
            collisions = 0;
            tableSize = 47;
            hashEntries = new T[47];
            inUse = new bool[47];
            onceUsed = new bool[47];
            for(int i=0;i<47;i++){
                inUse[i] = false;
                onceUsed[i] = false;
            }
            hashfn = NULL;
            probefn = NULL;
        }
        // 可指定表大小的构造函数（假设传入的 table_size 合理）
        miniHashTable(int table_size){
            // pray that whatever's given to us is a prime. or else things can get real ugly.
            numData = 0;
            collisions = 0;
            tableSize = table_size;
            hashEntries = new T[table_size];
            inUse = new bool[table_size];
            onceUsed = new bool[table_size];
            for(int i=0;i<table_size;i++){
                inUse[i] = false;
                onceUsed[i] = false;
            }
            hashfn = NULL;
            probefn = NULL;
        }
        ~miniHashTable(){
            delete [] hashEntries;
            delete [] inUse;
            delete [] onceUsed;
        }
        //设置hash函数 
        void setHashFn(int (*f)(T, int)){
            if(hashfn==NULL)
                hashfn = f;
            // 只能设置一次哈希函数（防止中途重置导致不一致）
			else{
                cout << "Cannot reset hash function." << endl;
            }
        }
        //设置探测函数，同样只能设置一次 
        void setProbeFn(int (*f)(int,int)){
            if(probefn==NULL)
                probefn = f;
            else{
                cout << "Cannot reset probe function." << endl;
            }
        }
        bool isEmpty(){
            return (numData==0);
        }
        bool isFull(){
            return (numData==tableSize);
        }
        
        /* 查找操作 searchData
        	searchData 的目的是判断给定的关键码 x 是否存在于哈希表中。遇到冲突的方式是开放寻址。 
           - 使用 hashfn 计算起始单元 hashCell
           - 使用 onceUsed 作为循环条件：只要当前位置曾被使用过，就可能在后续位置找到目标
             （如果某个位置从未使用过，说明从起始位置到此位置的所有探测路径都不会有该元素）
           - 注意：这里先比较 hashEntries[hashNext] 是否等于 x，再移动到下一个位置
           		//上面感觉不是人话，详细解释一下
				//查找一个元素，如果在hashcell找到了，那万事大吉
				//如果没找到，那么看onceUsed是否为1，如果onceUsed为1，说明它是发生了冲突，就接着往后面找
				//否则，由我们的算法设计，可以直接保证找不到 
           - 返回 true：找到了元素；返回 false：未找到
        */
        bool searchData(T x){
            int k=0;
            //使用 hashfn 计算起始位置 hashCell，把 hashNext 设为 hashCell。
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            while(onceUsed[hashNext]){
                k++;    //往后面找 
                if(hashEntries[hashNext]==x) return true;    //找到返回1 
                else hashNext = probefn(hashCell+tableSize,k) % tableSize;    //否则更新hashNext，接着往后面找 
            }
            return false;
        }
        /* 插入操作 insertData
           - 先检查是否已满
           - 计算起始单元 hashCell
           - 如果当前位置 inUse，则说明冲突，调用探测函数寻找下一个候选并统计 collisions
           - 找到空闲单元后放入元素，并将 inUse 与 onceUsed 标记为 true
           - numData++ 表示当前元素数增加
           说明：使用 onceUsed 可以在删除后保留“曾经被占用”的信息，以便查找时继续探测。
        */
        void insertData(T x){
            int k=0;
            //先检查是否已满
            if(isFull()){
                cout << "Table full." << endl;
                return;
            }
            //计算起始单元 hashCell
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            //如果当前位置 inUse，则说明冲突，调用探测函数寻找下一个候选并统计 collisions
            while(inUse[hashNext]){
                k++;
                hashNext = probefn(hashCell+tableSize,k) % tableSize;
                collisions++;
            }
            //更新相关数据 
            numData++;
            hashEntries[hashNext] = x;
            inUse[hashNext] = true;
            onceUsed[hashNext] = true;
        }
        /* 删除操作 deleteData
           - 从 hashCell 开始，按照探测序列寻找元素
           - 当遇到 inUse[hashNext] 为 false 时停止（如果在探测序列上已经没有有效元素，说明没找到）
           - 找到后将 inUse 标记为 false（但保持 onceUsed 为 true），numData--
           说明：我们并未清除 onceUsed 标志，以便查找其它在冲突链后面的元素时不误终止。
        */
        void deleteData(T x){
            int k=0;
            int hashCell = hashfn(x,tableSize);
            int hashNext = hashCell;
            //当遇到 inUse[hashNext] 为 false 时停止（如果在探测序列上已经没有有效元素，说明没找到）
            while(inUse[hashNext]){
                k++;
                if(hashEntries[hashNext]==x){
                    //更新有关参数 
					inUse[hashNext] = false;
                    numData--;
                    return;
                }
                else hashNext = probefn(hashCell+tableSize,k) % tableSize;
            }
            return;
        }
        // 打印整个表的状态（每个格子以及是否包含元素）
        void printTable(){
            for(int i=0;i<tableSize;i++){
                cout << "Cell " << i << ": ";
                if(inUse[i]) cout << hashEntries[i];
                cout << endl;
            }
        }
        int getCollisionCount(){
            return collisions;
        }
};

/* 用来测试不同哈希函数与探测策略的辅助函数 test
   - 创建 miniHashTable<int>（大小为 23）
   - 设置哈希函数与探测函数
   - 生成 15 个随机数并依次插入，期间每 5 个数字打印一次表状态
   - 最后输出冲突计数
*/

void test(int (*h)(int,int),int (*p)(int,int)){
    miniHashTable<int> ht(23); //the table with 47 entries should be fine.
    ht.setHashFn(h);
    ht.setProbeFn(p);
    int randomNums[15];
    for(int i=0;i<15;i++)
        randomNums[i] = rand() % 10000;
    for(int i=0;i<15;i++){
        cout << randomNums[i] << " (" << h(randomNums[i],23) << "), ";
        ht.insertData(randomNums[i]);
        if(i%5==4){
            cout << endl;
            cout << "Current Table is as follows:" << endl;
            ht.printTable();
            cout << endl;
        }
    }
    cout << "Collision count: " << ht.getCollisionCount() << endl;
    cout << endl;
}

int main()
{
    srand(time(NULL));
    cout << "Simplest hash and linear probe:" << endl;
    test(hash1,linear_probe_next);
    
    cout << "Simplest hash and quadratic probe:" << endl;
    test(hash1,quad_probe_next);
    
    cout << "Not so simple hash and linear probe:" << endl;
    test(hash2,linear_probe_next);
    
    cout << "Simplest hash and linear probe:" << endl;
    test(hash2,quad_probe_next);

    return 0;
}
