# 数据结构与算法
## 树和二叉树
### 树的基本术语
**结点：** 树的一个独立单元。包含一个数据元素及若干指向其子树的分支
**结点的度：** 结点拥有的子树数目称为结点的度
**树的度：** 树内各结点度的最大值
**叶子：** 度为0的结点
**非终端结点：** 度不为0的结点。除根结点外，非终端结点也称内部结点
**双亲和孩子：** 结点的子树的根称为该结点的孩子，相应地，该结点称为孩子地双亲。
**层次：** 结点的层次从根开始定义起，根为第一层，根的孩子为第二层。书中任意结点的层次为其双亲结点的层次加1
**树的深度：** 树中结点的最大层次称为树的深度或者高度
**有序树和无序树：** 如果将树中结点的各子树看成从左到右是有次序的（即不能互换），则称该树为有序树
**森林：** 是m(m >= 0)棵互不相交的树的集合。对树中的每个结点而言，其子树的集合即为森林
### 二叉树的定义
**性质：** 
1. 二叉树每个结点至多只有两棵树（即二叉树中不存在度大于2的结点）
2. 二叉树的子树有左右之分，其次序不能任意颠倒
### 二叉树的性质
**性质1**  在二叉树的第i层至多有2^(i-1)个结点(i >= 1)
**性质2**  深度为k的二叉树最多有2^k - 1个结点
**性质3**  对任意一棵二叉树T，如果其终端结点树为n0，度为2的结点数为n2，则n0 = n2 + 1;
**满二叉树：** 深度为k的，且含有2^k - 1个结点的二叉树
**完全二叉树：** 深度为k，有n个结点的二叉树，当且仅当其每个结点都与深度为k的满二叉树中编号从1至n的结点一一对应时，称之为完全二叉树
**性质4**  具有n个结点的完全二叉树的深度为 求底(log2n) + 1
**性质5**  如果对一棵有n个结点的完全二叉树的结点按层序编号，则对任一结点i(1 <= i <= n)有
    (1) 如果i=1，则结点i是二叉树的根，无双亲；如果i > 1，则其双亲是结点 求底(i/2)
    (2) 如果2i>n，则结点i无左孩子，否则其左孩子是结点2i
    (3) 如果2i+1>n，则结点i无右孩子，否则其右孩子是结点2i+1

## 图的应用
### 最短路径
#### Dijkstra算法
##### 基本思想
>1. 指定源点u
>2. 结点集合V被划分为两个部分：集合S和集合V-S，S的作用是记录已求出最短路径的顶点(以及相应的最短路径长度)，而V-S则是记录还未求出最短路径的顶点(以及该顶点到起点s的距离)。
>3. 初始时，集合S中仅包含u，最短路径长度为0。集合V-S所包含的结点到源点的最短路径待定，称从源点出发只经过集合S中的结点到达集合V-S的结点的路径为特殊路径，并用数组dist[]记录每个结点所对应的最短特殊路径的长度

就是用贪心算法，依次找两点之间的最短路径，由于当前顶点到源点已为当前最短路径，借由当前顶点为跳板找到的最短路径亦为当前最短路径。

#### 算法步骤
>1. 数据结构：带权邻接矩阵G.arc[][]；一维数组dist[i]记录源点到结点i的最短路径长度；一位数组p[i]记录最短路径上结点i的前驱
>2. 初始化：源点为u，则对于集合V-S中的所有结点i，dist[i] = G.arc[u][i]；若源点与结点i之间有路径相连，则初始化p[i] = u，否则p[i] = -1
>3. 找最小：在集合V-S中查找令dist[t]最小的结点t，则结点t就是集合V-S中离源点最近的结点，将其加入集合S中，同时更新V-S
>4. 若V-S为空，则算法结束，否则转向5
>5. 找跳板：对于集合V-S中的所有结点j ，都有可能借由j走捷径。若dist[j] > dist[t] + G.arc[t][j]，则令dist[j] = dist[t] + G.arc[t][j]，同时更新结点j的前驱结点为t，即p[j] = t。转向步骤3

#### Floyd算法
##### 基本思想
>在结点i和结点j之间插入结点k，看看是否可以缩短结点i与结点j之间的距离（松弛操作）
##### 算法步骤
>1. 数据结构：带权邻接矩阵G.arc[][]；最短距离数组dist[i][j],记录结点i到j的最短路径长度；前驱数组path[i][j]，记录从结点i到结点j的最短路径上结点j的前驱
>2. 初始化：初始化dist[i][j] = G.arc[i][j]；如果从结点i到结点j有边相连，则初始化path[i][j] = i，否则为1
>3. 松弛：在结点i、j之间插入结点k，看是否可以缩短结点i、j间的距离