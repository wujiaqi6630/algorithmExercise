#if WDEBUG
/* 排列组合问题：
 * 1. 全排列问题
 * 1.1  字符串的排列
 */

//https://leetcode-cn.com/problems/combinations/solution/hui-su-si-xiang-tuan-mie-pai-lie-zu-he-zi-ji-wen-2/
//比较了排列，组合，子集三类问题
/********************** 无重复全排列 ************************/
//无重复全排列 46 面试题08.07
vector<vector<int>> ret;
set<vector<int>> tmp;
int len;

void backTrack (vector<int> input, vector<int>& path, vector<bool>& visited); {
    if (path.size() == input.size()) {
        ret.push_back (path);
        return;
    }
    
    for (int i = 0; i < input.size(); ++i) {
        if (!visited[i]) {
            path.push_back(input[i]);
            visited[i] = true;
            backTrack(input, path, visited);
            path.pop_back();
            visited[i] = false;
        }
    }
}
//无重复排列方法二：交换法(尽量不使用，除非有重复元素)
void backTrack1 (vector<int>& input, int start)  {
    if (start == input.size()) {
        ret.push_back(input);
        return ;
    }
    
    for (int i = start; i < input.size(); ++i) {
        
        swap(input[i], input[start]);
        //特别注意，是start参与递归
        backTrack1 (input, start+1);
        swap(input[i], input[start]);
        
    }
}
/********************** 无重复全排列 ************************/

/********************** 有重复全排列 ************************/
//47  面试题08.08
//使用unordered_set去重
//可以使用交换法，更加简洁
set<vector<int>> tmp;
int len;
void backTrack1 (vector<int> input, int start) {
    if (start >= len) {
        tmp.insert (input);
        return;
    }
    
    
    for (int i = start; i < len; ++i) {
        swap (input[i], input[start]);
        backTrack1 (input, start+1);
        swap (input[i], input[start]);
    }
    
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    len = int(nums.size());
    backTrack1(nums,0);
    return vector<vector<int>>(tmp.begin(), tmp.end());
}
/********************** 有重复全排列 ************************/


/********************** 组合 77 ************************/
vector<vector<int>> ret3;
void backTrack3 (int n, int m, vector<int>& path, int start) {
    if (path.size() == m) {
        ret3.push_back(path);
        return ;
    }
    
    for (int i = start; i <= n; ++i) {
        path.push_back(i);
        //注意是i参与递归
        backTrack3 (n, m, path, i+1);
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int m) {
    vector<int> path;
    backTrack3 (n, m, path, 1);
    return ret3;
}
//组合总数系列问题 39， 40， 216


/********************** 组合 ************************/


/********************** 子集 78 ************************/
vector<vector<int>> ret4;
void backTrack4(vector<int>& nums, vector<int>& path, int start) {
    ret4.push_back(path);
    
    for (int i = start; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        backTrack4(nums, path, i+1);
        path.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<int> path;
    backTrack4(nums, path, 0);
    return ret4;
}

//子集问题2 ： 90
/********************** 子集 ************************/


/**************** 电话号码组合 17 *****************/
/* 题目：数字2-9，返回他能表示的所有组合。 {{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}}
 * 输入23，输出 ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
 */
//方法一：三层for循环
//需要注意的是：并不知道输入长度是多少
vector<string> ret;
string path;
int len;
unordered_map<char,string> dict{{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}};
/*方法二：使用回溯解决：关键是如何设置for循环
 * 通常for循环两种设置模式：
 *  模式一： for (int i = start; i < len; ++i)这种主要用来控制“不回头”的回溯，比如组合，子集，字符串切割
 *  模式二： for (int i = 0; i < len; ++i) 这种用的不多，主要是带标识位的全排列
 *  本题电话号码组合采用特殊模式：for (int i = 0; i < map[start].size(); ++i)
 */
void backTrack(string digits, int start) {
    if (path.size() == len) {
        ret.push_back(path);
    }
    
    for (int i = 0; i < dict[digits[start]].size(); ++i) {
        path += dict[digits[start]][i];
        backTrack (digits, start+1);
        path.pop_back();
    }
}

vector<string> letterCombinations2(string digits) {
    len = int(digits.size());
    if (len != 0){
        backTrack (digits, 0);
    }
    return ret;
}
/**************** 电话号码组合 17 *****************/


/*
 * 回溯函数
 * 使用sort函数对字符串排序，使重复的字符相邻，
 * 使用visit数组记录遍历决策树时每个节点的状态，
 * 节点未遍历且相邻字符不是重复字符时，
 * 则将该字符加入排列字符串中，依次递归遍历。
 * */
void backtrack(vector<string> &res, string s, string &track, vector<bool> &visit) {
    // 回溯结束条件
    if(track.size() == s.size()){
        //if (find(res.begin(), res.end(), track) == res.end())
            res.push_back(track);
        return;
    }
    
    // 选择和选择列表
    for(int i = 0; i < s.size(); i++){
        // 排除不合法的选择
        if(visit[i]) continue;
        if(i > 0 && !visit[i-1] && s[i-1] == s[i]) continue;
        // 做选择
        visit[i] = true;
        track.push_back(s[i]);
        // 进入下一次决策树
        backtrack(res, s, track, visit);
        // 撤销选择
        track.pop_back();
        visit[i] = false;
    }
}

vector<string> permutation(string s) {
    if(s.empty()){
        return {};
    }
    // 对字符串进行排序
    std::sort(s.begin(), s.end());
    vector<string> res;
    // 标记字符是否遍历过
    vector<bool> visit(s.size(), false);
    string track;
    backtrack(res, s, track, visit);
    
    return res;
}


//解题思路二 交换法————回溯算法
/*
 * 交换法 —— 回溯算法
 *
 * [a, [b, c]]
 * [b, [a, c]] [c, [b, a]]
 *
 * 如上，对字符串"abc"分割，每次固定一个字符为一部分，
 * 其他字符为另一部分，再将固定字符与其他字符进行交换，
 * 依次遍历每个字符，再进行回溯递归。
 * */

vector<string> permutation2(string s) {
    // 去重处理
    set<string> res;
    backtrack2(s, 0, res);
    
    return vector<string>(res.begin(), res.end());
}

/*
 * 回溯函数
 * 使用set函数对字符串字符进行去重，
 * 使用swap函数交换两个字符
 * */
void backtrack2(string s, int start, set<string> &res) {
    // 回溯结束条件
    if(start == s.size()){
        res.insert(s);
        return;
    }
    
    for(int i = start; i < s.size(); i++){
        // 做选择
        swap(s[i], s[start]);
        // 进入下一次决策树
        backtrack2(s, start+1, res);
        // 撤销选择
        swap(s[i], s[start]);
    }
}
/******************************字符串全排列问题*******************************/

#endif
