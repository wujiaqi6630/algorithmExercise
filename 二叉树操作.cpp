#if WGEBUG
/* 二叉树及其操作:所有递归的时间复杂度是O(N)
 * 1. 创建二叉树：采用前序递归创建二叉树
 * 2. 递归遍历二叉树
 * 3. 前向非递归，中序非递归(再看)
 * 4. 层序遍历，树宽，树高
 * 5. 前序，中序，重构二叉树
 * 6. 下一节点:找出该节点在中序遍历中的下一个节点,提供父指针
 * 7. 二叉树中和为某一值的路径
 * 8. 二叉树镜像：输入一个二叉树，输出他的镜像二叉树，左右子树交换
 * 9. 子树结构：输入两个二叉树，判断B是否为A的子树
 * 10. 给定一个二叉搜索树，转换成排好序的双向链表
 * 11. 平衡二叉树 判断是否为平衡二叉树
 * 12. 二叉树第K个节点
 * 13. 打印二叉树
 * 14. 二叉树的序列化和反序列化
 * 15. 最低公共祖先
 */
/*                             0(5)
 *
 *                1(1)                          2(7)
 *
 *          3(0)        4(3)              7(6)         8(9)
 *
 *                   5(2)  6(4)                     9(8)
 *
 * 层序： 5， 1，7， 0，3，6,9， 2，4，  8
 * 前序： 5，1，0，3，2，4，7，6，9，8
 * 中序： 0，1，2，3，4，5，6，7，8，9
 * 后序： 0，2，4，3，1，6，8，9，7，5
 * 树宽： 4
 * 树高： 4
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>

using namespace std;

#define ElementType int
/********** 树的结构 **********/
struct BinaryTreeNode {
    struct BinaryTreeNode* lc;
    struct BinaryTreeNode* rc;
    struct BinaryTreeNode* par;
    ElementType data;
    BinaryTreeNode() {}
    BinaryTreeNode(ElementType v):data(v), lc(NULL), rc(NULL){}
};
/********** 树的结构 **********/

void display (ElementType e) {
    cout << e << " " ;
}

//1. 前序递归创建树
void createBinaryTree (BinaryTreeNode* &root) {
    char c;
    cin>>c;
    if (c == '#') {
        root = nullptr;
        return;
    }
    else {
        root = new BinaryTreeNode();
        root->data = c;
        createBinaryTree(root->lc);
        createBinaryTree(root->rc);
    }
}
//2. 递归遍历二叉树
void preOrder (BinaryTreeNode* root) {
    if (root == NULL) return ;
    else {
        display(root->data);
        preOrder(root->lc);
        preOrder(root->rc);
    }
}
void midOrder (BinaryTreeNode* root) {
    if (root == NULL) return ;
    else {
        preOrder(root->lc);
        display(root->data);
        preOrder(root->rc);
    }
}
/********** 3. 非递归遍历，5种方法**********/
//前序非递归 ：有右孩子，右孩子进栈；有左孩子，左孩子进栈
//方法一：
void preOrderRoll (BinaryTreeNode* root) {
    stack< pair<BinaryTreeNode*, bool>> st;
    bool visted;
    st.push(make_pair(root,false));
    while (!st.empty()) {
        root = st.top().first;
        visted = st.top().second;
        st.pop();
        
        if (root == NULL) continue;
        if (visted) display(root->data);
        else {
            st.push(make_pair(root->rc,false));
            st.push(make_pair(root->lc,false));
            st.push(make_pair(root,true));
        }
    }
}
/*
 void preOrderRoll(BinaryTreeNode* root) {
 if (root == NULL) return ;
 else {
 stack<BinaryTreeNode*> st;
 st.push(root);
 while (!st.empty()) {
 BinrayTreeNode* tmp = st.top();
 st.pop();
 display(tmp->data);
 if (tmp->rc != NULL) {    //此处必须使用tmp，不能使用root!!!
 st.push(tmp->rc);
 //root = root->rc;
 }
 if (tmp->lc != NULL) {
 st.push(tmp->lc);
 //root = root->lc;
 }
 
 }
 }
 } */

