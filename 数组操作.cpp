#if WDEBUG

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <deque>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define ElemType int
struct BinaryTreeNode {
    struct BinaryTreeNode* lc;
    struct BinaryTreeNode* rc;
    struct BinaryTreeNode* par;
    ElemType data;
    BinaryTreeNode() {}
    BinaryTreeNode(ElemType val):data(val),lc(nullptr),rc(nullptr) {}
};

/***************************** 2. 二维数组查找 *******************************/
/* 题目： 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 * 分析 ： 每次判断这个二维数组的右上角数据和目标数据进行比较：
 *      如果 tar > cur : 则 c--,r--
 *      否则 r++ c++;
 */
bool isExistTarNum (int** matrix, int rows, int cols, int tar) {
    if (matrix == nullptr || rows == 0 || cols == 0) return false;
    else {
        //需要注意的几个点：第一是一层循环！！
        //第二：不能使用在for循环中不能使用c++,r++，因为循环体中有！！
        //第三： 注意初始值，因为是右上角数据
        for (int r = 0, c = cols-1; r < rows && c >= 0;) {
            if (matrix[r][c] == tar) return true;
            else if (tar > matrix[r][c]) r++;
            else c--;
        }
        return false;
    }
}
/***************************** 2. 二维数组查找 *******************************/

/***************************** 3. 旋转数组最小数字 *******************************/
/* 题目：例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
 * 分析： 遍历一遍肯定能找到，没有意义，看见有序查找，就要想到二分查找
 * 二分查找过程中，判断cur > next ?  错误！！！
 */
//标准二分查找，都是下标操作，不用考虑越界问题
int searchBinary (vector<int> nums, int tar) {
    int len = (int)nums.size();
    int l = 0, r = len-1;
    while (l < r) {
        int m = l + ((r-l) >> 1);
        if (nums[m] == tar) return m;
        else if (nums[m] < tar) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
//寻找旋转数字的最小数字
/* 二分查找：if nums[m] > nums[r] , 则最小数字一定在右侧， l = m + 1;
 *          if nums[m] < nums[r], 则最小数字一定不在右侧，但是m有可能是最小： r = m;
 *          if nums[m] = nums[r], r--; 向前移动一位，重新判断
 */
int findMinNum (int* nums, int len) {
    if (len == 0) return 0;
    else {
        int l = 0, r = len - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] > nums[r]) l = m + 1;
            else if (nums[m] > nums[r]) r = m ;
            else r--;
        }
        return nums[l];
    }
}
/***************************** 3. 旋转数组最小数字 *******************************/

/***************************** 4. 调整数组使得奇数位于偶数之前 *******************************/
/* 双指针，头尾开始，遇到就交换*/
void exchange(vector<int>& nums) {
    int len = (int)nums.size();
    if (len >= 2) {
        int p = 0, q = len - 1;
        while (p < q) {
            if ((nums[p] & 1) == 1) p++;
            else {
                // 注意 &作为 与运算时候，优先级是低于 == 的
                while (p < q && ((nums[q] & 1) == 0)) q--;
                if (p >= q) break;
                else swap (nums[p], nums[q]);
                p++;q--;
            }
        }
    }
}
/***************************** 4. 调整数组使得奇数位于偶数之前 *******************************/

/***************************** 5. 顺时针打印矩阵 *******************************/
//输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
//输出：[1,2,3,4,8,12,11,10,9,5,6,7]
void spiralOrdeCore (vector<vector<int>>& matrix, int begin_r, int end_r, int begin_c, int end_c, vector<int>& ret)    {
    for (int i = begin_c; i <= end_c; ++i) ret.push_back (matrix[begin_r][i]);
    for (int i = begin_r+1; i <= end_r; ++i) ret.push_back (matrix[i][end_c]);
    if (end_r > begin_r)
        for (int i = end_c - 1; i >= begin_c; --i) ret.push_back (matrix[end_r][i]);
    if (end_c > begin_c)
        for (int i = end_r-1; i >= begin_r+1; --i) ret.push_back (matrix[i][begin_c]);
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ret;
    int rows = (int)matrix.size();
    if (rows != 0) {
        int cols = (int) (matrix[0].size());
        int begin_r = 0; int end_r = rows-1; int begin_c = 0; int end_c = cols-1;
        while (begin_r <= end_r && begin_c <= end_c) {
            spiralOrdeCore (matrix, begin_r, end_r, begin_c, end_c, ret);
            begin_r++ ;  end_r--;  begin_c++;  end_c--;
        }
    }
    return ret;
}
/***************************** 5. 顺时针打印矩阵 *******************************/


