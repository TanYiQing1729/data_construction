#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

//冒泡排序
template <class T>
void bubbleAsc(T* &arr, int n){
    bool swapped = false;
    do{
        swapped = false;
        for(int i=0;i<n-1;i++){
            if(arr[i] > arr[i+1]){
                T tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                swapped = true;
            }
        }
    }while(swapped);
}

//冒泡排序：用 lastSwap 记录本轮最后一次交换发生的位置，从而缩小下一轮需要比较的范围
template <class T>
void bubbleAscS(T* &arr, int n){
    int lastSwap = n-1;
    while(lastSwap>0){
        int bound = lastSwap;
        lastSwap = 0;
        for(int i=0;i<bound;i++){
            if(arr[i] > arr[i+1]){
                T tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                lastSwap = i+1;
            }
        }
    }
}

//原版的插入排序 
template <class T>
void insertionAsc(T* &arr, int n){
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] < arr[j]){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

//遇到顺序正确直接终止内层循环，带break的插入排序 
template <class T>
void insertionAscB(T* &arr, int n){
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] < arr[j]){
                T tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            else
                break;
        }
    }
}

// 希尔排序（升序）
// 思想：把数组按“步长 d”分组，对每组做插入排序；然后不断缩小步长（一般 d/=2）
// 当 d=1 时，就等价于对整个数组做一次插入排序，但此时数组已“基本有序”，所以整体更快。
template <class T>
void shellAsc(T* &arr, int n){
    int curSep = n;    // 步长（间隔）初始设为 n，马上会在循环里变成 n/2

    do{
        curSep = curSep / 2;    // 每一轮把步长减半：n/2, n/4, n/8, ... , 1
        // 从 curSep 开始扫描到末尾：
        // i 表示当前要“插入”的元素下标，和 i-curSep, i-2*curSep ... 这些元素构成同一组
        for(int i = curSep; i < n; i++){
            // 对“同一组”做插入排序（组内相邻元素的下标差为 curSep）
            // j 从 i-curSep 开始，向前跳 curSep
            for(int j = i - curSep; j >= 0; j -= curSep){
                // 如果后面的元素（j+curSep）比前面的元素（j）小，则交换
                // 这相当于在做“按 curSep 间隔的插入排序”
                if(arr[j + curSep] < arr[j]){
                    T tmp = arr[j];
                    arr[j] = arr[j + curSep];
                    arr[j + curSep] = tmp;
                }
            }
        }
    } while(curSep > 1); // 当 curSep 变成 1 时，本轮做完就结束（因为下一轮会变成 0 不合理）
}

template <class T>
void shellAscB(T* &arr, int n){
    // we play separation of n/2, then n/4, n/8, etc...
    int curSep = n;
    do{
        curSep = curSep / 2;
        for(int i=curSep;i<n;i++){
            for(int j=i-curSep;j>=0;j-=curSep){
                if(arr[j+curSep] < arr[j]){
                    T tmp = arr[j];
                    arr[j] = arr[j+curSep];
                    arr[j+curSep] = tmp;
                }
                else
                    break;    //带break的 
            }
        }
    }while(curSep > 1);
}

// 快速排序的一次划分（partition）过程：
// 选取“区间第一个元素”为枢轴 pivot（注意：这里 pivot 的值隐含在不断交换中，并未单独保存变量）
// 目标：通过左右指针 le/ri 的移动与交换，把 pivot 放到它最终应在的位置上
// 返回值：pivot 最终所在的下标（也就是 le == ri 时的位置）
template <class T>
int quickPivot(T* &arr, int n, int sIndex, int eIndex){ //use first element as pivot, put pivot in correct position, return index
    // le：从左往右扫描的指针（left）
    // ri：从右往左扫描的指针（right）
    int le = sIndex;
    int ri = eIndex;
    // 当 le 与 ri 没有相遇前，不断进行“从右找小、从左找大”的交换
    while(le < ri){
        // 1) 先从右往左找：寻找一个“比左侧当前元素 arr[le] 小”的元素
        // 条件 arr[le] <= arr[ri] 表示右边这个元素不需要换到左边（它够大/不小于左元素）
        // 所以 ri-- 继续往左找，直到找到 arr[ri] < arr[le]（或 le==ri）
        while(le < ri && arr[le] <= arr[ri]) ri--;

        // 找到了 arr[ri] < arr[le]：把它交换到左边 le 的位置
        // 这一步可以理解为：把“小元素”放到左侧区域
        if(le < ri){
            T tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            le++; // 左指针右移，左侧“已处理区”扩大
        }

        // 2) 再从左往右找：寻找一个“比右侧当前元素 arr[ri] 大”的元素
        // 条件 arr[le] <= arr[ri] 表示左边这个元素不需要换到右边（它够小/不大于右元素）
        // 所以 le++ 继续往右找，直到找到 arr[le] > arr[ri]（或 le==ri）
        while(le < ri && arr[le] <= arr[ri]) le++;

        // 找到了 arr[le] > arr[ri]：把它交换到右边 ri 的位置
        // 这一步可以理解为：把“大元素”放到右侧区域
        if(le < ri){
            T tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            ri--; // 右指针左移，右侧“已处理区”扩大
        }
    }

    // le == ri，相遇位置就是 pivot 应该在的位置（pivot 已通过来回交换被“送”到这里）
    return le;
}


//快速排序(上面那个是辅助函数) 
template <class T>
void quickAsc(T* &arr, int n, int sIndex, int eIndex){ //start index, end index inclusive
    if(sIndex >= eIndex) return;    //终止条件 
    int pivotPos = quickPivot(arr,n, sIndex, eIndex);    //枢轴pivot位置 
    quickAsc(arr,pivotPos,sIndex,pivotPos-1);    //递归 
    quickAsc(arr,n-pivotPos-1,pivotPos+1,eIndex);
}