//3.2 中序非递归遍历：当前节点存在就进栈；没有左孩子就出栈。
//方法一：
void midOrderRoll (BinaryTreeNode* root) {
    stack< pair<BinaryTreeNode*, bool>> st;
    bool visted;
    st.push(make_pair(root,false));
    while (!st.empty()) {
        root = st.top().first;
        visted = st.top().second;
        st.pop();
        //display(root->data);
        if (root == NULL) continue;
        if (visted) display(root->data);
        else {
            st.push(make_pair(root->rc,false));
            st.push(make_pair(root,true));
            st.push(make_pair(root->lc,false));
        }
    }
}
/*
 void inOrderRoll (BinaryTreeNode *root) {
 if (root == NULL) return ;
 else {
 stack<BinaryTreeNode*> st;
 while (root != NULL || !st.empty()) {
 if (root != NULL) {
 st.push(root);
 root = root->lc;
 }
 else {
 root = st.top();
 st.pop();
 display(root->data);
 root = root->rc;      //不能直接使用 root = (st.top())->rc;  !!!!
 }
 }
 }
 } */

//后序非递归遍历
void backOrderRoll (BinaryTreeNode* root) {
    stack< pair<BinaryTreeNode*, bool>> st;
    bool visited;
    st.push(make_pair(root,false));
    while (!st.empty()) {
        root = st.top().first;
        visited = st.top().second;
        st.pop();
        if (root == NULL) continue;
        if (visited) display(root->data);
        else {
            st.push(make_pair(root,true));
            st.push(make_pair(root->rc,false));
            st.push(make_pair(root->lc,false));
        }
    }
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ret;
    if (!root) return ret;
    stack<pair<TreeNode*, bool>> st;
    st.push (make_pair(root, false));
    bool visited;
    while (!st.empty()) {
        TreeNode* root = st.top().first;
        visited = st.top().second;
        st.pop();
        
        if (!root) continue;
        if (visited) ret.push_back(root->val);
        else {
            st.push (make_pair(root, true));
            st.push (make_pair(root->right, false));
            st.push (make_pair(root->left, false));
        }
    }
    return ret;
}
/********** 3. 非递归遍历，5种方法**********/

/********** 4. 层序遍历，树宽，树高**********/
void BFS (BinaryTreeNode* root) {
    if (root != NULL) {
        queue<BinaryTreeNode*> qu;
        qu.push(root);
        while (!qu.empty()) {
            root = qu.front();
            qu.pop();
            display(root->data);
            
            if (root->lc) qu.push(root->lc);
            if (root->rc) qu.push(root->rc);
        }
    }
}

//树宽
int getTreeWidth (BinaryTreeNode* root) {
    if (root != NULL) {
        int width = 0;
        queue<BinaryTreeNode*> qu;
        qu.push(root);
        while (!qu.empty()) {
            if (qu.size() > width) width = qu.size();
            for (int i = 0; i < qu.size(); ++i) {
                root = qu.front();
                qu.pop();
                if (root->lc) qu.push(root->lc);
                if (root->rc) qu.push(root->rc);
            }
        }
        return width;
    }
    else
        return 0;
}

int getTreeHeight (BinaryTreeNode* root) {
    if (root == NULL) return 0;
    int left = getTreeHeight (root->lc);
    int right = getTreeHeight (root->rc);
    return left > right ? (left + 1) : (right + 1);
}
/********** 4. 层序遍历，树宽，树高**********/

/********** 5. 前序，中序，重构二叉树 **********/
/* 前序{1,2,4,7,3,5,6,8}，中序{4,7,2,1,5,3,8,6}
 *  前序特点是：第一个元素是跟元素，中序特点是跟元素的左侧是左子树，右侧是右子树
 *  采用递归的方法构建二叉树
 */
BinaryTreeNode* createCore(int pre[], int in[], int ps, int pe, int is, int ie) {
    if (ps > pe || is > ie) return NULL;
    else {
        BinaryTreeNode* node = new BinaryTreeNode();
        int index = is;
        int value = pre[ps];
        while (index <= ie && in[index] != value) index++;
        if (!(index <= ie && in[index] == value)) throw invalid_argument("Invalid Params!");
        node->data = value;
        node->lc = createCore (pre,in,ps+1,ps+index-is,is,index-1);
        node->rc = createCore (pre,in,ps+index-is+1,pe,index+1,ie);
        return node;
    }
}

