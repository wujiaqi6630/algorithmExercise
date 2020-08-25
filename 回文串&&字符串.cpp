#if WDEBUG

#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <deque>
using namespace std;
#define DIFF 0.0000001

/* 回文串
 * 字符串操作：
 * 1. 有个仅有小写字母组成，长度为n的字符串；判断字符串等价：当切仅当重拍后相同
 
 */

#include <stdio.h>
#include <map>
using namespace std;

/**************** 1. 长度为n的字符串；判断字符串等价 ****************/
//这里只能使用map
bool isSameStirng (const string& str1, const string& str2) {
    bool res = true;
    map<char,int> table1, table2;
    for (char i : str1)
        table1[i]++;
    for (char i : str2)
        table2[i]++;
    int len1 = table1.size();
    int len2 = table2.size();
    if (len1 != len2) return false;
    else {
        for (int i = 0; i < len1; ++i) {
            if (table1[i] != table2[i]) {
                res = false;
                break;
            }
        }
    }
    return res;
}
/**************** 1. 长度为n的字符串；判断字符串等价 ****************/


/**************** 1. 最长回文串409 ****************/
/**************** 最长回文串 ****************/

/**************** 2. 最长回文子串5 ****************/
/**************** 最长回子文串 ****************/

/**************** 3. 最长回文子序列516 ****************/
/**************** 最长回文子序列 ****************/

/**************** 4. 让字符串成为回文串的最少插入次数1312 ****************/
/**************** 让字符串成为回文串的最少插入次数 ****************/

/**************** 5. 分割回文串131 ****************/
/**************** 分割回文串131 ****************/

/**************** 6. 验证回文串 ****************/
//https://www.cnblogs.com/Kobe10/p/6365676.html
/**************** 验证回文串 ****************/

/************************ 1. 替换空格 (再做)************************/
/* 题目：将一个字符串中的每个空格替换成“%20”
 * 分析 ： 遍历两遍：第一遍遇到“ ” 就填充两个字符；
 * 遍历第二遍，从后往前替换
 */
string replaceSpace (string s) {
    int len1 = (int)s.length() - 1;
    if (len1 >= 0) {
        for (int i = 0; i <= len1; ++i)
            if (s[i] == ' ') s += "11";
        int len2 = (int)s.length() - 1;
        while (len1 >= 0) {
            if (s[len1] == ' ') {
                s[len2--] = '0';
                s[len2--] = '2';
                s[len2--] = '%';
                len1--;
            }
            else s[len2--] = s[len1--];
        }
    }
    return s;
}
/************************ 1. 替换空格 ************************/

/*********************** 2. 数值的整数次方(再做) *******************/
/* 题目 ： 给定double类型的浮点数base，int型整数exponent。求取base的exponent次方
 * 分析 ： 递归
 */

double myPow (double x, int n) {
    if (abs (x) < DIFF) return 0;
    if (n == -1) return (1.0 / x);
    if (n == 0) return 1;
    if (n == 1) return x;
    
    double ret = myPow(x, n >> 1);
    ret *= ret;
    if ((n & 1) != 0) ret *= x;
    return ret;
}

/*********************** 2. 数值的整数次方 *******************/

/*********************** 3. 找到第一个只出现一次的字符 *******************/
char firstUniqChar(string s) {
    int len = (int)s.length();
    if (len == 0) return ' ';
    if (len == 1) return s[0];
    else {
        unordered_map<char, int> myMap;
        for (auto i : s)  ++myMap[i];
        for (auto it = myMap.begin(); it != myMap.end(); ++it) cout << it->first << " ";
        cout <<endl;
        char ret = ' ';
        for (auto i : s) {
            if (myMap[i] == 1) {
                ret = i;
                break;
            }
        }
        return ret;
    }
}
/*********************** 3. 找到第一个只出现一次的字符 *******************/

/********************** 4. 左旋转字符串 ************************/
/* 题目：字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。
 */