//最熟悉的选择排序 
template <class T>
void selectionAsc(T* &arr, int n){
    T max;
    int mPos;
    //从数组末尾向前遍历，逐渐缩小未排序部分的范围
    for(int j=n-1;j>=1;j--){
        max = arr[0];    //最大值 
        mPos = 0;
        for(int i=1;i<=j;i++){
            if(max < arr[i]){
                max = arr[i];
                mPos = i;
            }
        }
        //最大甩到后面去 
        arr[mPos] = arr[j];
        arr[j] = max;
    }
}

template <class T>//归并排序
void mergeSortAsc(T* &arr, int n){
    int mergeStep = 1;   //当前归并的子数组大小，初始为1（单个元素）
    T* arr2 = new T[n];    //创建临时数组用于归并操作，笔记里写了注意点 
    //当归并步长小于数组长度时，继续归并
	while(mergeStep < n){
		//每次处理两个相邻的子数组进行归并
        //每次循环处理两个mergeStep长度的子数组
        for(int i=0;i<n;i+=2*mergeStep){ // increment is 2*mergeStep, since we are merging every 2 lists
            //定义三个指针：
            //j：左子数组起始索引
            int j=i;
            //k：右子数组起始索引
            int k=i+mergeStep;
            //z：临时数组的写入索引
            int z=i;
            
            
            //按顺序写入新数组 
            //归并两个子数组：将较小的元素依次放入临时数组
            //条件：两个子数组都还有元素，且右子数组未越界
			while(j<i+mergeStep && k<i+2*mergeStep && k<n){ //when true, we haven't run into end of list nor finished current list
                //保持排序稳定性：当元素相等时，左边的先放入
				if(arr[j] <= arr[k]){ // if = is left out, we won't have a stable merge sort.
                    arr2[z] = arr[j];
                    z++;
                    j++;
                }
                else{
                    arr2[z] = arr[k];
                    z++;
                    k++;
                }
            }
            //如果左(右)子数组还有剩余元素，全部复制到临时数组
            while(j<i+mergeStep && j<n){
                arr2[z] = arr[j];
                z++;
                j++;
            }
            while(k<i+2*mergeStep && k<n){
                arr2[z] = arr[k];
                z++;
                k++;
            }
        }

		//将临时数组中归并好的数据复制回原数组
        for(int i=0;i<n;i++){ // putting the sorted runs of length 2*mergeStep into arr.
            arr[i] = arr2[i];
        }
        //将归并步长加倍，准备下一轮更大子数组的归并
        mergeStep = mergeStep * 2;
    }
    //释放临时数组内存
    delete [] arr2;
}

int* generateRandom(int num, int min, int max){ //generate random numbers between min and max, inclusive
    int* tmp = new int[num];
    for(int i=0;i<num;i++)
        tmp[i] = rand() % (max+1-min) + min;
    return tmp;
}

template <class T>
T* dupArray(T* arr, int n){
    T* tmp = new T[n];
    for(int i=0;i<n;i++){
        tmp[i] = arr[i];
    }
    return tmp;
}


void printIArr(int* arr, int n){
    // print, at most 10 per row
    int count = 0;
    for(int i=0;i<n;i++){
        cout << left << setw(10) << arr[i];
        count = (count+1)%10;
        if(count==0) cout << endl;
    }
    if(count!=0) cout << endl;
    cout << endl;
}

int main(){
    srand(time(NULL));
    int* seq1 = generateRandom(70,0,100);
    int* seq2 = generateRandom(2000,0,100000);

    int* tmp = NULL;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1,70);
    insertionAsc<int>(tmp,70);

    cout << "Insertion: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    insertionAscB<int>(tmp,70);

    cout << "Insertion with Break: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    shellAsc<int>(tmp,70);

    cout << "Shell: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1,70);
    bubbleAsc<int>(tmp,70);

    cout << "Bubble: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    bubbleAscS<int>(tmp,70);

    cout << "Better Bubble: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    quickAsc<int>(tmp,70,0,69);

    cout << "Quick Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    tmp = dupArray<int>(seq1,70);
    selectionAsc<int>(tmp,70);

    cout << "Selection Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;



    tmp = dupArray<int>(seq1,70);
    mergeSortAsc<int>(tmp,70);

    cout << "Merge Sort: " << endl;
    printIArr(tmp,70);
    delete [] tmp;

    cout << "Insertion 70: ";
    clock_t start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        insertionAsc<int>(tmp,70);
        delete [] tmp;
    }
    clock_t end = clock();
    double timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 70 with break: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        insertionAscB<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        shellAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell with break 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        shellAscB<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        bubbleAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        bubbleAscS<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        quickAsc<int>(tmp,70,0,69);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        selectionAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 70: ";
    start = clock();
    for(int i=0;i<10000;i++){
        tmp = dupArray<int>(seq1,70);
        mergeSortAsc<int>(tmp,70);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        insertionAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000 with break: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        insertionAscB<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        shellAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell with break 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        shellAscB<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        bubbleAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        bubbleAscS<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        quickAsc<int>(tmp,2000,0,1999);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        selectionAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 2000: ";
    start = clock();
    for(int i=0;i<1000;i++){
        tmp = dupArray<int>(seq2,2000);
        mergeSortAsc<int>(tmp,2000);
        delete [] tmp;
    }
    end = clock();
    timess = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;
}
