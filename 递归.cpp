#define WDEBUG 0
#if WDEBUG

/* 递归
 * 1. 交换左右子树
 * 2. 汉诺塔
 */

#include <iostream>
using namespace std;

/**************** 1. 交换左右子树 ****************/
struct BinaryTreeNode {
    struct BinaryTreeNode* lc;
    struct BinaryTreeNode* rc;
    int data;
};

void exchange1 (BinaryTreeNode* root) {
    if (root == NULL || (root->lc == NULL && root->rc == NULL)) return ;
    BinaryTreeNode* tmp = root->lc;
    root->lc = root->rc;
    root->rc = tmp;
    if (root->lc != NULL) exchange1 (root->lc);
    if (root->rc != NULL) exchange1 (root->rc);
}
/**************** 1. 交换左右子树 ****************/

/**************** 2. 汉诺塔 ****************/
/* 第一次移动，要把A柱子上的前n-1个移动到B柱子上；
 * 第二次移动，直接把A柱子上的最后一个移动到C柱子上；
 * 第三次移动，把B柱子上的n-1个柱子通过柱子A移动到柱子C上。
 */
//将n个盘子从A可以借助B移到C
void moveDisk (int n, char a, char b, char c) {
    if (n == 0) return ;
    else if (n == 1)
        cout << "Move " << n << "-th disk from " << a << " to " << c << endl;
    else {
        //把上面的n-1个盘子从a盘借助c盘移动到b盘
        moveDisk (n-1, a, c, b);
        cout << "Move " << n << "-th disk from " << a << " to " << c << endl;
        //把上面的n-1个盘子从b盘借助a盘移动到c盘
        moveDisk (n-1, b, a, c);
        
    }
}
/**************** 2. 汉诺塔 ****************/
#endif
