# RMQ问题
RMQ问题全称是区间最值查询问题（Range Minimum/Maximum Query），是指在一个数组中，预处理该数组以便能够高效地回答关于某个子区间内的最小值或最大值的查询。
## 问题描述
给定一个数组`A`，需要支持以下两种操作：
1. **预处理**：对数组`A`进行预处理，以便能够高效地回答查询。
2. **查询**：对于给定的区间`[L, R]`，返回数组`A`在该区间内的最小值或最大值。
3. **更新（可选）**：有些RMQ问题还需要支持对数组元素的更新操作。
## 常见解决方案
### 1. 线段树（Segment Tree）
线段树是一种二叉树数据结构，适用于动态数组的区间查询和更新操作。它将数组划分为若干个区间，并在每个节点存储该区间的最小值或最大值。查询和更新操作的时间复杂度均为`O(log n)`。
### 2. 稀疏表（Sparse Table）
稀疏表(ST表)是一种静态数据结构，适用于不需要更新操作的RMQ问题。它通过预处理数组的区间最值信息，使得查询操作可以在`O(1)`时间内完成。预处理时间复杂度为`O(n log n)`。
### 3. 倍增法（Doubling Method）
倍增法是一种基于预处理的技术，适用于静态RMQ问题。它通过预处理数组的区间最值信息，使得查询操作可以在`O(1)`时间内完成。预处理时间复杂度为`O(n log n)`。

## 伪代码实现
### 线段树伪代码
```cpp
class SegmentTree:
    function build(A, node, start, end):
        if start == end:
            tree[node] = A[start]
        else:
            mid = (start + end) / 2
            build(A, 2*node+1, start, mid)
            build(A, 2*node+2, mid+1, end)
            tree[node] = min(tree[2*node+1], tree[2*node+2])

    function query(node, start, end, L, R):
        if R < start or end < L:
            return ∞
        if L <= start and end <= R:
            return tree[node]
        mid = (start + end) / 2
        left_min = query(2*node+1, start, mid, L, R)
        right_min = query(2*node+2, mid+1, end, L, R)
        return min(left_min, right_min)
```
### 稀疏表伪代码
```cpp
function buildSparseTable(A):
    n = length(A)
    log = floor(log2(n)) + 1
    st = array[n][log]
    for i from 0 to n-1:
        st[i][0] = A[i]
    for j from 1 to log:
        for i from 0 to n - (1 << j):
            st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1])
    return st
function querySparseTable(st, L, R):
    j = floor(log2(R - L + 1))
    return min(st[L][j], st[R - (1 << j) + 1][j])
```
### 倍增法伪代码
```cpp
function buildDoubling(A):
    n = length(A)
    log = floor(log2(n)) + 1
    dp = array[n][log]
    for i from 0 to n-1:
        dp[i][0] = A[i]
    for j from 1 to log:
        for i from 0 to n - (1 << j):
            dp[i][j] = min(dp[i][j-1], dp[i + (1 << (j-1))][j-1])
    return dp
function queryDoubling(dp, L, R):
    j = floor(log2(R - L + 1))
    return min(dp[L][j], dp[R - (1 << j) + 1][j])
```

## 进一步思考
这类方法也可以用于求gcd、lcm等其他区间查询问题，只需在构建和查询过程中更改相应的操作即可。例如，在稀疏表中将`min`操作替换为`gcd`操作即可实现区间gcd查询。