/***************************** 6. 获取数组中前k大的数字，要求时间复杂度为O(n)**************************/
//方法一：partition  在允许修改原来数组的情况下：
int partition (vector<int>& nums, int left, int right) {
    int axis = -1;
    if (left < right) {
        int l = left, r = right;
        int pivot = nums[l];
        while (l < r) {
            while (l < r && pivot < nums[r]) r--;
            if (l < r) nums[l++] = nums[r];
            while (l < r && pivot > nums[l]) l++;
            if (l < r) nums[r--] = nums[l];
        }
        nums[l] = pivot;
        axis = l;
    }
    return axis;
}

vector<int> findKtopNum (vector<int> nums, int k) {
    int left = 0, right = nums.size()-1;
    int axis = partition(nums, left, right);
    
    while (axis != k-1) {
        if (axis < k-1) axis = partition(nums, axis+1, right);
        if (axis > k-1) axis = partition(nums, left, axis-1);
    }
    vector<int> ret;
    for (int i = 0; i < axis; ++i) {
        ret.push_back(nums[i]);
    }
    return ret;
}

//方法二：在不修改原来数据的海量数据情况下，使用STL 容器实现 O(nlogk)
/* 思路：选择一个容器，容量为k，遍历整个数组，i<k时直接放进容器，大于k时候：
 * 每次从容器中选出最大值max, if max > nums[i] ,则删除、交换
 * 复杂度分析： 使用set容器： 每次查找、删除、插入都是logk
 */
vector<int> findTOPKnums (vector<int> nums, int k) {
    vector<int> ret;
    int len = (int) nums.size();
    if (k < 1 || len < k) return ret;
    else {
        set<int> kset;
        
        for (int i = 0; i < k; ++i) kset.insert(nums[i]);
        for (int i = k; i < len; ++i) {
            set<int>::reverse_iterator it = kset.rbegin();
            if (*it > nums[i]) {
                kset.erase(*it);
                kset.insert(nums[i]);
            }
        }
        
        for (auto it = kset.begin(); it != kset.end(); ++it)
            ret.push_back(*it);
        return ret;
    }
}
/***************************** 获取数组中第k大的数字，要求时间复杂度为O(n)**************************/

/***************************** 7. 数组中次数超过一半次数的数字 ***********************/
/* 输入如下所示的一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
 * 方法一：hash存储
 */
int findRepeatNums (vector<int> nums) {
    int len = (int) nums.size();
    if (len == 0) throw invalid_argument("Invalid");
    else {
        unordered_map<int, int> repeat_map;
        
        for (int i = 0; i < len; ++i) {
            if (repeat_map.count(nums[i]) != 0) repeat_map[nums[i]]++ ;
            else repeat_map.insert(make_pair(nums[i],1));
        }
        
        for (auto it = repeat_map.begin(); it != repeat_map.end(); ++it) {
            cout << it->first << " , " << it->second << endl;
            if (it->second > (len/2)) return it->first;
        }
        return 0;
    }
}
// 方法二： 在允许修改原数组的情况下，且前提一定是存在一个元素占用一半元素以上！基于partition， 如果 axis = len/2, 则是超过一半的数字
int findRepeatNums1 (vector<int> nums) {
    int len = (int) nums.size();
    if (len == 0) throw invalid_argument("Invalid");
    else {
        int l = 0, r = len-1;
        int axis = partition(nums, l, r);
        
        while (axis != len/2) {
            if (axis > len/2) partition(nums, l, axis-1);
            if (axis < len/2) partition(nums, axis+1, r);
        }
        
        return nums[axis];
    }
}