//如果允许辅助空间，则O(n)
//不允许辅助空间：三次反转：前半部分反转，后半部分反转，整体反转
void reverse (string& s, int l, int r) {
    while (l < r) {
        swap (s[l], s[r]);
        l++;
        r--;
    }
}

string leftRotateString (string s, int k) {
    int len = (int)s.length();
    if (len < 2) return s;
    else {
        reverse (s, 0, k-1);
        reverse (s, k, len-1);
        reverse (s, 0, len-1);
        return s;
    }
}
//4.2反转单词序列 ： “student. a am I” -> "I ma a ，tenduts" -> I am a student.
// 分析 ： 反转整体，在逐个反转
string reverseWord (string s) {
    int len = (int)s.length();
    if (len < 2) return s;
    else {
        reverse (s, 0, len-1);
        int start = 0, end = 0;
        while (end <= len-1 && start <= len-1) {
            while (end < len && s[end] != ' ' ) end++;
            reverse (s, start, end-1);
            start = end + 1;
            end = start;
        }
        //reverse (s, start, len-1);
        return s;
    }
}
/********************** 4. 左旋转字符串 ************************/

/********************** 5. 字符串转换成数字(再做) ********************/
//题目：允许开头空格，+，-，最长有效连续数字字符，在INT有效范围内
//分析 ： 去除开头空格，允许开头连续是0的情况
//去除开头连续空字符
void spaceFilter (string& s) {
    int len = (int) s.length();
    if (len > 0) {
        int start = 0;
        while (start < len && s[start] == ' ') start++;
        s = s.substr (start, len-start);
    }
}

//变换核心函数
long long myAtoiCore (string s, long long res) {
    int len = int (s.length());
    if (len == 0 || res >= pow(2,31) ) return res;
    else {
        if (s[0] >= '0' && s[0] <= '9') {
            res = res * 10 + (s[0] - '0');
            res = myAtoiCore(s.substr(1, len-1), res);
        }
        
        return res;
    }
}


int myAtoi(string str) {
    int len = (int) str.length();
    if (len == 0) return 0;
    else {
        //去除开头连续空字符
        spaceFilter (str);
        char first = str[0];
        long long res = 0;
        if (first == '+' || first == '-') res = myAtoiCore (str.substr (1, len-1), res);
        else if (first >= '0' && first <= '9') res = myAtoiCore (str, res);
        
        //考虑正负号
        if (first == '-') {
            if (res >= pow(2,31)) res = pow (2,31);
            res *= -1;
        }
        if (res >= (pow(2,31)-1) ) res = pow (2,31)-1;
        
        return int(res);
    }
}
/********************** 5. 字符串转换成数字 ********************/

/********************** 6.字符数组的编码方法 ********************/
int countCodingNums (const string& s) {
    int len = int (s.length());
    if (len == 0) return 0;
    else {
        if (s[0] == '0') return 0;
        int ppre = 1, pre = 1, cur = 1;
        for (int i = 1; i < len; ++i) {
            assert (s[i] >= '0' && s[i] <= '9');
            if (s[i] == '0') {
                if (s[i-1] == '1' || s[i-1] == '2') {cur = pre; ppre = pre; pre = cur; }
                else {cur = 0; break;}
            }
            else if (s[i] >= '1' && s[i] <= '6') {
                if (s[i-1] == '1' || s[i-1] == '2') {cur = pre+ppre; ppre = pre; pre = cur; }
                else {cur = pre; ppre = pre; pre = cur; }
            }
            else {
                if (s[i-1] == '1' ) {cur = pre+ppre; ppre = pre; pre = cur; }
                else {cur = pre; ppre = pre; pre = cur; }
            }
        }
        return cur;
    }
}
/********************** 6.字符数组的编码方法 ********************/