BinaryTreeNode* createTreeByPreAndInOrder (int pre[], int in[], int plen, int ilen) {
    if (plen != ilen || plen == 0 || ilen == 0)
        throw invalid_argument("invalid arguments");
    return createCore(pre,in,0,plen-1,0,ilen-1);
    
}
/********** 5. 前序，中序，重构二叉树 **********/

/********** 6. 下一节点:找出该节点在中序遍历中的下一个节点,提供父指针 **********/
/* 当前节点cur，如果cur是左孩子：
 *                  如果cur没有右子树，则下一节点是父节点
 *                  如果cur有右子树，则下一节点是右子树的最左下角的子孙节点
 *            如果cur是右孩子，则其下一节点是 沿着父节点向上找，找到第一个祖先节点是左孩子的那个，则下一节点是这个祖先节点的父节点；不存在就是NULL;
 */
BinaryTreeNode* findNextNode (BinaryTreeNode* root, BinaryTreeNode* cur) {
    if (root == NULL) return NULL;
    else {
        //当前节点是跟节点
        if (cur->par == NULL)  {
            BinaryTreeNode* p = cur->rc;
            while (p->lc != NULL) p = p->lc;
            return p;
        }
        //当前节点不是跟节点
        else {
            BinaryTreeNode* par = cur->par;
            //当前节点是左孩子时候
            if (par->lc == cur) {
                //当前节点没有右孩子，下一节点是父节点
                if (cur->rc == NULL) return cur->par;
                //当前节点有右孩子，下一节点是右子树的最左下角那个节点
                else {
                    BinaryTreeNode* p = cur->rc;
                    while (p->lc != NULL) p = p->lc;
                    return p;
                }
            }
            //当前节点是右孩子时候
            else {
                //沿着父节点向上找
                while (par->par != NULL && par->par->lc != par) par = par->par;
                //如果中序中最后一个节点，返回跟节点
                if (par->par == NULL) return root;
                else
                    return par->par;
            }
        }
    }
}
/********** 6. 下一节点:找出该节点在中序遍历中的下一个节点,提供父指针 **********/

/********** 7. 二叉树中和为某一值的路径 **********/
/* 应该选择深度优先搜索遍历将所有可能路径找到，选择哪一种遍历？因为路径都是从跟节点开始的，所以应该选择前序遍历
 * 将前序遍历的访问路线记录在path（vector）中，不过需要注意：
 *      前序递归的本质就是用一个压栈出栈的过程，比如上面的那个树：依次访问4->2->1->0,到0时候没有左右节点，递归（出栈）则会返回到父节点，在返回之前应该将path的m尾部元素去除。
 */
void findPathCore (BinaryTreeNode* root, int tar, vector<int>& path, int sum) {
    //讨论：int arr[] 不需要加引用， vector<int>& vec,已确定。这里sum能不能加引用？！！
    //不加引用，是值传递
    //加引用，是地址传递
    path.push_back(root->data);
    sum += root->data;
    if (root->lc == NULL && root->rc ==NULL && tar == sum) {
        cout << "One of paths is : " << endl;
        for (int i = 0; i < path.size(); ++i)
            cout << path[i] <<" ";
        cout << endl;
    }
    if (root->lc != NULL) findPathCore (root->lc,tar, path, sum);
    if (root->rc != NULL) findPathCore (root->rc,tar, path, sum);
    path.pop_back();
    //sum -= root->data;    //如果加引用的话，在这里需要剪去一次
}

void findPath (BinaryTreeNode* root, int tar) {
    if (root == NULL) return ;
    else {
        vector<int> path;
        int sum = 0;
        findPathCore (root, tar, path, sum);
    }
}


