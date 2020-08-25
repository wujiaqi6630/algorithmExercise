#if WDEBUG
/* 矩阵中路径
 * 机器人运动范围
 */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <deque>
#include <algorithm>
using namespace std;


/********************* 1. 矩阵中的路径 12 ************************/
/* 题目 ： 判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。
 * 分析 ： 遍历整个二维数组，遇到第一个字符匹配的时候，就开始分别往上下左右分别试探， 不成功就回溯
 * 需要保存一个二维表 表示是否已经访问过
 */
vector<vector<bool>> visited;
int len, rows, cols;
int count;

bool isExistPath (vector<vector<char>>& board, string word, int r, int c){
    if (count == len) return true;
    if (!(r >= 0 && r < rows && c >= 0 && c < cols && !visited[r][c] && board[r][c] == word[count])) {
        return false;
    }
    ++count;
    visited[r][c] = true;
    
    bool flag = isExistPath (board, word, r+1, c) ||
    isExistPath (board, word, r-1, c) ||
    isExistPath (board, word, r, c+1) ||
    isExistPath (board, word, r, c-1);
    
    if (!flag) {
        --count;
        visited[r][c] = false;
    }
    return flag;
}

bool exist(vector<vector<char>>& board, string word) {
    len = int (word.size());
    if (len < 1) return true;
    rows = int (board.size());
    if (rows < 1) return false;
    cols = int (board[0].size());
    count = 0;
    bool ret = false;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == word[0]){
                visited = vector<vector<bool>>(rows,vector<bool>(cols,false));
                count = 0;
                if (isExistPath (board, word, i, j)) {
                    ret = true;
                    break;
                }
            }
        }
    }
    return ret;
}
/********************* 矩阵中的路径 ************************/

/********************* 2. 机器人运动范围 13 ************************/
/* 题目 ： 地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
 * 分析 ： 从当前节点出发，每次有四个方向可选，每次走过的都设置为true，如果不满足条件，则退回去换另外一个方向
 */
vector<vector<bool>> visited;
int count;
int r, c;

bool isLegeal (int x, int y, int k) {
    int sum = 0;
    while (x > 0) {  //需要注意此处不是想x != 0 !!!
        sum += x % 10;
        x /= 10;
    }
    while (y > 0) {
        sum += y % 10;
        y /= 10;
    }
    return sum <= k;
}
void movingCountCore (int m, int n, int k) {
    //结束条件！！！！
    if (!(m >= 0 && m < r && n >= 0 && n < c && !visited[m][n] && isLegeal(m,n,k))) {
        return ;
    }
    ++count;
    visited[m][n] = true;
    movingCountCore (m+1, n, k);
    movingCountCore (m, n+1, k);
    
}
int movingCount(int rows, int cols, int k) {
    visited = vector<vector<bool>> (rows,vector<bool>(cols,false));
    r = rows, c = cols, count = 0;
    movingCountCore (0, 0, k);
    return count;
}

/********************* 机器人运动范围  ************************/

/********************* 3.  矩阵中的最长递增路径 329************************/
/* 题目：给定一个整数矩阵，找出最长递增路径的长度。对于每个单元格，你可以往上，下，左，右四个方向移动。 你不能在对角线方向上移动或移动到边界外
 * 输入：nums =   [9,9,4],
                 [6,6,8],
                 [2,1,1]    输出: 4； 解释: 最长递增路径为 [1, 2, 6, 9]。
 * 分析 ：对于每一个数字分别判断
 */
vector<vector<int>> mem;
int ret, count1, count2;
int rows, cols;
vector<int> path;

void findLongestPath (vector<vector<int>>& matrix, int r, int c) {
    if (!path.empty() && !(r >= 0 && r < rows && c >= 0 && c < cols && matrix[r][c] > path.back()))
        return ;
    
    if (mem[r][c] != -1)
        count2 = max (count2, count1 + mem[r][c]);
    else {
        ++count1;
        path.push_back(matrix[r][c]);
        
        findLongestPath (matrix, r, c+1);
        findLongestPath (matrix, r+1, c);
        findLongestPath (matrix, r, c-1);
        findLongestPath (matrix, r-1, c);
        
        count2 = max (count1, count2);
        --count1;
        path.pop_back();
    }
}

int longestIncreasingPath(vector<vector<int>>& matrix) {
    rows = int (matrix.size());
    if (rows == 0) return 0;
    cols = int (matrix[0].size());
    if (cols == 0) return 0;
    ret = 0;
    mem = vector<vector<int>> (rows,vector<int>(cols,-1));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            count1 = 0; count2 = 0;
            if (i==0&&j==1)
                cout << " ";
            findLongestPath (matrix, i, j);
            mem[i][j] = count2;
            ret = max (ret, count2);
        }
    }
    
    return ret;
}

/*********************  矩阵中的最长递增路径 ************************/

/**************** 5. 分割回文串131 ****************/
/* 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。返回 s 所有可能的分割方案。
 输入: "aab"
 输出:[   ["aa","b"],  ["a","a","b"]  ]
 */
/* 标准回溯问题 ：
 * 所谓分割就是substr（i,len-i）， i 从0开始，判断islegel(s(0,i))? : func(substr())
 */
vector<vector<string>> ret;

bool check (const string& s, int i, int j) {
    while (i <= j) {
        if (s[i++] != s[j--]) return false;
    }
    
    return true;
}

void backTrack (const string& s, vector<string>& tmp, int start) {
    if (start >= s.size()) {
        ret.push_back(tmp);
        return ;
    }
    
    for (int i = start; i < s.size(); ++i) {
        if (check (s, start, i)) {
            tmp.push_back(s.substr(start,(i-start+1)));
            backTrack(s, tmp, i+1);
            tmp.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    int len = int (s.size());
    if (len == 0) return ret;
    vector<string> tmp;
    backTrack (s, tmp, 0);
    return ret;
}
/**************** 分割回文串131 ****************/

/***************** N皇后 51****************/
//字符串输出形式见leetcode 51,虽然没通过，但是我认为是对的，答案是错误的
vector<vector<pair<int,int>>> ret;
vector<pair<int,int>> path;
vector<bool> flag;

bool check (vector<pair<int,int>>path, int r, int c) {
    for (int i = 0; i < path.size(); ++i) {
        if (r-path[i].first == c-path[i].second) return false;
    }
    return true;
}


//这里的r表示下一行，c表示当前列
void backTrack (int n, int r, int c) {
    //if (endFlag) return;
    if (r == n) {
        ret.push_back(path);
        return ;
    }
    
    for (int i = 0; i < n; ++i) {
        if (!flag[i] && check(r,i)) {
            path.push_back (make_pair(r, i));
            flag[i] = true;
            backTrack (n, ++r, i);
            path.pop_back();
            flag[i] = false;
            --r;
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    if (n < 1) return {};
    if (n == 1) return {{"Q"}};
    if (n < 4) return {};
    
    for (int c = 0; c < n; ++c) {
        if (ret.size() == 1)
            cout <<"123"<<endl;
        flag = vector<bool> (n, false);
        path.clear();
        
        path.push_back(make_pair(0,c));
        flag[c] = true;
        //注意这里是1而不是0，表示下一行，c表示当前列
        backTrack(n, 1, c);
    }
    return ret;
}
/***************** N皇后 51****************/

//下面两道题考到算倒霉！
/***************** 铺瓷砖 1240******************/
/***************** 铺瓷砖 ******************/

/**************** 解数独 37*****************/
/**************** 解数独 *****************/


#endif