/********************** 7.正则匹配 ********************/
bool isMatchCore (const string& s, const string& p, int ss, int ps) {
    if (ss == int(s.size()) && ps == int(p.size())) return true;
    if (ss != int(s.size()) && ps == int(p.size())) return false;
    
    if (ss < int(s.size()) && (p[ps] == '.' || p[ps] == s[ss] )) {
        if (ps+1 < int(p.size()) && p[ps+1] == '*') {
            return isMatchCore(s, p, ss, ps+2) ||
            isMatchCore(s, p, ss+1, ps);
        }
        else
            return isMatchCore(s, p,  ss+1, ps+1);
    }
    else if (ps+1 < int(p.size()) && p[ps+1] == '*') return isMatchCore(s, p, ss, ps+2);
    
    return false;
}

bool isMatch (const string& str, const string& pattern) {
    int strStart = 0, patternStart = 0;
    return isMatchCore (str, pattern, strStart, patternStart);
}
/********************** 7.正则匹配 ********************/

/********************** 8.表示数值的字符串 ********************/
//给定一个字符串，判断是否可表示为数值
// +100， 5e2 , -123,  3.1412, -2e-13  都符合
// +-2，  1a23,  1.2.3,  12e+3
// 分析 ：整体 [0-9, e, -, +, .]
// 1{+/-} 2{整数} 3{.}  4{整数} 5{e/E }  6{+/-}  7{整数，不能带有小数点}
//-12.34e+23
//unordered_set<char> pivotSet{'0','1','2','3','4','5','6','7','8','9','+','-','.','e','E'};

bool scanUnsignedInteger (const string& s, int& i) {
    int start = i;
    while (i < int(s.size()) && s[i] >= '0' && s[i] <= '9') i++;
    return (start != i);
}

bool scanInteger (const string& s, int& i) {
    if (s[i] == '+' || s[i] == '-') i++;
    return scanUnsignedInteger (s, i);
}

bool isNumber(const string& s) {
    int  len = int (s.length());
    if (len == 0) return 0;
    int i = 0;
    //表示整数部分（含正负号）
    bool numric = false;
    numric = scanInteger (s, i);    //表示一开始有没有整数部分（包涵正负整数），没有整数部分返回false
    if (i < len && s[i] == '.') {
        i++;
        // 12. == 12.0   合法的表示
        // .12  == 0.12  合法的表示
        numric = scanUnsignedInteger (s, i) || numric;    //表示小数点前有有没有整数部分都可以
    }
    if (i < len && (s[i] == 'e' || s[i] == 'E')) {
        i++;
        //e前面必须有数字（整数小数都行）
        //e的后面必须有整数部分
        numric = numric && scanInteger (s, i);
    }
    
    return numric && (i == len);
}
/********************** 8.表示数值的字符串 ********************/

/********************** 9.1到n中1的个数 ********************/
//1-13中包含1的数字有1、10、11、12、13因此共出现6次,
/* 分析 ：方法一 : 对每一个数字进行判断，对10求余，然后整除10，时间复杂度是O(nLogk)
 */
/********************** 9.1到n中1的个数(再做) ********************/
// 方法二 ：
/* 分析 ： 对数字n进行逐位判断 ：
 * 对于个位来说 ： 每隔10个数字才出现一次1 ： 1，11，21.。。
 * 对于十位来说 ： 每隔100个数字才出现10个1 ： 10-19
 * 对于百位来说 ： 每隔1000个数字才出现100个1 ： 100-199
 * 符号约定 ：
 *    当前数字 ： pre = pre /10; 初始值为n
 *    权重weight，用于表示个位，十位，百位 ： weight *= 10;  初始值为1
 *    当前数字的“个位” ： base = cur % 10
 *    当前判断位置weight之前的数字pre :  比如123，pre=23, 1234,pre=234
 * 考虑不整除情况 ：
 * 采用不断整除10，来循环判断，对于每轮判断中的“个位” ：
 * base == 0 ：表示整除 ： count += cur * weight;   比如说 ： 1021，百位上出现1个个数是 1*100=100
 * base == 1 : count += cur * weight + pre + 1    比如说 ： 3121，百位上出现1个个数是 3*100 + 21 + 1 =322
 * base > 1 : count += cur * weight + weight      比如说 ： 3221，百位上出现1个个数是 3*100 + 100 = 400
 */
