#if WDEBUG
/* 动态规划.cpp
 * 1. 讲解
 * 1.1 动态规划 vs 递归 （斐波那契数列）
 * 递归中you hyou hen du有很多重复计算；但是递归中没有对空间进行了增加，始终都是同样的长度，仅仅是不断的弹出和压入
 * 斐波那契使用递归实现：时间复杂度： 2^n  空间复杂度：O(n)
 * 斐波那契数列使用动态规划实现：可以避免重复计算，从O(2^N)指数级变为O(N)常数级别
 * 动态规划：不直接去解决问题，而是在每一步解决问题过程中，利用过去的状态以及当前状态的关系而达到一个当前的最优状态.
 * 规划：解决该类问题的时候，会有一个“填表格”的过程，一维表格、二维表格，以开辟空间换时间的思想，以争取最佳的时间效率. （保存过程中间值，方便后续直接使用）.
 * 动态：递归解决过程中的每一步都会从基本问题不断的“自顶向下”去求解，在每一步骤中，会有相同的计算逻辑进行了重复的计算。相比于递归思想，动态规划思想增加了对历史上计算结果的保存，逐步记录下中间的计算结果，在每一步求得最优值.
 * 1.2 解题步骤：（1）定义dp数组含义；（2）定义状态转移方程；（3）初始化；（4）优化
 * 定义dp数组含义：一维？二维？都是用来保存截止到目前的最优值
 */

/* 1. 斐波那契 及其改进
 * 2. 打家劫舍一，房屋是链表
 * 3. 机器人从左上角到右下角，求路径数
 * 4. 机器人从左上角到右下角，中间有障碍，求路径数
 * 5. 打家劫舍问题二，房屋成环
 * 6. 打家劫舍问题三，房屋成二叉树
 * 7. 乘积最大子数组
 * 8. 按摩师
 * 9. 背包问题
 * 10. 最长连续上升子序列
 * 11. 最长上升子序列
 * 12. 有几个最长上升子序列
 * 13. 最长连续序列长度，要求O(n)
 * 14. 最长公共子串（子序列）
 * 15. 单词转换最少次数
 * 16. 数字编码
 * 17. 不同的二叉搜索树
 * 18. 三角形最短路径和
 * 19. 买卖股票，一天最多交易一次
 * 20. 单词拆分
 * 21. 零钱兑换
 * 22. 4键键盘
 * 16. 拦截导弹
 * 17. 合唱队形
 * 18. 放苹果
 * 19. 最大子矩阵问题
 * 27. 连续数组最大和
 */


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <exception>
#include <unordered_set>
#include <memory.h>
using namespace std;

/********** 1. 斐波那契 及其改进 **********/
//1.1 递归实现
long long febnaci1 (unsigned n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return febnaci1(n-1) + febnaci1(n-2);
}
//1.2 DP实现
long long febnaci2 (unsigned n) {
    long long *dp = new long long[n+1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
//1.3 DP实现
long long febnaci3 (unsigned n) {
    long long a = 0, b = 1, c = 0;
    if (n == 0) return a;
    if (n == 1) return b;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}
/********** 1. 斐波那契 及其改进 **********/

/********** 2. 打家劫舍问题一 **********/
//题目：偷窃沿街的房屋，每间房都有钱，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//给定一个代表每个房屋存放金额的非负整数数组，计算你在不触动警报装置的情况下，能够偷窃到的最高金额。
/* 分析：dp[i]表示偷到第i家时最多获得dp[i],到达当前房间获取的dp[i]有两种来源：
 * （当前房间偷）：dp[i] = nums[i]+dp[i-2];
 * （当前房间不偷）：dp[i] = dp[i-1];
 * dp[i] = max {dp[i-1], (dp[i-2]+nums[i])};
 */
int row1 (const vector<int>& vec) {
    int len = (int)vec.size();
    if (len == 0) return 0;
    else if (len == 1) return vec[0];
    else {
        int* dp = new int[len];
        dp[0] = vec[0];
        dp[1] = max (vec[0],vec[1]);
        for (int i = 2; i < len; ++i)
            dp[i] = max (dp[i-1],(dp[i-2]+vec[i]));
        int res = dp[len-1];
        delete[] dp;
        return res;
    }
}
//优化：不需要用数组，使用两个变量就可以
int row2 (const vector<int>& vec) {
    int len = (int)vec.size();
    if (len == 0) return 0;
    else if (len == 1) return vec[0];
    else {
        int dp0 = vec[0];
        int dp1 = max (vec[0],vec[1]);
        int dp2 = dp1;
        for (int i = 2; i < len; ++i) {
            dp2 = max ((vec[i]+dp0),dp1);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp2;
    }
}
//时间复杂度：O(n), 空间复杂度O(1)
/********** 2. 打家劫舍问题一 **********/

/********** 3. 机器人 **********/
//题目：机器人位于一个 m x n 网格的左上角，每次只能向下或者向右移动一步，达到网格的右下角。问总共有多少条不同的路径？
//分析：dp[i][j]表示机器人从开始到达（i,j）位置一共有dp[i][j]种路径
//dp[i][j]=dp[i-1][j]+dp[i][j+1];
//初始条件：dp[0][]=dp[][0]=1;
//！！！！！！定义二维数组的方法！！！！！
/* 方法一：静态数组： int a[2][3] = {1,2,2,3,4,5};
 * 方法二：动态数组：
 * int** a = new int*[m];
 * for (int i = 0; i < m; ++i)
 *      a[i] = new int[n];
 * for (int i = 0; i < m; ++i)
 *      delete[] a[i];
 * delete[] a;
 * 方法三：vector:
 * vector<vector<int> > a = (m, vector<int>(n));
 */
//注意：！！使用二维数组的时候，不应该在二维表多设置一个0
int getPath1 (int m, int n) {
    if (m == 0 || m == 0) return 0;
    else {
        //方法一：
        //vector<vector<int> > dp(m, vector<int>(n));
        // for(for) 初始化
        //方法二：
        // vector<int> tmp(n, 1);
        //vector<vector<int> > dp(m, tmp);
        //方法三：
        int** dp = new int*[m];
        for (int i = 0; i < m; ++i)
            dp[i] = new int[n];
        for (int i = 0; i < m; ++i) dp[i][0] = 1;
        for (int i = 1; i < n; ++i) dp[0][i] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
        int ret = dp[m-1][n-1];
        for (int i = 0; i < m; ++i)
            delete[] dp[i];
        delete[] dp;
        return ret;
    }
}
//时间复杂度：O(m*n), 空间复杂度O(m*n)
//优化：还是空间优化：其实不用保存那么多，对于当前（i，j），只用保存第i行的前j-1个和第i-1行的j到最后即可。
int getPath2 (int m, int n) {
    int* dp = new int[n];
    for (int i = 0; i < n; ++i) dp[i] = 1;
    
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j-1] + dp[j];
        }
    }
    int ret = dp[n-1];
    delete[] dp;
    return ret;
}
//时间复杂度：O(m*n), 空间复杂度O(min(m,n))
/********** 3. 机器人 **********/

/********** 4. 机器人从左上角到右下角，中间有障碍，求路径数 **********/
//题目描述：和上一题类似，只不过在路上有障碍，用1表示，无障碍用0表示
/* dp[i][j]仍然表示从坐上角到(i,j)位置的路径数
 * dp[i][j] = obstacleGrid[i][j] * {dp[i-1][j]*obstacleGrid[i-1][j] + dp[i][j-1]*obstacleGrid[i][j-1]}
 */