//方法三： 不容易想起来：
// 分析 ： 设计一个pre = nums[0]， 一个 times = 1
// 从1开始遍历 : if pre == nums[i] times ++;
// else times--; if times == 0 pre = nums[i]
int findRepeatNums2 (vector<int> nums) {
    int len = (int) nums.size();
    if (len == 0) throw invalid_argument("Invalid");
    else {
        int pre = nums[0];
        int times = 1;
        
        for (int i = 1; i < len; ++i) {
            if (times == 0) pre = nums[i];
            else {
                if (nums[i] == pre) times++;
                else times--;
            }
        }
        
        return pre;
    }
}
/*****************************  数组中次数超过一半次数的数字 ***********************/

/***************************** 8.  连续子数组之和 ***********************/
//分析 ： 连续问题，当前元素必须考虑
int findMaxSumInArray (vector<int> nums) {
    int len = (int)nums.size();
    if (len > 0) {
        int maxV = nums[0], cur = nums[0];
        
        for (int i = 1; i < len; ++i) {
            cur = max (nums[i], nums[i]+cur);
            maxV = max (maxV, cur);
        }
        
        return maxV;
    }
    else throw invalid_argument("Invalid params.");
}
/*****************************  连续子数组之和 ***********************/

/***************************** 9. 把数组排成最小的数 *****************************/
// string和数值转换    转换类型
// string str = to_string(val)    把val转换成string
// stoi(s,p,b)    把字符串s从p开始转换成b进制的int
/* 用stringstream即可把多种数值类型转换为String类型的字符串
 * include <sstream>
 * double a = 123.32;
 * string res;
 * stringstream ss;
 * ss << a;
 * ss >> res;//或者 res = ss.str();
 */
int compare (const string& a, const string& b) {
    return a+b < b+a;
}

string minNumber(vector<int>& nums) {
    //把数组转化成字符串，将字符串数组进行排序
    int len = (int) nums.size();
    string ret = "";
    if (len > 0) {
        vector<string> strVec;
        for (auto i : nums)
            strVec.push_back(to_string(i));
        
        //sort(strVec.begin(), strVec.end(), [](const string& a,const string& b){return a+b < b+a;});
        sort (strVec.begin(), strVec.end(), compare);
        
        for (auto i : strVec)
            ret += i;
    }
    return ret;
}
/***************************** 把数组排成最小的数 *****************************/

/***************************** 10. 数组中逆序对 *****************************/
int merge (vector<int>& nums, int left, int mid, int right) {
    int len = right-left+1;
    vector<int> tmp(len);
    int l = left, r = mid+1, k = 0;
    int count = 0;
    while (l <= mid && r <= right) {
        if (nums[l] <= nums[r]) tmp[k++] = nums[l++];
        else {
            count += mid-l+1;
            tmp[k++] = nums[r++];
        }
    }
    while (l <= mid) tmp[k++] = nums[l++];
    while (r <= right) tmp[k++] = nums[r++];
    
    for (int i = left, k = 0; i <= right; ++i, ++k)
        nums[i] = tmp[k];
    
    return count;
}

int mergeSort (vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right-left)/2;
        return mergeSort (nums, left, mid) + mergeSort (nums, mid+1, right) +
        merge (nums, left, mid, right);
    }
    else return 0;
}

int reversePairs(vector<int>& nums) {
    int len = (int) nums.size();
    int ret = 0;
    if (len > 1) {
        int left = 0, right = len-1;
        ret = mergeSort (nums, left, right);
    }
    return ret;
}
/***************************** 数组中逆序对 *****************************/