void findAllPathCore (BinaryTreeNode* root, ElemType tar, ElemType sum, vector<vector<ElemType>>& ret, vector<ElemType>& path) {
    if (root == nullptr) return ;
    else {
        bool flag = root->lc == nullptr && root->rc == nullptr;
        path.push_back(root->data);
        sum += root->data;
        
        if (flag) {
            ret.push_back(path);
            if (sum == tar){
                cout << "#######################" << endl;
                for (auto i : path) {
                    cout << i << " ";
                }
                cout << endl;
                cout << "#######################" << endl;
            }
        }
        
        if (root->lc != nullptr) findAllPathCore (root->lc, tar, sum, ret, path);
        if (root->rc != nullptr) findAllPathCore (root->rc, tar, sum, ret, path);
        
        path.pop_back();
        
    }
}

vector<vector<ElemType>> findAllPathInBinaryTree (BinaryTreeNode* root, ElemType tar) {
    vector<vector<ElemType>> ret;
    if (root == nullptr) return ret;
    else {
        vector<ElemType> path;
        findAllPathCore (root, tar, 0, ret, path);
        return ret;
    }
}
/********** 7. 二叉树中和为某一值的路径 **********/

/********** 8.二叉树镜像：输入一个二叉树，输出他的镜像二叉树，左右子树交换********/
void exchangeBinaryTree (BinaryTreeNode* root) {
    if (root == NULL || (root->lc == NULL && root->rc ==NULL)) return ;
    else {
        BinaryTreeNode* tmp = root->lc;
        root->lc = root->rc;
        root->rc = tmp;
        if (root->lc != NULL) exchangeBinaryTree (root->lc);
        if (root->rc != NULL) exchangeBinaryTree (root->rc);
    }
}

//2. 判断是否为对称二叉树,在同一棵树内，左子树的左和右子树的右相同
bool isMirrorTreeCore (BinaryTreeNode* rootA, BinaryTreeNode* rootB) {
    if (rootA == NULL && rootB == NULL) return true;
    if ((rootA == NULL && rootB != NULL) || (rootA != NULL && rootB == NULL)) return false;
    if (rootA != NULL && rootB != NULL && rootA->data != rootB->data) return false;
    return isMirrorTreeCore (rootA->lc, rootB->rc) && isMirrorTreeCore (rootA->rc, rootB->lc);
}

bool isMirrorTree (BinaryTreeNode* root) {
    if (root == NULL) return true;
    return isMirrorTreeCore (root->lc, root->rc);
}


/********** 8.二叉树镜像：输入一个二叉树，输出他的镜像二叉树，左右子树交换********/

/********** 9.子树结构：输入两个二叉树，判断B是否为A的子树 ********/
/* 是一个两次递归过程： 外层递归：遍历A每一个节点：判断cur是否与rootB的跟节点是否相同，不形同直接continue
 * 相同情况下：依次判断A和B左子树，右子树是否相同，还用递归
 */
bool HasSubtreeCore (TreeNode* pRoot1, TreeNode* pRoot2){
    if (!pRoot1 && pRoot2) return false;
    if (!pRoot2) return true;
    if ((pRoot1->val != pRoot2->val)) return false;
    return HasSubtreeCore (pRoot1->left, pRoot2->left) && HasSubtreeCore (pRoot1->right, pRoot2->right);
}

bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
    if (pRoot1 == nullptr || pRoot2 == nullptr) return false;
    /*
     bool res = false;
     if (pRoot1->val == pRoot2->val) res = HasSubtreeCore (pRoot1, pRoot2);
     else {
     if (!res) res = HasSubtree(pRoot1->left, pRoot2);
     if (!res) res = HasSubtree(pRoot1->right, pRoot2);
     } */
    return HasSubtreeCore (pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2)
    || HasSubtree(pRoot1->right, pRoot2);
}
/********** 9.子树结构：输入两个二叉树，判断B是否为A的子树 ********/

/********** 10.给定一个二叉搜索树，转换成排好序的双向链表 ********/
/* 搜索二叉树的中序遍历就是一个有序数组
 * 可以在搜索二叉树的遍历的同时，保存前一个访问的节点，建立当前节点与前个节点的指向关系
 */