int getPath3 (vector<vector<int>> obstacleGrid) {
    int m = (int)obstacleGrid.size();
    if (m == 0) return 0;
    else {
        int n = (int)obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1) return 0;
        vector<vector<int> > dp(m, vector<int>(n));
        dp[0][0] = 1;
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) {
                for (int k = i; k < m; ++k)
                    dp[k][0] = 0;
                break;
            }
            else dp[i][0] = 1;
        }
        for (int i = 1; i < n; ++i) {
            if (obstacleGrid[0][i] == 1) {
                for (int k = i; k < m; ++k)
                    dp[0][k] = 0;
                break;
            }
            else dp[0][i] = 1;
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n;++j) {
                dp[i][j] = (1-obstacleGrid[i][j]) * (dp[i-1][j] + dp[i][j-1]);
            }
        }
        int ret = dp[m-1][n-1];
        return ret;
    }
}
//这个方法：时间复杂度为O(m*n),空间复杂度为O(m*n)
//优化，压根没必要开辟新空间，直接在原空间赋值
int getPath4 (vector<vector<int> > vec) {
    int m = (int)vec.size();
    if (m == 0) return 0;
    else {
        int n = (int)vec[0].size();
        if (vec[0][0] == 1) return 0;
        //初始化第0列
        else {
            vec[0][0] = 1;
            for (int i = 1; i < m; ++i) {
                if (vec[i][0] == 1) {
                    for (int k = i; k < m; ++k)
                        vec[k][0] = 0;
                    break;
                }
                else vec[i][0] = 1;
            }
            for (int i = 1; i < n; ++i) {
                if (vec[0][i] == 1) {
                    for (int k = i; k < n; ++k)
                        vec[0][k] = 0;
                    break;
                }
                else vec[0][i] = 1;
            }
            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    vec[i][j] = (1-vec[i][j]) * (vec[i-1][j] + vec[i][j-1]);
                }
            }
            int ret = vec[m-1][n-1];
            return ret;
        }
    }
}
//这个方法：时间复杂度为O(m*n),空间复杂度为O(1)
/********** 4. 机器人从左上角到右下角，中间有障碍，求路径数 **********/

/********** 5. 打家劫舍问题二，房屋成环 **********/
/* 在环的条件下：假设偷第0家，最大金额为dp1；偷第0家为dp2；则dp = max{dp1,dp2}
 */
int robCore (vector<int>& nums, int start, int end) {
    int len = end-start+1;
    if (len <= 1) return nums[start];
    else {
        int dp0 = nums[start];
        int dp1 = max(nums[start+1],nums[start]);
        int dp2 = dp1;
        for (int i = start+2; i <= end; ++i) {
            dp2 = max ((dp0+nums[i]),dp1);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp2;
    }
}
int rob3(vector<int>& nums) {
    int len = nums.size();
    if (len == 0) return 0;
    else if (len == 1) return nums[0];
    else {
        int ret1 = robCore (nums,0,len-2);
        int ret2 = robCore (nums,1,len-1);
        return max(ret1,ret2);
    }
}
//时间复杂度：O（n）,空间：O(1)
/********** 5. 打家劫舍问题二，房屋成环 **********/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode () {}
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/********** 6. 打家劫舍问题三，房屋成二叉树 **********/
/* 很悲伤，层序遍历是不可以的
 int getHeight (TreeNode* root) {
 if (root == NULL) return 0;
 else {
 int l = getHeight(root->left);
 int r = getHeight(root->right);
 return (l > r ? (l+1) : (r+1));
 }
 }
 
 vector<int> getWidth (TreeNode* root) {
 if (root == NULL) return {};
 else {
 queue<TreeNode*> qu;
 qu.push(root);
 int width = 1, sum = 0, count = 0;
 vector<int> vec;
 while (!qu.empty()) {
 count = 0; sum = 0;
 for (int i = 0; i < width; ++i) {
 root = qu.front();
 sum += root->val;
 qu.pop();
 if (root->left != NULL) {qu.push(root->left); count++;}
 if (root->right != NULL) {qu.push(root->right);count++;}
 }
 width = count;
 vec.push_back(sum);
 }
 return vec;
 }
 }
 
 int rob(TreeNode* root) {
 int height = getHeight(root);
 if (height == 0) return 0;
 else if (height == 1) return root->val;
 else {
 vector<int> vec = getWidth(root);
 int dp0 = vec[0];
 int dp1 = max(vec[0],vec[1]);
 int dp2 = dp1;
 for (int i = 2; i < height; ++i) {
 dp2 = max((vec[i]+dp0), dp1);
 dp0 = dp1;
 dp1 = dp2;
 }
 return dp2;
 }
 }
 */
/* 分析：逻辑是子节点信息陆续汇报给父节点，最后在跟节点汇报总值，采用后续遍历
 * 把当前节点作为根节点，对于这个节点有两种状态：偷或者不偷
 * 当前节点偷时： 两个子节点都不能偷
 * 当前节点不偷时： 两个字节点分别选出最大值，进行相加
 * 最难是如何进行表示？「偷」和「不偷」，把这一点设计成状态，放在第 2 维，这一步叫「消除后效性」，这一点技巧非常常见。
 * 比如：以当前节点作为根节点，最大值max = max(dp[0],dp[1]),其中dp[0]是偷当前节点；
 */
int* backDFS (TreeNode* root) {
    //此处不能直接返回 {0,0}!!!!!!!!!!!
    if (root == NULL) {
        int tmp[2] = {0,0};
        return tmp;
        
    }
    else {
        int* lc = backDFS (root->left);
        int* rc = backDFS (root->right);
        //此处不能使用int* dp  !!!!!!!!
        int dp[2];
        dp[0] = max(lc[0],lc[1]) + max(rc[0],rc[1]);
        dp[1] = root->val + lc[0] + rc[0];
        return dp;
    }
}

int rob (TreeNode* root) {
    if (root == NULL) return 0;
    else {
        int* dp = backDFS(root);
        return max(dp[0], dp[1]);
    }
}
/********** 6. 打家劫舍问题三，房屋成二叉树 **********/

/********** 7. 乘积最大子数组 **********/
//题目：一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积
/* 分析：无后效性：「动态规划」通常不关心过程，只关心「阶段结果」，这个「阶段结果」就是我们设计的「状态」。「回溯算法」需要记录过程，复杂度通常较高。
 * 分析：如果所有数据都是>=0，就可以单纯的使用dp[i]=max{dp[i-1]*num[i],num[i]}表示；
 但是引入了负数，就变得更复杂，引入状态设计：就像上一题当前节点偷或不偷分别使用dp[0]dp[1]表示。这道题的状态设计：对于当前节点：dp[0]表示最小值，dp[1]表示最大值，用此方法解决大部分的子序列的问题。
 * 子序列的最大特点就是当前节点必须选择
 * num[i]>=0: dp[i][0] = min {num[i], dp[i-1][0]*num[i]}
 dp[i][1] = max {num[i], dp[i-1][1]*num[i]}
 num[i]<0: dp[i][0] = min {num[i], dp[i-1][1]*num[i]}
 dp[i][1] = max {num[i], dp[i-1][0]*num[i]}
 * 初始值： dp[i][0] = dp[i][1]= num[0]
 */
int getMax1 (vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    //else if (len == 1) return nums[0];
    else {
        vector<vector<int> > dp(len,vector<int>(2));
        dp[0][0] = nums[0]; dp[0][1] = nums[0];
        for (int i = 1; i < len; ++i) {
            if (nums[i] >= 0) {
                dp[i][0] = min (nums[i], nums[i] * dp[i-1][0]);
                dp[i][1] = max (nums[i], nums[i] * dp[i-1][1]);
            }
            else {
                dp[i][0] = min (nums[i], nums[i] * dp[i-1][1]);
                dp[i][1] = max (nums[i], nums[i] * dp[i-1][0]);
            }
        }
        int ret = dp[0][1];
        for (int i = 1; i < len; ++i) {
            if (dp[i][1] > ret) ret = dp[i][1];
        }
        return ret;
    }
}
//时间复杂度是O(2n),空间复杂度为O(2n)
//优化:
int getMax2(vector<int> nums) {
    int len = (int) nums.size();
    if (len == 0) return 0;
    else {
        int dp00 = nums[0], dp01 = nums[0];
        int dp10 = dp00, dp11 = dp01;
        int maxNum = dp01;
        for (int i = 1; i < len; ++i) {
            if (nums[i] >= 0) {
                dp10 = min(nums[i], nums[i] * dp00);
                dp11 = max(nums[i], nums[i] * dp01);
                dp01 = dp11; dp00 = dp10;
                maxNum = max(maxNum, dp11);
            }
            else {
                dp10 = min(nums[i], nums[i] * dp01);
                dp11 = max(nums[i], nums[i] * dp00);
                dp01 = dp11; dp00 = dp10;
                maxNum = max (maxNum, dp11);
            }
        }
        return maxNum;
    }
}
//时间复杂度是O(n),空间复杂度为O(1)
/********** 7. 乘积最大子数组 **********/

/********** 8. 按摩师 **********/
//题目：一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。
//分析：和打家劫舍一样的。。。。
//设dp[i]表示在序列i位置，获取的最长时间，则状态转换方程为：
// dp[i] = max {dp[i-1], num[i]+dp[i-2]}
// 初始值： dp[0] = num[0]; dp[1] = max {num[0], num[1]}
int mssage (vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else if (len == 1) return nums[0];
    else {
        int dp0 = nums[0], dp1 = max (nums[0], nums[1]);
        int dp2 = dp1;
        
        for (int i = 2; i < len; ++i) {
            dp2 = max (dp1, nums[i]+dp0);
            dp0 = dp1;
            dp1 = dp2;
        }
        return dp2;
    }
}
//时间复杂度 O（n）,空间复杂度：O（1）
/********** 8. 按摩师 **********/

/********** 9. 0/1背包问题 **********/
//题目：一共有N件物品，每一种物品只有一件，第i（i从1开始）件物品的重量为w[i]，价值为v[i]。在总重量不超过背包承载上限W的情况下，能够装入背包的最大价值是多少？
/* n : 一共有n个物品；
 * m : 背包上限是m；
 * weight ：n个物品重量的序列；
 * value ： n个物品的价值序列。
 * ret : 背包最多装的价值
 * dp[i][j] 表示当前背包容量还剩下j时，从0～i件可获得的最大值
 * weight[i] < j:  dp[i][j] = max (dp[i-1][j], dp[i][j-weight[i]]+value[i]);
 * weight[i] > j : dp[i][j] = dp[i-1][j]
 */
/* 输入： 4，5 表示4件物品，背包容量为5
 * weight:{1,2,3,4}
 * value:{2,4,4,5}  m=5, n=4
 * 输出： 8
 */
int package (vector<int> weight, vector<int> value, int m, int n) {
    //dp[i][j]表示的是在背包容量剩余j的情况下，从0～i物品中选取可获得的最大值
    //return dp[n][m]
    if (n == 0) return 0;
    else {
        vector<vector<int> > dp(n+1, vector<int>(m+1));
        //memset 不能使用于vector
        for (int i = 0; i <= n; ++i) dp[i][0] = 0;
        for (int j = 0; j <= m; ++j) dp[0][j] = 0;
        
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (weight[i] > j) dp[i][j] = dp[i-1][j];
                else dp[i][j] = max (dp[i-1][j], value[i]+dp[i-1][j-weight[i]]);
            }
        }
        return dp[n][m];
    }
}
//时间复杂度为O(mn),空间复杂度为O（mn）
//优化：

