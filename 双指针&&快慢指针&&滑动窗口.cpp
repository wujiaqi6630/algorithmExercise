#if WDEBUG

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <iostream>

using namespace std;
//  双指针&&快慢指针.cpp

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

/********************** 字符串相乘 43********************/
string strMulti (string num1, string num2) {
    string ret = "";
    int carry = 0;
    int tmp = 0;
    string c;
    for (int i = num1.size()-1; i >= 0; --i) {
        c.clear();
        tmp = (num1[i]-'0') * (num2[0]-'0') + carry;
        carry = tmp/10;
        tmp = tmp%10;
        c.push_back(tmp+'0');
        ret = c + ret;
    }
    if (carry != 0) {
        c.clear();
        c.push_back(carry+'0');
        ret = c+ret;
    }
    return ret;
}

string strAdd (string a, string b) {
    string ret = "";
    int len1 = int (a.size())-1, len2 = int (b.size())-1;
    int len = min (len1,len2)-1;
    int carry = 0, tmp = 0;
    string c;
    
    while (len1 >= 0 && len2 >= 0) {
        c.clear();
        tmp = (a[len1]-'0') + (b[len2]-'0') + carry;
        carry = tmp/10;
        tmp = tmp%10;
        c.push_back(tmp+'0');
        ret = c + ret;
        --len1; --len2;
    }
    
    while (len1 >= 0) {
        c.clear();
        tmp = (a[len1]-'0') + carry;
        carry = tmp/10;
        tmp = tmp%10;
        c.push_back(tmp+'0');
        ret = c + ret;
        --len1;
    }
    while (len2 >= 0) {
        c.clear();
        tmp = (b[len2]-'0') + carry;
        carry = tmp/10;
        tmp = tmp%10;
        c.push_back(tmp+'0');
        ret = c + ret;
        --len2;
    }
    if (carry == 1) ret = "1" + ret;
    return ret;
}

string multiply(string num1, string num2) {
    int len1 = int(num1.size()), len2 = int(num2.size());
    if (len1 * len2 == 0) return "";
    if ((len1 == 1 && num1 == "0") || (len2 == 1 && num2 == "0")) return "0";
    int j = 0;
    string pre = "", mulStr="";
    while (j < len2) {
        mulStr = strMulti (num1, num2.substr(j,1));
        ++j;
        if (pre != "") {
            pre += "0";
            mulStr = strAdd (mulStr, pre);
        }
        pre = mulStr;
    }
    return pre;
}
/********************** 字符串相乘 43********************/

/********************** 最小覆盖子串 76********************/
/* 题目 ： 给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。
 * 输入：S = "ADOBECODEBANC", T = "ABC" 输出："BANC"
 * 前提： 如果 S 中不存这样的子串，则返回空字符串 ""。
 *       如果 S 中存在这样的子串，我们保证它是唯一的答案。
 * 分析 ：end++,直至包含所有T中元素，注意，这里的T中元素有可能是重复的， 那如何判断[start,end]是否包含了所有元素？
 * 维护一个map<char,int>,初始值是T中各字符，以及出现次数,在维护一个count，用于判断滑动窗口内的元素是否已经包含全部元素
 *      end++遍历的时候，s[end]要是在map中，map[s[end]]--,当map[s[end]] == 0,count--; 当count = 0时，说明已经包含全部元素
 *      此时再调整start++,map[s[start]]++,当map[s[start]] == 0时，说明不能调整了，此时求得一个长度
 * 继续重复上述过程
 */
string minWindow(string s, string t) {
    int len1 = int (s.size()), len2 = int(t.size());
    //有一个长度为0或者t的长度大于s的长度，直接返回
    if (len2 * len1 == 0 || len2 > len1) return "";
    unordered_map<char, int> mmap;
    for (char c : t) ++mmap[c];
    //使用count判断滑动窗口是否已经包含所有元素，t中可能有重复元素，因此不能使用count = len2
    int count = int(mmap.size());
    int start(0), end(0);
    int minLen = INT_MAX;
    string ret = "";
    
    while (end < len1) {
        //寻找满足包涵所有目标字符的[start,end]
        //这里必须加上end < len1，否则会死循环
        while (end < len1 && count != 0) {
            if (mmap.count(s[end]) != 0) {
                --mmap[s[end]];
                if (mmap[s[end]]==0) --count;
            }
            ++end;
        }
        //此时[start,end]已经包含全部目标元素
        //下面开始调整start，因为[start,end]范围内可能出现ABABC的情况
        //这里加一个if判断，主要为了避免多次对 minLen 和 ret 赋值，现在只需调整后一次赋值就行
        if (count == 0) {
            while (count == 0) {
                if (mmap.count(s[start]) != 0) {
                    ++mmap[s[start]];
                    if (mmap[s[start]] == 1) {
                        ++count;
                    }
                }
                ++start;
            }
            //调整后，现在的[start,end]范围内是满足包涵所有目标元素的最小范围，后面按照上述方法继续调整
            //此时的start和end由于start++和end++都在目标元素的后一个位置，相对长度不变
            if ((end-start+1) < minLen) {
                minLen = end-start+1;
                //这里的起始位置是start-1而不是start
                ret = s.substr(start-1, minLen);
            }
        }
    }
    return ret;
}
/********************** 最小覆盖子串 ********************/