void convert (BinaryTreeNode* root, BinaryTreeNode* &pre) {
    /* 关于是否使用 引用  ？？？？？？
     * root是指向二叉树的根节点，用来代表整个二叉树，二叉树结构改动了，返回跟节点，就是改动后的二叉树
     * 数值依据是否需要改动，确定是否需要使用引用
     * pre是一个指向节点的指针，本身就是指针，要想改动它，需要使用引用！！！！！！
     */
    if (root == NULL) return ;
    
    if (root->lc != NULL) convert (root->lc, pre);
    
    BinaryTreeNode* cur = root;
    cur->lc = pre;
    if (pre != NULL) pre->rc = cur;
    pre = cur;
    
    if (root->rc != NULL) convert (root->rc, pre);
}

BinaryTreeNode* binaryTreeToDoubleList (BinaryTreeNode* root) {
    if (root == NULL) return NULL;
    BinaryTreeNode* pre = NULL;
    convert (root, pre);
    //转换之后，得到的是二叉树的最后一个节点，应该返回首节点
    while (pre != NULL && pre->lc != NULL)
        pre = pre->lc;
    return pre;
}
/********** 10.给定一个二叉搜索树，转换成排好序的双向链表 ********/

/********** 11.平衡二叉树 判断是否为平衡二叉树 ********/
//注意！应该对每个节点都进行判断！！
int getHeight (BinaryTreeNode* root) {
    if (root == NULL) return 0;
    int left = getHeight(root->lc);
    int right = getHeight(root->rc);
    return left > right ? (left + 1) : (right + 1);
}

bool isBalenceTree (BinaryTreeNode* root) {
    if (root == NULL) return true;
    else {
        int diff = getHeight(root->lc) - getHeight(root->rc);
        if (diff > 1 || diff < -1)
            return false;
        return isBalenceTree (root->lc) && isBalenceTree (root->rc);
    }
}
/********** 11.平衡二叉树 ********/

/********** 12.二叉搜索树，请找出其中的第k小的结点 ********/
void findKtopNodeCore (BinaryTreeNode* root, int k, int &i, BinaryTreeNode* &node) {
    if (root == NULL) return ;
    findKtopNodeCore (root->lc, k, i, node);
    i++;
    if (i == k)  {
        node = root;
        return;
    }
    findKtopNodeCore (root->rc, k, i, node);
}

BinaryTreeNode* findKtopNode (BinaryTreeNode* root, int k) {
    if (root == NULL || k < 1) return NULL;
    else {
        int index = 0;
        BinaryTreeNode* node = NULL;
        findKtopNodeCore (root,k,index,node);
        return node;
        
    }
}
//方法二：
int count2 = 0;
BinaryTreeNode* findKtopNode2 (BinaryTreeNode* root, int k) {
    if (root == NULL || k < 1) return NULL;
    else {
        
        BinaryTreeNode* ret = NULL;
        if ((ret = findKtopNode2 (root->lc, k)) != NULL)
            return ret;
        count2++;
        if (count2 == k) return root;
        if ((ret = findKtopNode2 (root->rc, k)) != NULL)
            return ret;
        return ret;
        
    }
}
/********** 12.二叉树第K个节点 ********/

/********** 13.打印二叉树 ********/
//1.从上往下打印二叉树，每一行从左到右打印
void printBinaryTree1 (BinaryTreeNode* root) {
    if (root == NULL) return;
    else {
        queue<BinaryTreeNode*> qu;
        qu.push(root);
        cout << "PRINT : " << endl;
        while (!qu.empty()) {
            //int size = qu.size();
            //for (int i = 0; i < size; ++i) {
            root = qu.front();
            qu.pop();
            cout << root->data << " ";
            
            if (root->lc != NULL) qu.push(root->lc);
            if (root->rc != NULL) qu.push(root->rc);
            //}
        }
        cout << endl;
    }
}
//2. 之字形打印二叉树
void printBinaryTree2 (BinaryTreeNode* root) {
    if (root == NULL) return;
    else {
        queue<BinaryTreeNode*> qu;
        stack<BinaryTreeNode*> st;
        qu.push(root);
        int rows = 0;
        cout << "PRINT : " << endl;
        while (!qu.empty()) {
            rows++;
            int size = qu.size();
            for (int i = 0; i < size; ++i) {
                root = qu.front();
                qu.pop();
                if (rows % 2 == 1)
                    cout << root->data << " ";
                else
                    st.push(root);
                
                if (root->lc != NULL) qu.push(root->lc);
                if (root->rc != NULL) qu.push(root->rc);
            }
            while (!st.empty()) {
                cout << (st.top())->data << " ";
                st.pop();
            }
        }
        cout << endl;
    }
}
/********** 13.打印二叉树 ********/