int package1 (vector<int> weight, vector<int> value, int m, int n) {
    //dp[j]表示的是在背包容量剩余j的情况下可获得的最大值
    //return dp[m]
    if (n == 0) return 0;
    else {
        vector<int> dp(n+1, 0);
        //memset 不能使用于vector
        //for (int j = 0; j <= m; ++j) dp[j] = 0;
        
        
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= weight[i]; --j) {
                dp[j] = max (dp[j], value[i]+dp[j-weight[i]]);
            }
        }
        return dp[m];
    }
}
//时间复杂度：O(mn) 空间复杂度O(m)*/
//9.2 完全背包问题：一共有N种物品，每一种物品不限个数，第i（i从1开始）件物品的重量为w[i]，价值为v[i]。在总重量不超过背包承载上限W的情况下，能够装入背包的最大价值是多少？
int package2 (vector<int> weight, vector<int> value, int m, int n) {
    
    vector<int> dp(m+1,0);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = weight[i]; j <= m; ++j)
            dp[j] = max (dp[j], dp[j-weight[i]] + value[i]);
    }
    
    return dp[m];
}
/********** 9. 0/1背包问题 **********/

/********** 10. 最长连续上升子序列 **********/
/* 题目： 输入: [1，3，5，4，7] 输出: 3
 * 解释: 必须连续
 */
//dp[i]表示0~i最长为dp[i]; nums[i]>nums[i-1]: dp[i] = dp[i-1]+1
/********** 10. 最长连续上升子序列 **********/
int longestSeq (vector<int> nums) {
    int len = (int)(nums.size());
    if (len == 0) return 0;
    else {
        vector<int> dp(len,1);
        int maxV = 1;
        for (int i = 1; i < len; ++i) {
            if (nums[i] > nums[i-1])
                dp[i] = dp[i-1] + 1;
            maxV = max (maxV, dp[i]);
        }
        return maxV;
    }
}
//优化：
int longestSeq1 (vector<int> nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else {
        int dp0 = 1, dp1 = 1, maxNum = 1;
        for (int i = 1; i < len; ++i){
            if (nums[i] > nums[i-1]) {
                dp1 = dp0+1;
                dp0 = dp1;
            }
            else {
                dp0 = 1;  //!!!!!很重要，容易漏掉
                dp1 = 1;
            }
            
            maxNum = max (dp1, maxNum);
        }
        return maxNum;
    }
}
/********** 11. 最长上升子序列 **********/
/* 题目： 输入: [10,9,2,5,3,7,101,18] 输出: 4
 * 解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
 */
//dp[i]表示从0～i的最长上升子序列， dp[i]=max(dp[i],dp[j]+1);
int lengthOfLIS(vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else {
        vector<int> dp(len);
        int maxV = 1;
        for (int i = 0; i < len; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j])
                    dp[i]= max (dp[i], dp[j]+1);
            }
            maxV = max (maxV, dp[i]);
        }
        return maxV;
    }
}
//时间复杂度O(n^2),空间复杂度O(n)
//优化：
/* 最长上升子序列的实质是：让子序列上升的最慢的那个：将上升子序列存储在increse[]中，长度len
 * 对于nums[i]，nums[i] > increase[len-1],则直接加入，len++
 * 否则，更新这个上升的队列，使用二分查找
 */