/********************** 字符串的排列 576********************/
/* 题目 ： 给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。，第一个字符串的排列之一是第二个字符串的子串。
 * 输入：s1 = "ab" s2 = "eidbaooo" 输出：True  解释: s2 包含 s1 的排列之一 ("ba").
 * 前提： 输入的字符串只包含小写字母
 * 分析 ：
 * 上一题求包涵目标字符串的最小传，每次只把目标字符放进map中，通过调整start,end获取最小串
 * 这一题求包涵目标串的全排列，即中间不允许夹杂其他字符
 * 还是用map，每次所有字符全都放进窗口[start,end]内：当mma[i]==0表示这个字符个数正好，<0表示多了，>0表示少了
 * 字符一个个放进去，每次放一个字符都进行判断：<0,就出窗，出窗的时候++，直到这个字符==0，停止出窗
 *      这样就能保证在窗内的字符都是 >=0,
 * 结束条件 ： 窗口内的字符个数 == len1.size()
 */
bool checkInclusion(string s1, string s2) {
    int len1 = int (s1.size()), len2 = int (s2.size());
    if (len1*len2 == 0 || len1 > len2) return false;
    unordered_map<char,int> mp;
    for (auto c : s1) ++mp[c];
    int start(0), end(0);
    
    while (end < len2) {
        --mp[s2[end++]];
        while (start < end && mp[s2[end-1]] < 0) ++mp[s2[start++]];
        if (end-start == len1) return true;
    }
    return false;
}
/********************** 字符串的排列 ********************/

/********************** 找到字符串中所有字母异位词 438********************/
/* 题目 ： 给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。
 * 输入：s: "cbaebabacd" p: "abc" 输出：[0, 6]  解释: 起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
 * 分析 ：这道题目是上一道题目的变种形式
 */
vector<int> findAnagrams(string s, string p) {
    int len1 = int (s.size()), len2 = int (p.size()) ;
    if (len1*len2 == 0 || len2 > len1) return {};
    vector<int> ret;
    unordered_map<char,int> mp;
    for (auto c : p) ++mp[c];
    int start(0), end(0);
    
    while (end < len1) {
        --mp[s[end++]];
        while (start<end && mp[s[end-1]] < 0) ++mp[s[start++]];
        if (end-start == len2) ret.push_back(start);
    }
    return ret;
}
/********************** 找到字符串中所有字母异位词 ********************/

/********************** 无重复字符的最长子串 3********************/
/* 题目 ： 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 * 输入："abcabcbb" 输出：3  解
 * 分析 ：确定这个字符串中的最长不重复子串， 可以使用滑动窗口来解决， 通过起始指针来确定窗口位置
 * start指针的确定 ： max(start, index[s[end]]) : end表示当前位置，s[end]表示当前元素， index[s[end]]表示 s[end]元素 在 历史重复记录中 离 当前位置最近的那个
 * end： 顺序++
 */
int lengthOfLongestSubstring(string s) {
    int len = int (s.size());
    if (len == 0) return 0;
    //!!!!!! 这里使用int!!!而不是 char ！！！！将char转换成int作为index的下标！！！
    vector<int> index(128, 0);
    int start(0), maxLen(0);
    
    for (int i = 0; i < len; ++i) {
        start = max(start, index[s[i]]);
        //这里的+1的意思是下一次确定start的位置是这个元素的下一个位置
        index[s[i]] = i+1;
        maxLen = max (maxLen, i-start+1);
    }
    return maxLen;
}
/********************** 无重复字符的最长子串 ********************/
#endif