int countOneNums (int n) {
    if (n <= 9) return 1;
    int weight = 1;  // weight = 1,10,100表示位置权重
    int cur = n;     //对数据每次整除10，cur表示当前数字
    int base = 0;     // base 表示当前数字的个位数据
    int pre = 0;      // pre表示之前数据权重位置后面的数字，对123来说，pre = 23
    
    int count = 0;
    //从个位开始，逐个位进行判断
    while (cur != 0) {
        base = cur % 10;
        cur /= 10;
        pre = n % weight;
        
        if (base == 0) count += weight * cur;
        if (base == 1) count += weight * cur + pre + 1;
        if (base > 1) count += weight * cur + weight;
        
        weight *= 10;
    }
    return count;
}
/********************** 11.和为S的连续正数序列 ********************/
//题目 ： 输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序。
// 比如 输入 ： s = 100 输出 {{9,10,11,12,13,14,15,16},  {18,19,20,21,22}}
/* 分析 ： 暴力解决 ： 两层循环
 
 /********************** 和为S的连续正数序列 ********************/
/* 分析 ： 使用双指针，分别指向前两个位置，依次向右滑动，sum = (l+r)(r-l+1)/2
 * sum < tar : r++;  sum > tar : l++
 * 找到之后，l++,继续下一个寻找
 * 结束条件 ： l >= r || l > n/2
 */
vector<vector<int>> findContinuousSequence(int target) {
    vector<vector<int>> res;
    if (target > 2) {
        int l = 1, r = 2;
        vector<int> tmp;
        while (l < r && l <= target/2) {
            int sum = (l+r)*(r-l+1)/2;
            if (sum == target) {
                tmp.clear();
                for (int i = l; i <= r; ++i) tmp.emplace_back(i);
                res.emplace_back(tmp);
                l++;
            }
            else if (sum < target) r++;
            else l++;
        }
    }
    return res;
}
/********************** 12.数据流的中位数 ********************/
//寻找数据流中的中位数，如果从数据流中读取的元素个数是奇数个，则中位数是中间的数值；如果是偶数个，则中位数是中间两个数的平均值。
/* 分析 ：寻找数据流的中位数需要分别实现接收个返回两个函数
 * 方法一： 使用数据： 接收：可以使用插入排序，时间复杂度为O(n)，返回：时间复杂度为O(1)
 *          也可以直接接收，在返回的石斛使用partition,时间复杂度为O(n)
 * 方法三 ： 使用堆接收，插入最大/最小堆时间复杂度为O(logn)，返回时间复杂度为O(1)
 */
//方法一：
class MedianFinder {
private:
    vector<int> vec;
    int len;
public:
    MedianFinder():len(0) {}
    void addNum (int num) {
        if (len == 0) {
            vec.emplace_back(num);
            len++;
        }
        else {
            int pos = -1;
            for (int i = 0; i < len; ++i) {
                if (num < vec[i]) {
                    pos = i;
                    break;
                }
            }
            if (pos == -1)  {
                vec.push_back(num);
                len++;
            }
            else {
                vec.push_back(0);
                len++;
                for (int i = len-1; i > pos; --i) vec[i] = vec[i-1];
                vec[pos] = num;
            }
        }
    }
    
    double findMedian () {
        if (len % 2 == 1) return double (vec[len/2]);
        else return (double (vec[len/2]) + double (vec[len/2-1]))/2.0;
    }
};
//时间复杂度 ： O(n) + O(n) + O(1) 1476ms
//方法二 使用快拍
class MedianFinder1 {
private:
    vector<int> vec;
    int len;
public:
    /** initialize your data structure here. */
    MedianFinder1() {
        len = 0;
    }
    
    void addNum(int num) {
        vec.emplace_back(num);
        len++;
    }
    
    int partition (vector<int>& vec, int left, int right) {
        assert (left <= right);
        int l = left, r = right;
        int pivot = vec[l];
        while (l < r) {
            while (l < r && pivot < vec[r]) r--;
            if (l < r) vec[l++] = vec[r];
            while (l < r && pivot > vec[l]) l++;
            if (l < r) vec[r--] = vec[l];
        }
        vec[l] = pivot;
        return l;
    }
    