//贪心+二分查找并更新
void binarySearch(vector<int>& incrase,int res,int tar) {
    int l = 0, r = res;
    while (l <= r) {
        int m = l + (r-l)/2;
        if (incrase[m] == tar) {l = m;break;}
        else if (incrase[m] < tar) {
            l = m+1;
        }
        else r = m-1;
    }
    incrase[l] = tar;
}

int lengthOfLIS1(vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else {
        vector<int> incrase(len+1,0);
        int res = 0;
        incrase[res++] = nums[0];
        for (int i = 1; i < len; ++i) {
            if (nums[i] > incrase[res-1])
                incrase[res++] = nums[i];
            else
                binarySearch (incrase,res,nums[i]);
        }
        return res;
    }
}
//时间复杂度分析：O(nlogn), 空间复杂度O(n)
/********** 11. 最长上升子序列 **********/

/********** 12. 有几个最长上升子序列 **********/
/* 输入: [1,3,5,4,7] 输出: 2
 * 解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
 */
int findNumbersOfList (vector<int> nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else {
        vector<int> dp(len);
        vector<int> count(len);
        int maxV = 0;
        for (int i = 0; i < len; ++i) {
            dp[i] = 1; count[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    if (dp[j]+1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    }
                    //说明此时j的位置那有重复
                    else if (dp[j]+1 == dp[i])
                        count[i] += count[j];
                }
            }
            maxV = max (dp[i], maxV);
        }
        int ret = 0;
        for (int i = 0; i < len;++i) {
            if (dp[i] == maxV)
                ret += count[i];
        }
        return ret;
    }
}
//时间复杂度：O(n^2) 空间复杂度：O(n)
/********** 12. 有几个最长上升子序列 **********/

/********** 13. 最长连续序列长度，要求O(n) **********/
/* 题目： 给定一个未排序的整数数组，找出最长连续序列的长度。要求算法的时间复杂度为 O(n)。
 * 输入: [100, 4, 200, 1, 3, 2]； 输出: 4
 * 解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
 */
/* 分析： 首先使用unordered_set去重；
 * 遍历整个数组 ： 对于当前元素k，如果不存在（k-1），则表明，如果k是存在连续数组则是以k开始的，然后不断去判断(k++)是否存在，获取对应长度；
 * 如果当前元素k存在(k-1)说明不是以k开头的，则直接跳过*/
int longestConsecutive(vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    else {
        // unordered_set 基于哈希表实现，插入和查找是O(1)
        //!!!!非常注意：unordered_set可以去重，但是会打乱原数组顺序！！！
        unordered_set<int> setList;
        int maxLong = 0;
        for (auto i : nums) setList.insert(i);
        
        for (auto i : setList) {
            int curLong = 1;
            if (setList.count(i-1)) continue;
            else {
                while (setList.count(++i)) curLong++;
            }
            maxLong = max (maxLong, curLong);
        }
        return maxLong;
    }
}
//时间复杂度分析：外循环是O(n)，对于内循环，只有是连续数组的第一个数字，才会进入内循环：两种极端情况：第一是数组中每一个数字都是连续数组的第一数字{1,3,5,7}，这样的话，内循环都不进入；对于{5,4,3,2,1},则只有1这个数字才会进入内循环，因此还是O(n)
//空间复杂度是O(n)
/********** 13. 最长连续序列长度，要求O(n) **********/

/********** 14. 最长公共子序列 **********/
/* 题目： 返回这两个字符串的最长公共子序列的长度。
 * 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。
 *若这两个字符串没有公共子序列，则返回 0。
 */
/* 这种题处理起来比较固定，为了方便写出状态转移方程，最好画二维表，记住前面加个0:
 比如： text1:{babcde}, text2{ace}
 0   1   2   3   4   5   6
 
 0   b   a   b   c   b   e
 0    0  0   0   0   0   0   0   0
 1    a  0   0   1   1   1   1   1
 2    c  0   0   1   1   2   2   2
 3    e  0   0   1   1   2   2   3
 dp[i][j]表示text1[1~i] 与 text2[1~j]的最长公共子序列长度
 text1[i-1] == text2[j-1]:  dp[i][j] = dp[i-1][j-1] + 1;
 text1[i-1] != text2[j-1]:  dp[i][j] = max (dp[i-1][j] ,dp[i][j-1]);
 说明：使用i-1主要是由于从1开始；如果从0开始，对于下标是i-1的情况还要单独讨论
 不等时，当前最常长度，分别由二维列表中的左面和上面那个大决定
 */

int longestCommonSubsequence(string text1, string text2) {
    int len1 = (int)text1.length(), len2 = (int)text2.length();
    if (len1 == 0 || len2 == 0) return 0;
    else {
        vector<int> vec((len2+1),0);
        vector<vector<int> > dp((len1+1), vec);
        
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (text1[i-1] == text2[j-1])
                    //理解：dp[i-1][j-1]表示text1[1~i-1] 与 text2[1~j-1]的最长公共子序列长度,这时候，text1[i]（从1开始是i,从0开始是i-1） 和 text2[j]又相等,所以直接在dp[i-1][j-1] 上加 1
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max (dp[i-1][j], dp[i][j-1]);
            }
        }
        
        return dp[len1][len2];
    }
}
/********** 14. 最长公共子序列 **********/

/********** 15. 单词转换最少次数 **********/
/* 题目：给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 ，你可以对一个单词进行如下三种操作：
 1）插入一个字符
 2） 删除一个字符
 3）替换一个字符
 示例 1:输入: word1 = "horse", word2 = "ros"  输出: 3
 解释:
 horse -> rorse (将 'h' 替换为 'r')
 rorse -> rose (删除 'r')
 rose -> ros (删除 'e')
 */
int minDistance(string word1, string word2) {
    /* 思路：
     * dp[i][j] 表示将 s1[0-i] 转换成 s2[0-j] 所需要的最小次数；
     * if (s1[i] == s2[j]) dp[i][j] = dp[i-1][j-1];
     * else :
     *  第一种处理办法： 直接将s1的第i 个字符替换成 s2的第j个字符： dp[i][j] = dp[i-1][j-1] + 1;
     *  第二种处理办法： 直接在s1的第i 个字符后插入一个 s2的第j个字符： dp[i][j] = dp[i][j-1] + 1;
     *  第三种处理办法： 直接将s1的第i 个字符删除掉： dp[i][j] = dp[i-1][j] + 1;
     */
    int len1 = (int)word1.length(), len2 = (int)word2.length();
    //if (len1 == 0) return len2;
    //else if (len2 == 0) return len1;
    if (len1 * len2 == 0) return len1+len2;
    else {
        //初始化
        vector<vector<int>> dp(len1+1, vector<int>(len2+1));
        for (int i = 0; i <= len1; ++i) dp[i][0] = i;
        for (int i = 1; i <= len2; ++i) dp[0][i] = i;
        
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
                else  dp[i][j] = 1 + min ( (min (dp[i-1][j-1], dp[i][j-1])), dp[i-1][j]);
            }
        }
        return dp[len1][len2];
    }
}
/********** 15. 单词转换最少次数 **********/

/********** 16. 数字编码 **********/
/* 题目：一条包含字母 A-Z 的消息通过以下方式进行了编码：
 'A' -> 1
 'B' -> 2
 'Z' -> 26
 给定一个只包含数字的非空字符串，请计算解码方法的总数。
 */