/********** 二叉搜索树的后序遍历 ********/
/* 分析：
 * 后序+二叉搜索树，特点是最后一个是跟节点，从前往后数，m个节点是左子树，后面是又子树
 */
bool VerifySquenceOfBSTCore (vector<int>sequence, int start, int end){
    if (end <= start) return true;
    int root = sequence[end];
    int le = start, i = start;
    
    while (i <= end && sequence[i] < root) ++i;
    le = i-1;
    while (i <= end && sequence[i] > root) ++i;
    if (i != end) return false;
    
    return VerifySquenceOfBSTCore (sequence, start, le) && VerifySquenceOfBSTCore (sequence, le+1, end-1);
}


bool VerifySquenceOfBST(vector<int> sequence) {
    int len = int (sequence.size());
    if (len == 0) return false;
    return VerifySquenceOfBSTCore (sequence, 0, len-1);
    
}
/********** 二叉搜索树的后序遍历 ********/


/********** 14.二叉树的序列化和反序列化 ********/
/*
 对于序列化：使用前序遍历，递归的将二叉树的值转化为字符，并且在每次二叉树的结点不为空时，在转化val所得的字符
 之后添加一个','作为分割。对于空节点以'#'代替。
 对于反序列化：按照前序顺序，递归的使用字符串中的字符创建一个二叉树（特别注意：在递归时，递归函数的参数一定要
 是char**，这样才能保证每次递归后指向字符串的指针会随着递归的进行而移动）。
 */
/********** 14.二叉树的序列化和反序列化 ********/

/********** 15.最低公共祖先 ********/
//搜索二叉树的情况下：从根节点开始，遍历整棵树，如果遇到某个节点的值比左孩子大，比右孩子小，则找到
BinaryTreeNode* ret = NULL;
BinaryTreeNode* findPar1 (BinaryTreeNode* root, BinaryTreeNode* roota, BinaryTreeNode* rootb) {
    if (root == NULL || roota == NULL || rootb == NULL) return NULL;
    else {
        if (root->data > roota->data && root->data < rootb->data)
            ret =  root;
        if (root->lc != NULL) findPar1(root->lc, roota, rootb);
        if (root->rc != NULL) findPar1(root->rc, roota, rootb);
    }
    return ret;
}

//普通二叉树的情况下：需要保存从根节点到两个节点的路径，然后对路径进行从头遍历
BinaryTreeNode* searchPar (vector<BinaryTreeNode*> veca, vector<BinaryTreeNode*> vecb) {
    int size_a = veca.size();
    int size_b = veca.size();
    BinaryTreeNode* ret1;
    ret1 = size_a > size_b ? (vecb[size_b-1]) : (veca[size_a-1]);
    if (veca[0]->data != vecb[0]->data) {
        throw invalid_argument ("INVLID");
    }
    for (int i = 1; i < size_a, i < size_b; i++) {
        if (veca[i]->data != vecb[i]->data)
            ret1 = veca[i-1];
    }
    return ret1;
}

void findPath1 (BinaryTreeNode* root, BinaryTreeNode* tar, vector<BinaryTreeNode*> &path,
                bool& flag) {
    if (root == NULL) return;
    if (flag) {
        path.push_back(root);
        if (root->data == tar->data) flag = false;
    }
    if (root->lc) findPath1 (root->lc, tar, path, flag);
    if (root->rc) findPath1 (root->rc, tar, path, flag);
    if (flag) path.pop_back();
}

BinaryTreeNode* findPar2 (BinaryTreeNode* root, BinaryTreeNode* roota, BinaryTreeNode* rootb) {
    if (root == NULL || roota == NULL || rootb == NULL) return NULL;
    else {
        vector<BinaryTreeNode*> veca;
        vector<BinaryTreeNode*> vecb;
        bool flag = true;
        findPath1 (root, roota, veca, flag);
        flag = true;           //很重要！！！！
        findPath1 (root, rootb, vecb, flag);
        return searchPar (veca,vecb);
    }
}