/***************************** 11. 数字在排序数组中出现的次数 *****************************/
//题目 ： 输入排序数组{1,2,3,3,3,3,4,5}和数字3，由于数字3在该数组中出现了4次，所以函数返回4。
//看见排序数组就想到二分查找
int countNumTimes (vector<int> nums, int k) {
    int ret = 0;
    int len = (int) nums.size();
    if (len > 0) {
        int l = 1, r = len-1, start = -1;
        while (l <= r) {
            int m = l + (r-l)/2;
            if (nums[m] == k) {
                if (m-1 < l || nums[m-1] != k) {start = m; break;}
                else r = m-1;
            }
            else if (nums[m] < k) l = m+1;
            else r = m-1;
        }
        if (start == -1) throw invalid_argument("Invalid");
        
        int end = len;
        while (l <= r) {
            int m = l + (r-l)/2;
            if (nums[m] == k) {
                if (m+1 > r || nums[m+1] != k) {end = m; break;}
                else l = m+1;
            }
            else if (nums[m] < k) l = m+1;
            else r = m-1;
        }
        if (end == len || end < start) throw invalid_argument("Invalid");
        
        return end-start+1;
    }
    return ret;
}
/***************************** 11. 数字在排序数组中出现的次数 *****************************/

/***************************** 12. 数组中重复数字 *****************************/
//题目： 在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。
/*分析 ：
 * 方法一：对数组排序，然后遍历，时间复杂度为O(nlogn)
 * 方法二：存储在[0-n-1]表中，查找哪一个大于1，空间复杂度为O(n)
 * 方法三： 遍历： if nums[i] = i : i++
 *              else if nums[i] == nums[nums[i]],   则找到第一个
 *              else  swap (nums[i], nums[nums[i]]);
 */
int duplication (vector<int> nums) {
    int ret = 0;
    int len = (int) nums.size();
    if (len > 1) {
        for (int i = 0; i < len; ++i) {
            while (nums[i] != i) {
                if (nums[i] == nums[nums[i]]) {
                    ret = nums[i];
                    break;
                }
                else swap (nums[i], nums[nums[i]]);
            }
        }
    }
    return ret;
}
/***************************** 12. 数组中重复数字 *****************************/

/***************************** 13. 数组中重复数字 *****************************/
/* 题目 ： 给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1]。
   其中B中的元素B[i]=A[0] * A[1]... * A[i-1] * A[i+1]... * A[n-1]。不能使用除法。要求O(n)时间复杂度
 * 分析 ：直接求解肯定是O（n2）
 * B[i] = C[i]*D[i];    C[i] = A[0]...A[i-1];   D[i] = A[i+1]...A[n-1];
 * C[0] = 1; C[i] = C[i-1]*A[i-1];    D[len-1]=1; D[i] = D[i+1]*A[i+1]
 */
vector<int> getMultiArray (vector<int> A) {
    vector<int> ret;
    int len = (int) A.size();
    if (len > 0) {
        vector<int> C(len,1), D(len,1);
        for (int i = 1; i < len; ++i) C[i] = C[i-1] * A[i-1];
        
        for (int j = len-2; j >= 0; --j) {
            D[j] = D[j+1] * A[j+1];
            D[j] = D[j] * C[j];
        }
        D[len-1] = C[len-1];
        return D;
    }
    return ret;
}


/***************************** 1. 数组去重 *******************************/
int func (int *a, int n) {
    if (a == nullptr || n == 0) return 0;
    else {
        int count = n;
        //int* b;
        vector<int> b;
        int j = 0;
        b.push_back(a[j]);
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i-1])
                count--;
            else
                //b[++j] = a[i];
                b.push_back(a[i]);
        }
        //a = b;
        
        //对于这种特殊需求：希望在原数组上进行改变，可以使用memcpy
        //不过返回数组不是希望的{0 1 2 4},而是{0 1 2 4 2 2 4}，
        //C++不支持realloc函数，只能使用固定长度来控制
        memcpy (a, &b[0], b.size() * sizeof(int));
        return count;
    }
}
/***************************** 1. 数组去重 *******************************/