int countCodeWays (string s) {
    int n = (int) s.length();
    if (n == 0) return 0;
    else {
        if (s[0] == '0') return 0;
        else {
            int cur = 1, pre = 1, ppre = 1;
            for (int i = 1; i < n; ++i) {
                assert (s[i] >= '0' && s[i] <= '9');
                if (s[i] == '0') {
                    if (s[i-1] == '1' || s[i-1] == '2') {cur = ppre; ppre = pre; pre = cur;}
                    else {cur = 0; break;}
                }
                else if (s[i] >= '1' && s[i] <= '6') {
                    if (s[i-1] == '1' || s[i-1] == '2') {cur = pre +  ppre; ppre = pre; pre = cur;}
                    else {cur = pre; ppre = pre; pre = cur;}
                }
                else {
                    if (s[i-1] == '1') {cur = pre +  ppre; ppre = pre; pre = cur;}
                    else {cur = pre; ppre = pre; pre = cur;}
                }
            }
            return cur;
        }
    }
}
/* s[i]=='0' : if s[i-1]==[1,2], dp[i]=dp[i-2]; 不增加    另dp[-1] = dp[0] = 1;
 * s[i-1]='1' : dp[i] = dp[i-1] + dp[i-2]; s[i]与s[i-1]分开编码为dp[i-1],合并编码为dp[i-2]
 * s[i-1]='2' : and s[i]==[1,6] : dp[i]=dp[i-1]+dp[i-2]; s[i]与s[i-1]分开编码为dp[i-1],合并编码为dp[i-2]
 */
int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int pre = 1, curr = 1;//dp[-1] = dp[0] = 1
    for (int i = 1; i < s.size(); i++) {
        int tmp = curr;
        if (s[i] == '0')
            if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
            else return 0;
            else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
                curr = curr + pre;
        pre = tmp;
    }
    return curr;
}
/********** 16. 数字编码 **********/

/********** 17. 不同的二叉搜索树 **********/
/* 题目 ：给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？ https://leetcode-cn.com/problems/unique-binary-search-trees/
 * 分析 ： f(n) 表示n个节点可以组成的二叉搜索树种类总数，g(i，n)表示以i为根，一共有n个节点可以构建的种类总数
 * 则f(n) = g(1,n) + g(2,n) + ... + g(n,n)
 * 例如 g(4,6)表示以3为根节点，节点一共5个，其中1，2,3号节点只能放在跟节点左面，5，6只能放在右面，所以g(3,5)=f(3)*f(2)
 * 抽象出来就是g(i,n)=f(i-1)*f(n-i)
 * f(n) = g(1,n) + g(2,n) + ... + g(n,n)
 *      = f(0)*f(n-1) + f(1)*f(n-2) + ... + f(n-1)f(0)
 * 初始化条件：
 * f(0)比较特殊，f(0)表示的实际意义应该是0，这里初始化为1；
 * f(1) = 1, f(2) = 2;
 */
int searchBinaryTreeNums (unsigned int n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else if (n == 2) return 2;
    else {
        vector<int> dp(n+1,0);
        dp[0] = 1; dp[1] = 1; dp[2] = 2;
        for (int i = 3; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i-1-j];
            }
        }
        return dp[n];
    }
}
/********** 17. 不同的二叉搜索树 **********/

/********** 18. 三角形最短路径和 **********/
/* 题目： 给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。链接：https://leetcode-cn.com/problems/triangle/
 * 相邻的结点 与(i, j) 点相邻的结点为 (i + 1, j) 和 (i + 1, j + 1)。
 [2],
 [3,4],
 [6,5,7],
 [4,1,8,3]
 * 分析：dp[i][j]表示到达第i行第j列元素得到的最小路径和。
 * 可以到达（i,j）位置的分为三种情况：
 * 对于每一行的首元素位置：dp[i][j] = dp[i-1][j] + nums[i][j];
 * 对于每一行的末尾元素位置： dp[i][j] = dp[i-1][j-1] + nums[i][j-1];
 * 对于每一行的剩下位置元素： dp[i][j] = min（dp[i-1][j], dp[i-1][j-1]）+nums[i][j]
 * 最后遍历最后一行得到最小元素
 */
int minimumTotal(vector<vector<int>>& triangle) {
    int rows = (int)triangle.size();
    if (rows == 0) return 0;
    else {
        //使用原来空间进行存储
        for (int i = 1; i < rows; ++i) {
            int cols = (int)triangle[i].size();
            for (int j = 0; j < cols; ++j) {
                if (j == 0) triangle[i][j] += triangle[i-1][j];
                else if (j == cols-1)  triangle[i][j] += triangle[i-1][j-1];
                else triangle[i][j] += min (triangle[i-1][j], triangle[i-1][j-1]);
            }
        }
        //新技能！！！！！！！！！
        int minNum = *min_element(triangle[rows-1].begin(),triangle[rows-1].end());
        //int minV = triangle[rows-1][0];
        //for (int i = 1; i < (int)triangle[rows-1].size(); ++i)
        //    if (triangle[rows-1][i] < minV) minV = triangle[rows-1][i] ;
        return minNum;
    }
}
/********** 18. 三角形最短路径和 **********/

/********** 19. 买卖股票，一天最多交易一次 **********/
/* 题目：给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。注意：你不能在买入股票前卖出股票。
 示例 1:
 输入: [7,1,5,3,6,4]   输出: 5
 解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
 */
int maxProfit(vector<int>& prices) {
    int len = (int) prices.size();
    if (len < 2) return 0;
    else {
        int dp = 0;
        int minV = prices[0], maxV = 0;
        for (int i = 1; i < len; ++i) {
            if (prices[i] < minV) minV = prices[i];
            else dp = prices[i] - minV;
            maxV = max(maxV, dp);
        }
        return maxV;
    }
}
/********** 19. 买卖股票，一天最多交易一次 **********/

/********** 20. 单词拆分 **********/
/* 题目 ： 给出一个字符串s和一个词典，判断字符串s是否可以被空格切分成一个或多个出现在字典中的单词。
 * s = "lintcode"   dict = ["lint","code"]   返回true
 * 分析： dp[i] 表示 字符串的前i位 是否可以被字典表示
 * dp[j] = dp[i] && dict.count(s[i+1:j]);
 */
bool wordSplite (string s, unordered_set<string> dict) {
    int len = (int) s.length();
    if (len == 0) return true;
    else {
        vector<bool> dp(len+1, false);
        dp[0] = true;
        //i表示子串的起点
        for (int i = 0; i < len; ++i) {
            //j表示子串的终点
            for (int j = 1; j <= len; ++j) {
                //s.substr(pos,len);
                string sub = s.substr(i+1, j-i);
                if (!dp[j])
                    dp[j] = dp[i] && dict.count(sub);
            }
        }
        return dp[len];
    }
}
/********** 20. 单词拆分 **********/

/********** 21. 零钱兑换 **********/
/* 题目： 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。 https://leetcode-cn.com/problems/coin-change/
 输入: coins = [1, 2, 5], amount = 11  输出: 3
 解释: 11 = 5 + 5 + 1
 * 方法一： 动态规划 ： dp[i] 表示凑够i所需最少次数
 */