/********** 15.最低公共祖先 ********/


/********** 主函数 **********//*
int main()
{
    //BinaryTreeNode* root = NULL;
    //createBinaryTree(root);
    //cout<<endl;
    //cout<<"lc : "<<root->lc->data<<endl;
    
    BinaryTreeNode root[10];
    root[0].data = 5;
    root[0].lc = &root[1];
    root[0].rc = &root[2];
    root[0].par = NULL;
    
    root[1].data = 1;
    root[1].lc = &root[3];
    root[1].rc = &root[4];
    root[1].par = &root[0];
    
    root[2].data = 7;
    root[2].lc = &root[7];
    root[2].rc = &root[8];
    root[2].par = &root[0];
    
    root[3].data = 0;
    root[3].lc = NULL;
    root[3].rc = NULL;
    root[3].par = &root[1];
    
    root[4].data = 3;
    root[4].lc = &root[5];
    root[4].rc = &root[6];
    root[4].par = &root[1];
    
    root[5].data = 2;
    root[5].lc = NULL;
    root[5].rc = NULL;
    root[5].par = &root[4];
    
    root[6].data = 4;
    root[6].lc = NULL;
    root[6].rc = NULL;
    root[6].par = &root[4];
    
    root[7].data = 6;
    root[7].lc = NULL;
    root[7].rc = NULL;
    root[7].par = &root[2];
    
    root[8].data = 9;
    root[8].lc = &root[9];
    root[8].rc = NULL;
    root[8].par = &root[2];
    
    root[9].data = 8;
    root[9].lc = NULL;
    root[9].rc = NULL;
    root[9].par = &root[8];
    
    //preOrder(&root[0]);
    //preOrderRoll(&root[0]);
    //midOrderRoll(&root[0]);
    //midOrderRoll(&root[0]);
    //backOrderRoll(&root[0]);
    //BFS(&root[0]);
    //cout << getTreeWidth(&root[0]) << endl;
    //cout << getTreeHeight (&root[2]) << endl;
    
    
     //int pre[] = {1,2,4,7,3,5,6,8};
     //int in[] = {4,7,2,1,5,3,8,6};
     //int plen = sizeof(pre)/sizeof(int);
     //int ilen = sizeof(in)/sizeof(int);
     //BinaryTreeNode* root1 =  createTreeByPreAndInOrder(pre, in, plen, ilen);
     //cout << "root->left->data: " << root1->lc->data << endl;
     
    
    //BinaryTreeNode* next =  findNextNode (&root[0],&root[5]);
    //cout << next->data;
    
    //findPath(&root[0],9);
    
    //exchangeBinaryTree(&root[0]);
    //cout << root->rc->lc->data<<endl;

     BinaryTreeNode root2[3];
     root2[0].data = 2;
     root2[0].lc = &root2[1];
     root2[0].rc = &root2[2];
     
     root2[1].data = 1;
     root2[1].lc = NULL;
     root2[1].rc = NULL;
     
     root2[2].data = 1;
     root2[2].lc = NULL;
     root2[2].rc = NULL;
     
     //if (isChildTree(&root[0], &root2[0])) cout << "exist !" <<endl;
     //else cout << "NO !" <<endl;
     
     //if (isMirrorTree(&root[0])) cout << "YES !" <<endl;
     //else cout << "NO !" <<endl;
    
    //BinaryTreeNode* root3 = binaryTreeToDoubleList(&root[0]);
    //cout << root3->rc->rc->data<<endl;
    
    //if (isBalenceTree (&root[0]))
    //    cout << "YES!" << endl;
    //else
    //    cout << "NO!"<<endl;
    
    //cout << findKtopNode2 (&root[0], 3)->data << endl;
    
    //printBinaryTree1 (&root[0]);
    //printBinaryTree2 (&root[0]);
    
    cout << (findPar2 (&root[0], &root[3], &root[5]))->data << endl;
    cout << endl;
    return 0;
}
*//********** 主函数 **********/
#endif