/**************** 1. 两数之和 ****************/
//返回下标
vector<int> twoSum(vector<int>& nums, int tar) {
    unordered_map<int, int> mmap;
    for (int i = 0; i < int(nums.size()); ++i) {
        if (mmap.find(tar-nums[i]) != mmap.end()) {
            return {mmap[tar-nums[i]], i};
        }
        mmap[nums[i]] = i;
    }
    return {};
}
/**************** 两数之和 ****************/

/**************** 2. 三数之和(好题目！！) ****************/
//求数组中三个元素之和等于0的所有情况，不能有重复
/* 排序后，夹逼法：外层循环，确定基准值，后面使用双指针
 */
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ret;
    int len = int (nums.size());
    if (len > 2) {
        sort(nums.begin(), nums.end(), [](const int& a, const int& b) {return a < b;});
        for (int i = 0; i < len-2; ++i) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i-1] == nums[i]) continue;
            int l = i+1, r = len-1;
            while (l < r) {
                int tmpSum = nums[l]+nums[r];
                if (tmpSum + nums[i] == 0) {
                    //必须先进，再去重，否则有可能漏掉 0 0 0 的情况
                    ret.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[r] == nums[r-1]) r--;
                    while (l < r && nums[l] == nums[l+1]) l++;
                    l++;r--;
                }
                else if (tmpSum + nums[i] < 0) l++;
                else r--;
            }
        }
    }
    return ret;
}
/**************** 三数之和 ****************/

/**************** 3. 两数相加 ****************/
/* 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 输出：7 -> 0 -> 8
 原因：342 + 465 = 807
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* res = new ListNode(-1);
    ListNode* pre = res;
    ListNode* p = l1, *q = l2;
    int carry = 0, bitSum = 0;
    while (p || q || carry != 0) {
        if (p && q) bitSum = p->val + q->val + carry;
        if (p && !q) bitSum = p->val + carry;
        if (!p && q) bitSum = q->val + carry;
        if (!p && !q) bitSum = carry;
        carry = bitSum / 10;
        bitSum %= 10;
        ListNode* node = new ListNode(bitSum);
        pre->next = node;
        pre = node;
        if (p) p = p->next;
        if (q) q = q->next;
    }
    
    //链表反转
    /*
     pre = nullptr, p = res->next, q = p->next;
     while (p) {
     p->next = pre;
     pre = p;
     p = q;
     if (p) q = p->next;
     }
     */
    return res->next;
}
/**************** 两数相加 ****************/


/**************** 5. 两个数组的交集 ****************/
/*题目一：给定两个数组，编写一个函数来计算它们的交集。输出结果中的每个元素一定是唯一的。
 输入：nums1 = [1,2,2,1], nums2 = [2,2]
 输出：[2]
 */
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ret;
    int len1 = int (nums1.size());
    int len2 = int (nums2.size());
    
    if (len1 * len2 != 0) {
        unordered_map<int, int> mmap;
        for (auto i : nums1) mmap[i] = 1;
        for (auto i : nums2) {
            if (mmap.find(i) != mmap.end() && mmap[i] != 0) {
                ret.push_back(i);
                mmap[i] = 0;
            }
        }
    }
    return ret;
}

/*题目二：
 * 输入：nums1 = [1,2,2,1], nums2 = [2,2]
 输出：[2,2]
 */
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ret;
    int len1 = int (nums1.size());
    int len2 = int (nums2.size());
    
    if (len1 * len2 != 0) {
        unordered_map<int, int> mmap;
        for (auto i : nums1) {
            if (mmap.find(i) != mmap.end()) mmap[i]++;
            mmap[i] = 1;
        }
        for (auto i : nums2) {
            if (mmap.find(i) != mmap.end() && mmap[i] != 0) {
                ret.push_back(i);
                mmap[i]--;
            }
        }
    }
    return ret;
}
/**************** 两个数组的交集 ****************/
#endif