    int findTopK (vector<int>& vec, int k) {
        int index = partition (vec, 0, (int)vec.size()-1);
        while (k != index) {
            if (k < index) index = partition (vec, 0, index-1);
            else if (k > index) index = partition (vec, index+1, len-1);
        }
        return vec[k];
    }
    
    
    double findMedian() {
        assert (len > 0);
        int m = findTopK(vec, len/2);
        if (len % 2 == 0) {
            int n = findTopK (vec, len/2-1);
            return (double) (m+n)/2;
        }
        return double(m);
    }
};
//效果特别差！！！
//方法3: 使用大顶堆小顶堆
/* 当是第奇数个元素，插入到大顶堆，偶数个元素插入到小顶堆，且大顶堆的最大数 小于 小顶堆的最小数字
 * 这样就能保证当总数是奇数时候使用大顶堆的最大值，总是是偶数的时候使用大顶堆的最大值和小顶堆的最小值求平均值
 * make_heap(v.begin(),v.end(),less<int>())  （默认是大顶堆）或者lambda函数(a<b,是大顶堆！！！！！)。 时间复杂度是O(n)
 只有已经是堆了，才可以用下面两个算法
 * push_heap(v.begin(),v.end(),less<int>())  像堆中插入元素 ，时间复杂度为O(logn)
 * pop_heap (v.begin(),v.end(),less<int>())  弹出堆顶元素 时间复杂度为O(2logn)
 * sort_heap(v.begin(),v.end(),less<int>())  默认是将序排序 时间复杂度为O(nlogn)
 */
class MedianFinder2 {
private:
    vector<int> max;   //不可以使用deque
    vector<int> min;
    int len;
public:
    /** initialize your data structure here. */
    MedianFinder2() {
        len = 0;
    }
    
    void addNum(int num) {
        len++;
        //奇数时候，该插进最大堆
        if (len%2==1) {
            //如果发现要插入的值比最小堆的最小值要大，则插入到最小堆，然后从最小堆找到一个最小值放进最大堆
            if (min.size() > 0 && num > min[0]) {
                //先推进最小堆
                min.emplace_back(num);
                //最小堆调整
                push_heap(min.begin(), min.end(), [](const int& a, const int& b){return a>b;});
                num = min[0];
                //将最小值弹出
                pop_heap(min.begin(), min.end(), [](const int& a, const int& b){return a>b;});
                min.pop_back();
            }
            max.emplace_back(num);
            push_heap(max.begin(), max.end(), [](const int& a, const int& b){return a<b;});
            
        }
        else {
            if (max.size() > 0 && num < max[0]) {
                max.emplace_back(num);
                push_heap(max.begin(), max.end(), [](const int& a, const int& b){return a<b;});
                num = max[0];
                pop_heap(max.begin(), max.end(), [](const int& a, const int& b){return a<b;});
                max.pop_back();
            }
            min.emplace_back(num);
            push_heap(min.begin(), min.end(), [](const int& a, const int& b){return a>b;});
        }
    }
    
    double findMedian() {
        assert (len > 0);
        if (len%2==1) return (double)max[0];
        else return (double (max[0]) + double(min[0]))/2;
    }
};

/********************** 数据流的中位数 ********************/

/********************** 13. 扑克牌顺子 ********************/
/* 题目 ： 一副扑克牌，有两个大王，两个小王，可以替代任意数字，其中A代表1，J代表11，Q代表12，K代表13
 * 为方便，可以将大王小王看成0，可以替代任意数字
 * 输入一组数字，判断是否是顺子，比如 {0,0,1,3,5}就是true
 */
/* 分析 ：统计0的个数，还有空缺的个数，先排序？
 * 限制条件 ： 最多空缺不能超过4， 出现对子，则直接输出false
 */