int coinChange (vector<int> coins, int amount) {
    int len = (int)coins.size();
    if (len == 0) throw invalid_argument("None");
    else {
        if (amount == 0) return 0;
        else {
            vector<int> dp(amount+1, amount+1);
            dp[0] = 0;
            for (int i = 1; i <= amount; ++i) {
                for (auto j : coins) {
                    if (i - j < 0) continue;
                    else
                        dp[i] = min (dp[i], dp[i-j]+1);
                }
            }
            return dp[amount] == amount+1 ? -1 : dp[amount];
        }
    }
}
//方法二： 贪心 + DFS (以后有时间回头看！！！！)
/********** 21. 零钱兑换 **********/

/********** 22. 4键键盘 **********/
/* 题目：一个特殊的键盘包含下面的按键：
 Key 1: (A)：在屏幕上打印一个 'A'。
 Key 2: (Ctrl-A)：选中整个屏幕。
 Key 3: (Ctrl-C)：复制选中区域到缓冲区。
 Key 4: (Ctrl-V)：将缓冲区内容输出到上次输入的结束位置，并显示在屏幕上。
 输入: N = 7
 输出: 9
 解释:
 我们最多可以在屏幕上显示九个'A'通过如下顺序按键：
 A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
 * 分析： 假设A的个数是s,(Ctrl-V)的个数是t, 则 s+2+t=n, 求f(s,t) = s*(1+t)的最大值，其中 1<=s<= n-3
 */
int ANums (unsigned int n) {
    if (n <= 6) return n;
    else {
        int maxV = 7;
        for (int i = 1; i <= n-3; ++i) {
            int tmp = i*(n-i-1);
            maxV = max (maxV, tmp);
        }
        return maxV;
    }
}
/********** 22. 4键键盘 **********/

/********** 23. 拦截导弹 **********/
/* 题目 ： 一种导弹拦截系统有一个缺陷：第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能高于前一发的高度。
 　　输入导弹依次飞来的高度（雷达给出的高度不大于30000的正整数）。计算要拦截所有导弹最小需要配备多少套这种导弹拦截系统。
 【输入】８        389 207  155  300  299  170  158 65
 【输出样例】 2
 * 对于第i个导弹，如果这个导弹高度比所有降序序列的最低高度都要大，则需要增加一个系统，否则使用原来某个系统
 */
int decreaseNums (vector<int> nums) {
    int len = (int) nums.size();
    if (len == 0) return 0;
    else {
        vector<int> minHeightList;  //用来存储每个系统目前可击落的导弹高度
        minHeightList.push_back(nums[0]);
        int systemNums = (int)minHeightList.size();  //目前有几个系统
        //i表示每个导弹高度
        for (int i = 1; i < len; ++i) {
            bool flag = false; //表示当前导弹是否可被已有的系统拦截；
            //j表示每个系统现在最高可击落的导弹高度
            for (int j = 0; j < minHeightList.size(); ++j) {
                if (nums[i] < minHeightList[j]) {
                    minHeightList[j] = nums[i];
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                minHeightList.push_back(nums[i]);
                systemNums++;
            }
        }
        return systemNums;
    }
}
/********** 23. 拦截导弹 **********/

/********** 24. 合唱队形 **********/
/* 题目 ； N位同学站成一排，音乐老师要请其中的(N-K)位同学出列，使得剩下的K位同学排成合唱队形。
 合唱队形是指这样的一种队形：设K位同学从左到右依次编号为1, 2, …, K，他们的身高分别为T1, T2, …, TK，则他们的身高满足T1 < T2 < … < Ti , Ti > Ti+1 > … > TK (1≤i≤K)。
 你的任务是，已知所有N位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。
 输入： 8
 4 4 2 6 3 1 5 7
 输出：4
 */
/* 分析 ： 出队人数最少 -> 留下人数最多
 * 留下人的特点 ： 一个递增序列 + 一个递减序列
 * 设 increase[i] 表示 以i 位置为结尾的最长递增子序列； decrease[i]表示以i为结尾的最长递减子序列
 * dp[i] = increase[i] + decrease[i]
 * return max (dp[i])
 */
vector<int> maxIncraseList (vector<int> nums) {
    int len = (int) nums.size();
    vector<int> ret(len,1);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) nums[i] = max (nums[i], nums[j]+1);
        }
    }
    return ret;
}

vector<int> maxDecraseList (vector<int> nums) {
    vector<int> ret(len,1);
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] < nums[j]) nums[i] = max (nums[i], nums[j]+1);
        }
    }
    return ret;
}

int gerMinOut (vector<int> nums) {
    int ret = 0;
    int len  = (int) nums.size();
    if (nums > 1) {
        vector<int> increase = maxIncraseList(nums);
        vector<int> decrease = maxDecraseList(nums);
        for (int i = 0; i < len; ++i) {
            ret = max (ret, (increase[i] + decrease[i]));
        }
    }
    
    return ret-1;
}
/********** 24. 合唱队形 **********/

/********** 25. 放苹果 **********/
/* 题目 ：把 M 个同样的苹果放在 N 个同样的盘子里，允许有的盘子空着不放，问共有多少种不同的分法？
 注意：5、1、1 和 1、5、1 是同一种分法，即顺序无关。
 输入：7 3；    输出：8
 * dp[i][j]表示i个苹果放在j个盘子的放法：dp[0][j]=dp[i][0]=0;
 * 盘子个数大于苹果个数时候，多出来的盘子必然空着，因为和顺序无关，所以 i < j dp[i][j]=dp[i][i]
 * i >= j 时：有两种情况：
 *      第一种情况：所有盘子都有苹果，即 dp[i][j] = dp[i-j][j]
 *      第二种情况：至少有一个盘子没有苹果，即 dp[i][j] = dp[i][j-1]
 *      两种情况加起来： dp[i][j] = dp[i-j][j] + dp[i][j-1];
 */
//方法一：动态规划
int placeApples0 (unsigned apples, unsigned disks) {
    if (apples == 0 || disks == 0) return 0;
    else if (apples == 1 || disks == 1) return 1;
    else {
        //注意：这个初始化并不代表实际意义，但是只能这样初始化！！dp[i][0]=dp[0][j]=1!!!!!
        vector<int> tmp(disks+1, 1);
        vector<vector<int>> dp(apples+1, tmp);
        for (int i = 2; i <= apples; ++i) {
            for (int j = 2; j <= disks; ++j) {
                if (j > i) dp[i][j] = dp[i][i];
                else dp[i][j] = dp[i-j][j] + dp[i][j-1];
            }
        }
        return dp[apples][disks];
    }
}
//方法二：递归
/* 这是一个递归调用，出口非常重要！
 * if j > i : j = i
 * if i == 0 || j == 1 return 1
 * j == 1 表示盘子只剩下一个的时候，所有苹果只能放在一个盘子里，return 1
 * i == 0 表示没有苹果可放的时候（这种情况下，盘子的个数也是0），定义为1；
 */
int placeApples1 (unsigned apples, unsigned disks) {
    if (apples == 0 || disks == 1) return 1;
    if (apples < disks) return placeApples1(apples, apples);
    else return placeApples1(apples-disks, disks) + placeApples1(apples, disks-1);
}
/********** 25. 放苹果 **********/

/********** 26. 最大子矩阵问题 (困难)**********/
/* 题目：给定一个正整数和负整数组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。
 * 返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。
 */
vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
    /* 思路： 将二维动态规划转换成一维动态规划
     * 对于矩阵中 所有可能的行号组合， 将列压缩成一维和，对于每一个一维（列之和）使用动态规划求取连续子数组的最大值
     */
    int rows = int (matrix.size());
    if (rows == 0) throw invalid_argument("Invalid.");
    else {
        int res = INT_MIN;  //用来存储矩阵中子矩阵的最大值
        vector<int> ret(4,0);
        int cols = int(matrix[0].size());
        int r1, r2, c1, c2;
        //（对矩阵的第i到第j行 进行压缩）
        for (int i = 0; i < rows; ++i) {
            r1 = i;
            for (int j = i; j < rows; ++j) {
                r2 = j;
                //compress是压缩后的一维数组
                vector<int> compress(cols,0);
                for (int k = 0; k < cols; ++k) {
                    for (int s = i; s <= j; ++s)
                        compress[k] += matrix[s][k];
                }
                //对压缩后的矩阵 求取连续子序列的最大值
                c1 = 0; c2 = 0;
                int pre = compress[0], cur = compress[0], maxV = compress[0];
                int begin = 0;
                for (int t = 1; t < cols; ++t) {
                    if (compress[t] > compress[t] + pre) {
                        cur = compress[t];
                        begin = t;  //因为很有可能compress[0]就是数组中的最大值，所以不能直接将t赋值给c1
                    }
                    else cur = compress[t] + pre;
                    pre = cur;
                    if (cur > maxV) {
                        maxV = cur;
                        c1 = begin;
                        c2 = t;
                    }
                }
                //当前压缩矩阵的最大值 和 矩阵中最大的子矩阵之和 res 进行比较
                if (maxV > res) {
                    res = maxV;
                    ret[0] = r1;  ret[1] = c1; ret[2] = r2; ret[3] = c2;
                }
            }
        }
        return ret;
    }
}
/********** 26. 最大子矩阵问题 **********/

/********** 27. 连续数组最大和 **********/
/* 题目： 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 输入: [-2,1,-3,4,-1,2,1,-5,4]  输出: 6
 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6
 * 连续子数组求和求积问题 当前元素 必须得取！!!!!
 * 连续子数组求和求积问题 当前元素 必须得取！!!!!!
 * 连续子数组求和求积问题 当前元素 必须得取！
 * 连续子数组求和求积问题中 dp[i] / dp[i][2] 表示的是以当前元素为结尾的局部最大值，而不是0-i的局部最大值问题。最后在0-len-1 取max即可
 */
// dp[i] = max (dp[i-1]+nums[i], nums[i]);
int maxSubArray(vector<int>& nums) {
    int len = (int) nums.size();
    if (len == 0) return 0;
    else if (len == 1) return nums[0];
    else {
        int pre = nums[0], cur = nums[0];
        int maxV = nums[0];
        for (int i = 1; i < len; ++i) {
            cur = max (nums[i], pre + nums[i]);
            pre = cur;
            maxV = max (maxV, cur);
        }
        return maxV;
    }
}
//方法二：贪心法：思想，每次都加上当前元素，使用sum表示到达当前位置时的连续子数组之和
//如果sum < 0; sum = 0;
//ret 表示到达当前位置时候，0-i的最大连续数组之和
int maxSubArray1(vector<int>& nums) {
    int len = (int) nums.size();
    if (len == 0) return 0;
    else if (len == 1) return nums[0];
    else {
        int sum = 0, ret = INT_MIN;
        for (int i = 1; i < len; ++i) {
            sum += nums[i];
            ret = max (ret, sum);
            if (sum < 0) sum = 0;
        }
        return ret;
    }
}
//方法三：分治/线段树
//27.3 返回最大连续子数组的起始位置

/********** 27. 连续数组最大和 **********/
vector<int> maxSubArrayIndex(vector<int>& nums) {
    int len = (int) nums.size();
    vector<int> ret{0,0};
    if (len == 0) throw invalid_argument("Invalid");
    else if (len == 1) return ret;
    else {
        int pre = nums[0], cur = nums[0];
        int maxV = nums[0];
        for (int i = 1; i < len; ++i) {
            if (nums[i] > pre + nums[i]) {
                cur = nums[i];
                ret[0] = i;
            }
            else cur = pre + nums[i];
            pre = cur;
            if (maxV < cur) {
                maxV = cur;
                ret[1] = i;
            }
        }
        return ret;
    }
}

//单调栈问题：
/*************************** 1. 每日温度 739 ***************************/
/* 题目 ： 给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0] 表示想观测到更高温度至少需要等待的天数，如果之后气温不再升高使用0表示。
 * 分析 ：设计一个单调栈 和 一个计数器：
 * 初始化：push(73),count=1
 * 从 74开始判断 ： 74>top(), pop(73), ret.push(d=1),push(74)
 * 75>top(), pop(74), ret.push(d=1),push(75)
 * 71<=top(),push(71)
 * 69<=top(),push(69)
 * 72 > top(), pop(69),ret.push(d=1); pop(71),ret.push(d=2),push(72)
 * 76>top(),pop(72),ret.push(d=1),pop(75),ret.push(d=4),push(76)
 * 73<top(),push(73),
 * end : ret.push(0),ret.push(0)
 * 关键是如何求得距离d : 先遍历一遍使用hash表？有没有更好的方法？ 可以单独保存一份距离数组！
 */
vector<int> dailyTemperatures(vector<int>& T) {
    int len = (int) T.size();
    vector<int> ret(len,0);
    if (len > 1) {
        stack<pair<int,int>> st;
        
        for (int i = 0; i < len; ++i) {
            while (!st.empty() &&  T[i] > st.top().second) {
                ret[st.top().first] = i-st.top().first;
                st.pop();
            }
            st.push(make_pair(i, T[i]));
        }
    }
    return ret;
}
/*************************** 每日温度 ***************************/

//单调栈：224,227,772,770 基本计算器系列题目
/*************************** 计算器问题 **************************/
/* 题目 ： 实现一个基本计算器来计算一个简单的字符串表达式的值
 * 表达式可以包涵左括号，右括号，加减号，非负整数和空格，假设所有表达式都是有效的
 *  分析 ： 单调栈主要用于解决括号匹配的问题：遇到左括号，就将ret和flag（正负号标识位入栈），遇到右括号就出站
 */
int calculator (string s) {
    int len = int (s.size());
    int ret = 0;
    int flag = 1;
    stack<int> st;
    if (len > 0) {
        for (int i = 0; i < len; ++i) {
            long long tmp = 0;
            if (s[i] == ' ') continue;
            else if (s[i] >= '0' && s[i] <= '9') {
                while (s[i] >= '0' && s[i] <= '9') {
                    tmp = tmp * 10 + s[i]-'0';
                    ++i;
                    if (tmp > INT_MAX) return 0;
                }
                --i;
                ret += tmp * flag;
            }
            else if (s[i] == '+') flag = 1;
            else if (s[i] == '-') flag = -1;
            else if (s[i] == '(') {
                st.push(ret);
                st.push(flag);
                ret = 0; flag = 1;
            }
            else if (s[i] == ')') {
                ret *= st.top(); st.pop();
                ret += st.top(); st.pop();
            }
            else
                throw invalid_argument ("Invalid input.");
        }
    }
    return ret;
}
/*************************** 计算器问题 **************************/

/*************************** 2. 接雨水 42 **************************/
/* 题目 ： n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 *  输入: [0,1,0,2,1,0,1,3,2,1,2,1]  输出: 6
 * 注意 ！ 这里的 输入的值不是一个点，而是一个柱子！一定要画图，而且画图表示柱子！！最少3个柱子才能接水！
 * 无法描述算法，只能画图分析，使用单调栈解决
 */
