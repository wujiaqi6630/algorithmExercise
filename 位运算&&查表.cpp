#if WDEBUG
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <deque>
#include <algorithm>
using namespace std;

/* 位运算特点：1表示负数，0表示正数
 * 正数在计算机中正常使用二进制表示，负数使用补码表示（反码加1）。比如
 * 3 ：00000000 00000000 00000000 00000011 转换为十六进制：0x0000000C
 * -3: 11111111 11111111 11111111 11111101 转换为十六进制：0xFFFFFFFD。好处：，所有的加法运算可以使用同一种电路完成
 * 1 ： 00000000 00000000 00000000 00000001
 * -1 ： 11111111 11111111 11111111 11111111  16进制为：0xFFFFFF
 
 * 对于8位机： 正数最大值： 0111 1111= 127； 正数最小值为 0000 0001 = 1；
 *           负数最大值： 1000 0000 = -128  d负数最小值 1111 1111= -1
 * & ： 1&1 = 1； 1&0 = 0&0 = 0；
 * ｜ ： （1 ｜ 1）  =  （1 ｜ 0 ）= 1；     0 ｜ 0 = 0；
 * ^ :  1 ^ 0 = 0 ^ 1 = 1;  1 ^ 1 = 0 ^ 0 = 0;
 *  右移>> 乘法减半：
 *          对于正数： 左侧补0， 右侧移除； 32位数据： 正数右移31位，则正数变成000..1 = 0
 *          对于负数： 左侧补1， 右侧移除； 32位数据： 负数右移31位，则正数变成111..1 = -1
 *  左移 << 2倍增长：
 *          对于正数/负数，都是左侧移除，右侧补0；
 */
/************************* 1. 不用加减乘除作 加法运算 **************************/
/* 不能使用加减乘除，则考虑位运算： 0101 + 0011，res1 = 使用^运算，res2 = 使用&运算 return res1+res2(可以使用递归实现)
 */
int add1 (int num1, int num2) {
    int carry = 0;
    while (carry != 0) {
        int sum = num1 ^ num2;
        carry = (num1 & num2)<<1;
        num1 = sum;
        num2 = carry;
    }
    return num1;
}

//递归方式：
int add2 (int num1, int num2) {
    if (num2 == 0) return num1;
    int sum = num1 ^ num2;
    int carry = (num1 & num2)<<1;
    return add2 (sum, carry);
}
/************************* 1. 不用加减乘除作 加法运算 **************************/

/************************* 2. 统计1的个数 **************************/
//方法一： 每次与1& ,然后右移，时间复杂度为O(n)
int countOne1 (int num) {
    int count = 0;
    while (num != 0) {
        if (num & 1 == 1) count++;
        num = num >> 1;
    }
    return count;
}

//方法2: 比较精巧 while (n = (n & n-1) ) count++
//解释：每次都能把n的最右面的1变成0
int countOne2 (int num) {
    int count = 0;
    while (num != 0) {
        num = num & (num -1);
        count ++;
    }
    return count;
}
/************************* 2. 统计1的个数 **************************/

/***************************** 3. 数组中只出现一次的数字 ******************************/
//一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度为O(n)，空间复杂度为O(1)。
/* 分析 ： 最简单的是将元素存储在hash标中，然后遍历判断。如果不允许使用额外空间的情况下
 * 异或两个特性： 两个相同数字抑或结果为0；   0和任何数字抑或结果都为原来数字
 */
vector<int> singleNumbers(vector<int>& nums) {
    int len = (int) nums.size();
    vector<int> ret(2);
    if (len > 1) {
        //将所有结果抑或
        int tmp = 0;
        for (int i : nums) tmp = tmp ^ i;
        
        //寻找临时结果二进制表示中从低位开始第一个为1的index
        int index = 0;
        while (index < 32) {
            if (((tmp>>index) & 1) == 1) break;
            index++;
        }
        
        //利用低位第index位置是否为1将数组分成两组
        for (auto i : nums) {
            if (((i>>index) & 1) == 1) ret[0] = ret[0] ^ i;
            else ret[1] = ret[1] ^ i;
        }
    }
    
    return ret;
}

//变形1 ： 一个数组，除了一个数字，剩下的都是成对出现，且符合 aabbc的形式，不会出现aabcb的形式，找出这个数字，要求时间复杂度小与O(n)
/* 分析 ： 两种情况： {1,1,2,2,3} {3,1,1,2,2}
 * 时间复杂度小于O（n）的一般都是O(logn)，一般都会和二分法关联
 * 若nums[m]左右数字不同，则是我们寻找目标；
 * 否则判断： 如果nums[m] == nums[m-1]，则tar一定在左面，这是因为第一的m一定是奇数位，如果前面是成对出现，则nums[m] != nums[m-1]
 */
int findSingleNum (vector<int> nums) {
    int len  = int (nums.size());
    if (len == 0) throw invalid_argument("No Numbers.");
    int l = 0, r = len-1, m=0;
    int ret = nums[0];
    while (l < r) {
        m = l + (r-l)/2;
        if (r-l > 2) {
            if (nums[m] != nums[m+1] && nums[m] != nums[m-1]) {l = m; break;}
            if (nums[m] == nums[m-1]) r = m-2;
            if (nums[m] != nums[m-1]) l = m+2;
        }
        else {
            if (nums[m] == nums[m-1]) ret = nums[m+1];
            else ret = nums[m-1];
        }
    }
    return ret;
}


//3.2 如果在一个数组中除了一个数字，每个数字出现了3次/4次？
/* 分析，将每个数字的二进制位加起来，整除3，除不尽的位，标明tar对应的位是1，否则对应的位是0
 */
int findNumberOfAppearnceTimes (vector<int> nums) {
    int ret = 0;
    int len = (int) nums.size();
    if (len > 0) {
        vector<int> bitSum(32,0);
        for (int i = 0; i < len; ++i) {
            int flag = 1;
            for (int j = 31; j >= 0; --j) {
                if ((nums[i] & flag) != 0) bitSum[j]++;
                flag = flag << 1;
            }
        }
        
        for (int i = 31; i >= 0; --i) {
            if ((bitSum[i] % 3) != 0) bitSum[i] = 1;
            else bitSum[i] = 0;
            ret += bitSum[i]*(pow(2,(31-i)));
        }
    }
    return ret;
}

/***************************** 3. 数组中只出现一次的数字 ******************************/
#endif