bool isSolution (vector<int> vec) {
    int len = (int)vec.size();
    if (len == 0) return false;
    if (len == 1) return true;
    for (auto i : vec) {
        if (i < 0 || i > 13) {
            throw invalid_argument("Invalid");
        }
    }
    
    sort (vec.begin(), vec.end(), [](const int& a, const int& b) {return a < b;});
    
    int zeroNums = 0, holeNums = 0;
    int i = 0;
    while (i < len && vec[i] == 0) {
        zeroNums++;
        i++;
    }
    i = 1;
    while (i < len) {
        if (vec[i-1] == 0) {i++; continue;}
        if (vec[i-1] == vec[i]) return false;
        holeNums += vec[i]-vec[i-1]-1;
        i++;
    }
    if (zeroNums <= 4 && holeNums <= zeroNums ) return true;
    return false;
}
/********************** 扑克牌顺子 ********************/


/********************** 14.骰子点数 ********************/
/********************** 骰子点数 ********************/
/* n个骰子，点数之和为s，求出s所有可能值的概率分布值
 * n个骰子，点数之和在[n,6*n]范围
 * 骰子可能出现6^n种情况
 * 如果n==2: 则骰子可能会出现[2,12]种情况，定义数组dp2[12-2+1],dp[0]表示点数之和为2的概率，dp2[1]表示点数之和为3的概率
 * 用pa[6],pb[6]分别表示骰子a和骰子b的概率数组，都是1/6，pa[0]表示点数是1的概率
 * 比如dp[2] = pa[0]*pb[2]+pa[1]*pb[1]+pa[2]*pb[0]
 * 则dp[i+j] = sum (pa[i]*pb[j]),其中i,j>=0, i <6
 * 同样的，对于n个骰子 ： dpn[i+j] = sum(p(n-1)[i]*pa[j]),  其中j>=0;j<6;  i>=0; i<5*n+1
 */
int N = 6;
vector<double> twoSum (int n) {
    if (n < 1) throw invalid_argument("Invalid input.");
    
    double base = double(1) / double(N);
    vector<double> cur(N, base);
    if (n == 1) return cur;
    
    vector<double> res(n*(N-1)+1, 0);
    vector<double> pre(n*(N-1)+1, base);
    
    //k层控制骰子个数
    for (int k = 1; k < n; ++k) {
        if (k != 1) {
            for (int i = 0; i < (N-1)*k+1; ++i) {
                pre[i] = res[i];
                res[i] = 0.0;
            }
        }
        //i层控制n-1个骰子的概率数组
        for (int i = 0; i < (N-1)*k+1; ++i) {
            //j层控制一个骰子的概率数组
            for (int j = 0; j < N; ++j) {
                res[i+j] += pre[i] * cur[j];
            }
        }
    }
    return res;
}
/********************** 15.丑数 ********************/
/* 分解因子都是2，3，5组成，称为丑数，习惯上1作为第一个丑数，求取第N个丑数
 * 可以遍历每个数字进行判断，时间复杂度为>O(n)
 * 丑数一定是由2，3，5这些因子相乘得到的，可以按序相乘, 初始化一个数组{1},则下一个丑数一定是从当前数组里*2，*3，*5得到的
 * 关键是如何保证数组是有序的增长。
 * 每次添加一个元素进去，每次保存下标i2,i3,i5,这个元素这一轮相乘中最小的结果
 */
int nthUglyNumber(int n) {
    vector<int> vec{1};
    int i2 = 0, i3 = 0, i5 = 0;
    int next2, next3, next5, next;
    while (vec.size() <= n) {
        next2 = vec[i2]*2;
        next3 = vec[i3]*3;
        next5 = vec[i5]*5;
        
        next = min (next2, min (next3, next5));
        if (next == next2) i2++;
        if (next == next3) i3++;   // 这里b不能使用if else 结构，会出现重复元素！！！！
        if (next == next5) i5++;
        
        vec.emplace_back(next);
    }
    return vec[n-1];
}
/********************** 15.丑数 ********************/