int trap(vector<int>& height) {
    int len = int (height.size());
    //保存最终可存储的雨水量
    int ret = 0;
    if (len > 2) {
        //pair分别表示柱子的下标和高度
        stack<pair<int,int>> st;
        //三个柱子中最低和最高的那个柱子
        int floor = 0, ceil = 0;
        for (int i = 0; i < len; ++i) {
            while (!st.empty() && height[i] > st.top().second) {
                //前面高度比当前低，因为前面的都计算过，低的柱子可以直接可忽略
                if (st.size() == 1) st.pop();
                else {
                    //在满足的条件下，有3个柱子就计算一次，floor是3个柱子中最低的那个，记录下高度后，就pop
                    floor = st.top().second;
                    st.pop();
                    // 高 * 宽, 高 = ceil - floor
                    ceil = min (st.top().second, height[i]);
                    // 宽 = i-st.top().first-1
                    ret += (ceil - floor) * (i-st.top().first-1);
                }
            }
            //当前柱子高度和栈顶柱子高度相同的情况，没有必要保存当前柱子
            while (!st.empty() && height[i] == st.top().second) st.pop();
            st.push(make_pair(i, height[i]));
        }
    }
    return ret;
}
/*************************** 接雨水 ***************************/


/*************************** 3. 柱状图中最大的矩形 84 ***************************/
/* 题目 ：  n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 ，求在该柱状图中，能够勾勒出来的矩形的最大面积。
 * 输入: [2,1,5,6,2,3] 输出: 10
 * 分析 ： 勾勒出的面积，必须是所有柱子的部分贡献的面积，对与5，6，2，3，可以是2*4 但是不能是3*4，原因就在这
 * 求最大矩形面积：宽*高，关于高可以采用遍历法，选取每一个高进行判断，看这个大于等于这个高度的柱子左右边界是多少，就可以确定宽了
 * 使用单调增栈来解决大于等于某个柱子高度的左右边界：站内元素递增序列，大于栈顶元素则直接入栈
 *      小于栈顶元素，说明栈顶元素的右边界就是当前元素，左边界就是栈内下一个元素
 *          不停出栈，直到栈顶元素比当前元素小，则当前元素入栈
 * 每一次出栈过程就能确定出战的这个柱子高度的左右边界，从而能计算以这个高度为高能够构成矩阵的面积。
 */
int largestRectangleArea(vector<int>& height) {
    //小技巧：可以在数组尾端加入一个高度为-1的柱子，这样循环结束后就可以保证栈中没有柱子了
    height.push_back(-1);
    int len = int (height.size());
    stack<pair<int,int>> st;
    int ret = 0;
    //每个柱子高度对应的宽和高
    int w = 1, h = 0;
    
    for (int i = 0; i < len; ++i) {
        //栈顶柱子高度比当前柱子小就出栈，计算栈顶高度柱子的面积
        while (!st.empty() && height[i] < st.top().second){
            //待计算的高度
            h = st.top().second;
            //栈顶高度的柱子有可能有多个
            while (!st.empty() && st.top().second == h) st.pop();
            //宽度, 右边界是i, 左边界分情况讨论：st中没有柱子的时候，说明左边界是起始位置
            if (st.empty()) w = i;
            else w = i - st.top().first - 1;
            ret = max (ret, w*h);
        }
        st.push(make_pair(i, height[i]));
    }
    return ret;
}
//最大矩形 85， 二维转成一维，就是本题中最大矩形面积
/*************************** 柱状图中最大的矩形 ***************************/

/*************************** 下一个更大元素1 496 ***************************/
/* 题目： 两个 没有重复元素 的数组 nums1 和 nums2 ，其中nums1 是 nums2 的子集。找到 nums1 中每个元素在 nums2 中的下一个比其大的值。nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置的右边的第一个比 x 大的元素。如果不存在，对应位置输出 -1 。
 * 输入: nums1 = [4,1,2], nums2 = [1,3,4,2].   输出: [-1,3,-1]
 * 分析 ： 分析nums2, 如果cur>top(),map(); pop(), push()
 *                  cur <= top(); push
 * 栈中保存递减数字
 */
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int len1 = int (nums1.size()), len2 = int (nums2.size());
    vector<int> ret;
    if (len2 < 1 || len1 < 1) return ret;
    unordered_map<int,int> mmap;
    stack<int> st;
    
    for (int i = 0; i < len2; ++i) {
        while (!st.empty() && nums2[i] > st.top()) {
            mmap[st.top()] = nums2[i];
            st.pop();
        }
        st.push(nums2[i]);
    }
    while (!st.empty()) {
        mmap[st.top()] = -1;
        st.pop();
    }
    for (int i : nums1) ret.push_back(mmap[i]);
    return ret;
}
//下一个更大元素2 503  下一个更大元素3 556
/*************************** 下一个更大元素1 ***************************/


int main () {
    cout << placeApples0(7,3) <<endl;
    vector<int> r1{1,2,5};
    cout<< coinChange(r1, 11)<<endl;
    //vector<int> t1{-4,-5};
    vector<int> t1{9,-8,1,3,-2},t2{-3,7,6,-2,4},t3{6,-4,-4,8,-7};
    vector<vector<int>> t{t1,t2,t3};
    vector<int> tmp = getMaxMatrix (t);
    for (auto i : tmp) cout <<i<<" ";
    cout<<endl;
    vector<int> s5{-2,1,-3,4,-1,2,1,-5,4};
    //vector<int> t = maxSubArrayIndex(s5);
    //cout<<t[0]<<"to"<<t[1]<<endl;
    int a[] = {0,1,1,1,2,2,4};
    cout << func (a,7)<<endl;
    for (auto i : a) cout << i << " ";
    cout<<endl;
    cout << febnaci1(5) << endl;
    cout << febnaci2(5) << endl;
    cout << febnaci3(5) << endl;
    vector<int> vec{2,3,2};
    cout << row2(vec)<<endl;
    cout << getPath1 (7, 3) << endl;
    vector<vector<int> > vec1{{0,0,0},{0,1,0},{0,0,0}};
    cout << getPath4(vec1)<<endl;
    cout << rob3(vec)<<endl;
    TreeNode root[10];
    root[0].val = 2;
    root[0].left = &root[1];
    root[0].right = &root[2];
    
    root[1].val = 1;
    root[1].left = NULL;
    root[1].right = &root[3];
    
    root[2].val = 3;
    root[2].left = NULL;
    root[2].right = NULL;
    
    root[3].val = 4;
    root[3].left = NULL;
    root[3].right = NULL;
    
    cout << rob (&root[0]) << endl;
    vector<int> v3{2,-1,0,4,-3,3,-2};
    cout << getMax1(v3)<<endl;
    
    vector<int> weight{1,2,3,4};
    vector<int> value{2,4,4,5};
    cout << package(weight, value, 5, 4) <<endl;
    vector<int> v{3,5,6,2,5,4,19,5,6,7,12};
    cout<< lengthOfLIS1 (v)<<endl;
    
    vector<int> v1{5,6,7,1,2,3,7,7};
    cout<< longestSeq (v1)<<endl;
    
    vector<int> v2{9,1,4,7,3,-1,0,5,8,-1,6};
    
    cout<< findNumbersOfList (v2)<<endl;
    cout<< longestConsecutive (v2)<<endl;
    string s1 = "horse", s2 = "ros";
    cout << longestCommonSubsequence (s1,s2)<<endl;
    string s = "";
    cout << " TESTING: " << countCodeWays (s) << endl;
}

#endif