/**************** 最长不重复子串 **************/
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> windows_map;
    int maxV = 0;
    int start = 0, end = 0;
    
    while (start <= end && end < s.length()) {
        if (windows_map.count(s[end]) != 0) {
            start = max (windows_map[s[end]]+1, start);  //好好琢磨，这部很重要！！！！不是start+1
        }
        
        windows_map[s[end]] = end;
        end++;
        maxV = max (maxV, end-start);   //插入不要总想着使用insert！！,可以使用map[k]=v,有重复会覆盖掉，没有重复就添加！！
    }
    return maxV;
}
/**************** 最长不重复子串 **************/

/**************** 1. 最长回文串409 ****************/
/* 输入:"abccccdd"输出: 7
 解释:我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
 */
int longestPalindrome1(string s) {
    int len = int (s.size());
    int ret = 0;
    bool flag = false;
    if (len > 0) {
        unordered_map<char, int> mmap;
        for (char c : s) {
            if (mmap.find(c) != mmap.end()) mmap[c]++;
            else mmap[c] = 1;
        }
        for (auto it = mmap.begin(); it != mmap.end(); ++it) {
            if (it->second % 2 == 0) ret += it->second;
            else {
                ret += it->second-1;
                flag = true;
            }
        }
    }
    return flag ? (ret+1) : ret;
}
/**************** 最长回文串 ****************/

/**************** 2. 最长回文子串5 ****************/
/* 动态规划 解决回文串问题 ： 一个字符串是回文串有三种情况 ：
 * len == 1 ;
 * len == 2 && s[i] == s[j]
 * len > 2 && s[i] == s[j] && dp[i+1][j-1]
 * 使用dp[i][j]表示从字符i到字符j是否为回文串，布尔矩阵
 *
 */
string longestPalindrome(string s) {
    int len = int (s.length());
    if (len <= 1) return s;
    int maxV = 1;
    int start = 0, end = 0;
    vector<vector<bool>> dp(len,vector<bool>(len));
    
    for (int i = 0; i < len; ++i) {
        dp[i][i] = true;
        for (int j = 0; j < i; ++j) {
            dp[j][i] = (s[i] == s[j]) && ((i-j == 1) || (i-j > 1 && dp[j+1][i-1]));
            if (dp[j][i] && (i-j+1 > maxV)) {
                maxV = i-j+1;
                start = j;
                end = i;
            }
        }
    }
    return s.substr(start,(end-start+1));
}
/**************** 最长回子文串 ****************/

/**************** 3. 最长回文子序列516 ****************/
/* "bbbab" 输出4，一个可能的最长回文子序列为 "bbbb"。
 * 回文串的特性就是：正过来反过来都一样；
 * 但是这里面可能不是连续的，因此就是其与其逆序列的最长公共子序列
 * 求两个字符串的最长公共子序列问题 ： 动态规划
 * dp[i][j] 表示s1从0-i字符，和 s2 从0- j字符的最长公共子序列的长度
 */
/*两个串的最长公共子序列问题*/
int longestPalindromeSubseq(string s) {
    int len = int (s.length());
    if (len == 0) return 0;
    string reverseStr = s;
    reverse(s.begin(), s.end());
    cout << "s : " << s << endl;
    cout << "reverse s is : " << reverseStr << endl;
    
    vector<int> tmp(len+1,0);
    vector<vector<int>> dp((len+1),tmp);
    
    for (int i = 1; i <= len; ++i) {
        for (int j = 1; j <= len; ++j) {
            if (s[i-1] == reverseStr[j-1]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max (dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[len][len];
}
/**************** 最长回文子序列 ****************/

/**************** 4. 让字符串成为回文串的最少插入次数1312 ****************/
//和上一道题目一样的，用字符串长度减去最长回文子序列的长度就是，最少插入次数
/**************** 让字符串成为回文串的最少插入次数 ****************/

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


/**************** main ****************/
int main () {
    string str1 = "wujiaqi";
    string str2 = "jiaqiwu";
    if (isSameStirng (str1, str2)) cout << "YES!" <<end;
    else cout << "NO!" << endl;
}
/**************** main ****************/
#endif
