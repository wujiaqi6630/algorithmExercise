#if WDUBUG
/* 链表操作
 * 1. 链表节点增加/删除
 * 2. 删除在排序的链表中重复的结点。（血泪教训）
 * 3. 从尾到头打印链表
 * 4. 删除链表中一个节点,要求时间复杂度为O(1) （新思路）
 * 5. 链表中倒数第k个节点
 * 6. 链表有序反转 （值得看）
 * 7. 两个链表合并 (好好琢磨这个递归)
 * 8. 两个链表的第一个公共节点
 * 9. 约瑟夫环
 * 10. 链表中环的入口
 * 11. 两个队列实现栈
 * 12. 包含min函数的栈
 * 13. 判断栈的压入，弹出序列
 * 14. 实现求得队列最大值函数，要求pop push max均为O(1)
 * 15. 队列中连续求和最大值
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>

using namespace std;

#define ElemType int

struct ListNode {
    struct ListNode* next;
    ElemType data;
    ListNode() {}
    ListNode(ElemType i):data(i),next(NULL) {}
};

int getSize (ListNode* head) {
    if (head == NULL) return 0;
    else {
        int size = 0;
        ListNode* p = head;
        while (p != NULL)  {
            size++;
            p = p->next;
        }
        return size;
    }
}

void printList (ListNode* head) {
    if (head != NULL) {
        ListNode* p = head;
        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    else
        cout << "NO Elements! " << endl;
}

/********** 1. 链表节点增加/删除 **********/
void addNode (ListNode* & head, ElemType val) {
    ListNode* node = new ListNode();
    node->data = val;
    node->next = NULL;
    
    if (head == NULL) {
        head = node;
    }
    else {
        ListNode* p = head;
        while (p->next != NULL) p = p->next;
        p->next = node;
    }
}
// 删除：如果是头节点，直接删除；如果是尾节点：
ListNode* deleteNode (ListNode* head, ElemType val) {
    if (head == NULL) throw invalid_argument ("NULL");
    else {
        ListNode* newHead = new ListNode(-1);
        newHead->next = head;
        ListNode* cur = newHead;
        ListNode* next = cur->next;
        ListNode* toBeDelted = NULL;
        
        while (next != NULL && next->data != val) {
            cur = next;
            next = cur->next;
        }
        
        if (next == NULL) throw invalid_argument ("NOT Exists!");
        else {
            toBeDelted = next;
            cur->next = next->next;
        }
        
        if (toBeDelted != NULL) {
            delete toBeDelted;
            toBeDelted = NULL;
        }
        return newHead->next;
    }
}
/********** 1. 链表节点增加/删除 **********/

/********** 2. 删除在排序的链表中重复的结点 **********/
//需要考虑 1，1，2，2，2，3的情况
ListNode* deleteRepeatNode (ListNode* head) {
    //当链表为空或者链表中只有一个元素的时候，返回原链表
    if (head == NULL || head->next == NULL) return head;
    //设置pre的原因：！！！！！因为cur和next都会被删除，所以应该有个不被删除的pre一直指向cur，保持链表连续
    //血泪教训！！！！必须设置新的头节点，要不然麻烦无穷！！！
    else {
        ListNode* newHead = new ListNode(-1);
        newHead->next = head;
        
        ListNode* pre = newHead;  //pre不会删除，用来代表链表的意思，保持联通性
        ListNode* cur = pre->next; // cur和next就是两个指针，不代表链表
        ListNode* next = cur->next;
        vector<ListNode*> toBeDeleted;
        
        while (next != NULL) {
            //内循环用于去除重复元素
            while (next != NULL && next->data == cur->data) {
                toBeDeleted.push_back(next);
                next = next->next;
            }
            //当前节点和下一节点的元素与不同，依次向下移动
            if (cur->next == next) {
                pre = cur;
                cur = next;
                next = cur->next;
            }
            //当前节点和下一节点的元素与相同，需要在去除cur节点
            else {
                toBeDeleted.push_back(cur);
                cur = next;
                pre->next = cur;
                //这时候，cur有可能是空，需要加判断
                if (cur != NULL)
                    next = cur->next;
                else
                    break;
            }
        }
        
        for (int i = 0; i < toBeDeleted.size(); ++i) {
            delete toBeDeleted[i];
            toBeDeleted[i] = NULL;
        }
        return newHead->next;
    }
}
/********** 2. 删除在排序的链表中重复的结点 **********/

/********** 3. 从尾到头打印链表 **********/
vector<ListNode*> printListFromBack (ListNode* head) {
    if (head == NULL) throw invalid_argument ("NON!");
    else {
        stack<ListNode*> st;
        vector<ListNode*> vec;
        ListNode* p = head;
        while (p != NULL) {
            st.push(p);
            p = p->next;
        }
        //cout << " PRINT : " << endl;
        while (!st.empty()) {
            //cout << (st.top())->data << " " ;
            ListNode* tmp = st.top();
            st.pop();
            vec.push_back(tmp);
        }
        //cout << endl;
        return vec;
    }
}
/********** 3. 从尾到头打印链表 **********/

/********** 4. 删除链表中一个节点,要求时间复杂度为O(1) **********/
//假设前提：1）要删除的节点tar肯定在链表中；
//2）tar是链表中的某个节点，即tar->next ！= NULL (如果tar不是尾元素的情况下)
/* 删除节点不是问题，关键是怎么在O(1)要求进行删除？
 * 传统做法，先遍历找到这个节点，然后删除，还是需要O(n)复杂度
 * 有一种方法不用遍历也可以：假设这个节点肯定在链表中，将后一个节点复制给目标节点，删除后一个节点即可
 * 对于尾元素，没有后一个节点，则还是需要遍历，但是时间复杂度是 (O(n)*1 + O(1)*(n-1)) / n = O(1)
 */
void deleteListInO1 (ListNode* &head, ListNode* tar) {
    if (head == NULL) return ;
    else {
        ListNode* toBeDeleted = NULL;
        ListNode* p = head;
        if (tar == head) {
            toBeDeleted = p;
            head = head->next;
        }
        else {
            if (tar->next == NULL) {
                while (p->next != tar) {
                    p = p->next;
                }
                toBeDeleted = p->next;
                p->next = NULL;
            }
            else {
                p = tar->next;
                tar->data = p->data;
                toBeDeleted = p;
                tar->next = p->next;
            }
        }
        
        if (toBeDeleted != NULL) {
            delete toBeDeleted;
            toBeDeleted = NULL;
        }
    }
}
/********** 4. 删除链表中一个节点 **********/

/********** 5. 寻找链表中倒数第k个节点 **********/
ListNode* deleteTopk (ListNode* head, int k) {
    if (head == NULL || k < 1) return NULL;
    else {
        ListNode* p = head;
        ListNode* q = head;
        int count = 1;
        while (count < k && p != NULL)  {
            p = p->next;
            count++;
        }
        if (p == NULL) throw invalid_argument("Invalid Params");
        while (p->next != NULL) {
            p = p->next;
            q = q->next;
        }
        return q;
    }
}
/********** 5. 链表中倒数第k个节点 **********/

/********** 6. 链表反转 **********/
ListNode* reverseList (ListNode* head) {
    if (head != nullptr) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* nxt = cur->next;
        
        while (cur != nullptr) {
            cur->next = pre;
            pre = cur;
            cur = nxt;
            if (cur != nullptr)
                nxt = cur->next;
            else break;
        }
        return pre;
    }
    else return nullptr;
}
//题目2 ： 部分链表反转
ListNode* reverseBetween(ListNode* head, int m, int n) {
    int reverseNum = n-m+1;   //待反转节点个数
    if (reverseNum == 1) return head;
    ListNode* pre = nullptr;  // 使用pre, cur, nxt三个指针进行部分链表反转
    ListNode* cur = head;
    ListNode* nxt = cur->next;
    ListNode* newEnd = head;   //记录下待反转的部分链表 在反转之前的开始位置，这个位置将会被作为链表反转后的尾节点，指向后面未反转的链表
    
    if (m == 1) {
        while (reverseNum != 0 && cur != nullptr) {  //操作退出时，反转链表的头节点是pre， cur指向下一个未被反转的链表，可能为空
            reverseNum--;
            cur->next = pre;
            pre = cur;
            cur = nxt;
            if (cur != nullptr) nxt = cur->next;
        }
        newEnd->next = cur;
        return pre;
    }
    else {
        ListNode* newStart = head;   //记录等待被反转链表 在反转前的 前一个节点， 反转结束后，用于指向其开始节点
        while (m > 2) {newStart = newStart->next; m--;}
        newEnd = newStart->next;
        cur = newEnd;
        nxt = cur->next;
        
        while (reverseNum != 0 && cur != nullptr) {
            reverseNum--;
            cur->next = pre;
            pre = cur;
            cur = nxt;
            if (cur != nullptr) nxt = cur->next;
        }
        newEnd->next = cur;
        newStart->next = pre;
        return head;
    }
}

/********** 6. 链表反转 **********/

/****************** 重排链表 ********************/
/* 分析 :
 * 方法一 ： 找到中间节点（双指针寻找），后半部分节点原地逆转，双指针操作进行重拍（推荐）
 * 方法二 ：  1，2，3，4，5 复制并反转
 * 保存4个指针 ： cur, nxt, newCur, 分奇偶数操作
 */
//方法一：
void reorderList(ListNode* head) {
    if (!head || !head->next || !head->next->next) return ;
    //找到中间节点：使用快慢指针，p走一步，q走两步，if q->next->next == nullptr , stop, 此时p就是中间节点，适用于奇偶数情况
    ListNode* p = head, *q = head;
    while (q->next && q->next->next) {
        p = p->next;
        q = q->next->next;
    }
    //将后半部分的节点原地反转
    ListNode* pre = nullptr,  *cur = p->next, *nxt = cur->next;
    p->next = nullptr; //将两部分分开
    
    while (cur) {
        cur->next = pre;
        pre = cur;
        cur = nxt;
        if (cur) nxt = cur->next;
    }
    q = pre;
    
    //变换指针指向，重排链表
    p = head;
    //后面链表长度小于等于前面链表长度，只用判断后面就行
    while (q) {
        nxt = q->next;
        q->next = p->next;
        p->next = q;
        p = q->next;
        q = nxt;
    }
}

//方法二：
void reorderList1(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return ;
    //复制并反转链表
    ListNode* newHead = new ListNode(head->val);
    ListNode* newPre = newHead;
    ListNode* cur = head->next;
    int listLen = 1;
    while (cur != nullptr) {
        listLen++;
        ListNode* node = new ListNode(cur->val);
        newPre->next = node;
        newPre = node;
        cur = cur->next;
    }
    //反转
    newPre = nullptr;
    ListNode* newCur = newHead;
    ListNode* newNxt = newCur->next;
    
    while (newCur != nullptr) {
        newCur->next = newPre;
        newPre = newCur;
        newCur = newNxt;
        if (newCur != nullptr) newNxt = newCur->next;
    }
    newHead = newPre;
    
    newCur = newHead; //cur指向反转后链表的头节点
    newNxt = newCur->next;
    
    //重排链表指向
    cur = head;
    ListNode* nxt = cur->next;
    
    int iterTimes = listLen/2;
    if (listLen%2 == 0) {
        iterTimes--;
    }
    while (iterTimes != 0) {
        iterTimes--;
        cur->next = newCur;
        newCur->next = nxt;
        
        cur = nxt;
        newCur = newNxt;
        nxt = cur->next;
        newNxt = newCur->next;
    }
    if (listLen%2 == 0) {
        cur->next=newCur;
        newCur->next = nullptr;
    }
    else cur->next = nullptr;
}
/****************** 重排链表 ********************/

/********** 7. 两个有序链表合并 **********/
ListNode* mergeList (ListNode* heada, ListNode* headb) {
    ListNode* node = new ListNode();
    if (heada == NULL)
        return headb;
    if (headb == NULL)
        return heada;
    else {
        if (heada->data < headb->data)  {
            node = heada;
            node->next = mergeList(heada->next, headb);
        }
        else {
            node = headb;
            node->next = mergeList(heada, headb->next);
        }
        return node;
    }
}

/**************** 合并有序数组 **************/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (n == 0) return ;
    if (m == 0) {
        for (int i = 0; i < n; ++i) nums1[i] = nums2[i];
    }
    int len = m+n-1;
    int i = m-1, j = n-1;
    while (len >= 0 && i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) nums1[len--] = nums1[i--];
        else nums1[len--] = nums2[j--];
    }
    while (j >= 0) nums1[len--] = nums2[j--];
}
/**************** 合并有序数组 **************/
/********** 7. 两个链表合并 **********/

/********** 8. 两个链表的第一个公共节点 (快慢指针) **********/
//前提假设：公共子节点之后的元素都相同
//方法一：使用两个栈
ListNode* findTraNode1 (ListNode* head1, ListNode* head2) {
    if (head1 == NULL || head2 == NULL) return NULL;
    else {
        ListNode* ret = NULL;
        stack<ListNode*> st1;
        stack<ListNode*> st2;
        ListNode* p = head1;
        ListNode* q = head2;
        while (p != NULL) {
            st1.push(p);
            p = p->next;
        }
        while (q != NULL) {
            st2.push(q);
            q = q->next;
        }
        while (!st1.empty() && !st2.empty()) {
            if ((st1.top())->data == (st2.top())->data) {
                ret = st1.top();
                st1.pop();
                st2.pop();
            }
            else break;
        }
        return ret;
    }
}

//方法二：获取长度，让长的那个先走
ListNode* findTraNode2 (ListNode* head1, ListNode* head2) {
    if (head1 == NULL || head2 == NULL) return NULL;
    else {
        ListNode* ret = NULL;
        int size1 = 0, size2 = 0;
        ListNode* p = head1;
        ListNode* q = head2;
        while (p != NULL) {
            size1++;
            p = p->next;
        }
        while (q != NULL) {
            size2++;
            q = q->next;
        }
        
        p = head1, q = head2;
        if (size1 > size2) {
            int diff = size1 - size2;
            while (diff > 0)  {
                p = p->next;
                diff--;
            }
        }
        else {
            int diff = size2 - size1;
            while (diff > 0) {
                q = q->next;
                diff--;
            }
        }
        
        while (p != NULL && q != NULL && p->data != q->data) {
            p = p->next;
            q = q->next;
        }
        if (p != NULL) ret = p;
        return p;
    }
}
/********** 8. 两个链表的第一个公共节点 **********/

/********** 9. 约瑟夫环 **********/
//圆圈中最后剩下的数字：使用0，1，  n-1这n个数字，每次从这个圆圈中删除第m个数字，求出这个圆圈里的最后一个数字
/********** 9. 约瑟夫环 **********/
//使用STL中的list实现。
int lastRemaining (int n, int m) {
    if (m < 1 || n < 1 || n < m) throw invalid_argument("INVALID");
    list<int> nums;
    for (int i = 0; i < n; ++i)
        nums.push_back(i);
    list<int>::iterator cur = nums.begin();
    while (nums.size() > 1) {
        for (int i = 1; i < m; ++i) {
            cur++;
            //如果到达尾部，则将首部迭代器赋值为cur
            if (cur == nums.end())
                cur = nums.begin();
        }
        //删除下一个节点
        list<int>::iterator next = ++cur;
        if (next == nums.end())
            next = nums.begin();
        --cur;
        nums.erase(cur);
        cur = next;
    }
    return *(cur);
}
/********** 10. 链表中环的入口 **********/
//如果一个链表中包含环，如何找出环的入口节点？
//1.p,q都指向d头节点，如果知道了环的个数n，p先走n步，p,q一起走，第一次相遇的地方就是环的入口
//2.如何确定环的个数？如果在环内，一个不动，另一个走，遇到的时候走了多少步就是多少
//3，如果保证都在环内？
//p每次走两步，q每次走一步，一定会在环内相遇
ListNode* isExistRing (ListNode* head) {
    ListNode* p = head;
    ListNode* q = head;
    
    //p每次走两步，q每次走一步,找到相遇节点
    ListNode* meet = NULL;
    while (p->next != NULL && q != NULL) {
        p = p->next->next;
        q = q->next;
        if (p == q) {
            meet = q;
            break;    //!!!!!否则是死循环
        }
    }
    return meet;
}

ListNode* findEntrance (ListNode* head) {
    if (head == NULL) return NULL;
    else {
        //第一步确定环中节点个数
        ListNode* p = head;
        ListNode* meet = isExistRing (head);
        if (meet != NULL) {
            while (p != meet) {
                p = p->next;
                meet = meet->next;
            }
            return meet;
        }
        else {
            throw invalid_argument ("NO Rings!");
        }
    }
}
/********** 10. 链表中环的入口 **********/

/********** 11. 两个栈列实现队列 **********/
//进栈直接进到st1中即可，出栈的时候，判断st1中有没有元素，有就全部进入st2,没有就判断st1
template <class T> class MyQue {
private:
    stack<T> st1;
    stack<T> st2;
public:
    MyQue() {}
    ~MyQue() {}
    
    void push (const T& val) {
        st1.push(val);
    }
    
    T pop() {
        T ret;
        while (!st1.empty()) {
            T tmp = st1.top();
            st1.pop();
            st2.push(tmp);
        }
        if (!st2.empty()) {
            ret = st2.top();
            st2.pop();
        }
        else
            throw invalid_argument ("NO Elements!");
    }
    
};
// 2. 两个队列实现栈呢？
/* 插入：如果q1不空，则插入q1中；如果q2不空，则插入到q2中，如果都空，则插入到q1中
 * 弹出：如果q1是空，判断q2，空就报错；不空则将q2的元素除了最后一个，剩下全都移到q1中，同理。。。。
 */
/********** 11. 两个队列实现栈 **********/

/********** 12. 包含min函数的栈 **********/
//找到栈的最小值函数，实现pop push min
template <class T> class minStack {
private:
    stack<T> st;
    stack<T> min_st;
public:
    minStack() {}
    ~minStack() {}
    
    void push (const T& val) {
        st.push(val);
        if (min_st.size() == 0) min_st.push(val);
        else {
            if (val < min_st.top()) min_st.push(val);
            else min_st.push(min_st.top());
        }
    }
    
    T pop () {
        assert (!st.empty() && !min_st.empty());
        st.pop();
        min_st.pop();
    }
    
    T min () {
        assert (!min_st.empty());
        return min_st.top();
    }
};
/********** 12. 包含min函数的栈 **********/

/********** 13. 判断栈的压入，弹出序列 **********/
//输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序
//思路：设置一个栈，只要当前栈顶元素（空栈的时候需要单独处理）和出栈队列首元素不相同，如果进栈队列还有元素能进栈，则进栈；没有元素能进栈则直接返回错误。
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    int size_pushed = pushed.size();
    int size_poped = popped.size();
    if (size_pushed == 0 || size_poped == 0) return true;
    int i = 0, j = 0;
    stack<int> st;
    while (j < size_poped) { //这块只能使用这个条件，只有当poped队列全部出完了，才有可能是出栈顺序
        //空栈情况下，不能使用top（）,相同就出栈
        if (!st.empty() && st.top() == popped[j]) {
            j++;
            st.pop();
        }
        else {//不同就进栈
            //空栈单独处理
            while (i < size_pushed && (st.empty() ||st.top() != popped[j])) {
                st.push(pushed[i]);
                i++;
            }
            //没有元素能进栈，还不同的话，直接返回错误
            if (i >= size_pushed && st.top() != popped[j]) return false;
        }
    }
    return true;
}
/********** 13. 判断栈的压入，弹出序列 **********/

/********** 14. 滑动窗口的最大值 **********/
//给定一个数组和滑动窗口的大小，找出所有滑动窗口中的最大值，比如 {2,3,4,2,6,2,5,1},k=3,则一共有8-2=6个窗口，每个窗口最大值序列为 {4,4,6,6,6,5}
//感悟，其实滑动窗口就是一个生命周期，方法一中，通过容器中始终保持3个元素，且每次删除的是原先数组中的过期元素来实现。
//关于找到窗口中的最大（小）值，可以选择一个有序、可重复的容器来解决，只能是multiset
vector<int>  maxSlidingWindows (vector<int> nums, int k) {
    int len = nums.size();
    vector<int> ret;
    if (len < 1 || k > len) return ret;
    else {
        multiset<int> windows;
        for (int i = 0; i < len; ++i) {
            //每次保留k个元素 && 每次删除 “过期” 元素
            if (i >= k)
                windows.erase(windows.find(nums[i-k]));
            //插入进去后都会进行自动排序
            windows.insert(nums[i]);
            if (i >= k -1)
                ret.push_back(*(windows.rbegin()));
        }
        return ret;
    }
}
//但是时间复杂度是O(nlogn)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    //双端队列存储的是下标！！！！
    int len = nums.size();
    vector<int> ret;
    if (k < 1 || len < k) return ret;
    else {
        deque<int> index;
        for (int i = 0; i < k; ++i) {
            while (!index.empty() && nums[i] > nums[index.back()]) index.pop_back();
            index.push_back(i);
        }
        ret.push_back(nums[index.front()]);

        for (int i = k; i < len; ++i) { 
            if (i - index.front() >= k) index.pop_front();
            while (!index.empty() && nums[i] > nums[index.back()]) index.pop_back();
            index.push_back(i);
            ret.push_back(nums[index.front()]);
        }
        return ret;
    } 
}
/********** 14. 滑动窗口的最大值 **********/

/********** 15. 实现求得队列最大值函数，要求pop push max均为O(1) **********/
//知识迁移能力：队列的出队入队可以看成一个滑动窗口。
//queue有新元素入队的时候，判断当前元素和deque中前面元素比较，如果大于前面元素，则直接删除，最后自己入队；
//出队的时候，用当前元素和deque队首元素比较，如果相同，则deque出队
//原则就一个，始终保持队首元素是最大值
template <class T> class MaxQue {
private:
    struct Node {
        T data;
        unsigned int index;
        //Node (ElemType e, int i):data(e),index(i) {}
    };
    
    unsigned int num;
    queue<Node> qu;
    deque<Node> max_qu;
public:
    MaxQue() {num = 0;}
    ~MaxQue() {}
    
    void push (T e) {
        Node node = {e,num++};
        qu.push(node);
        if (max_qu.empty()) max_qu.push_back(node);
        else {
            while (!max_qu.empty() && e > max_qu.back().data) {
                max_qu.pop_back();
            }
            max_qu.push_back(node);
        }
    }
    
    T pop() {
        assert(!qu.empty() && !max_qu.empty());
        T ret = qu.front().data;
        if (qu.front().index == max_qu.front().index) {
            qu.pop(); max_qu.pop_front();
        }
        else qu.pop();
        return ret;
    }
    
    T max() {
        assert(!max_qu.empty());
        return max_qu.front().data;
    }
};

/********** 15. 实现求得队列最大值函数，要求pop push max均为O(1) **********/

/********** 主函数 **********//*
int main()
{
    MaxQue<int> myQue;
    myQue.push(2);
    myQue.push(6);
    myQue.push(1);
    myQue.push(5);
    myQue.pop();
    cout << myQue.max() << endl;
    
    ListNode* ret = NULL;
    ListNode* head = NULL;
    addNode (head, 1);
    //addNode (head, 1);
    addNode (head, 2);
    //addNode (head, 2);
    //addNode (head, 3);
    addNode (head, 4);
    addNode (head, 11);
    
    ListNode* head1 = NULL;
    addNode (head1, 1);
    addNode (head1, 4);
    addNode (head1, 11);
    
    //head = deleteNode (head, 1);
    
    //head = deleteRepeatNode (head);
    
    //printListFromBack (head);
    
    //deleteListInO1 (head, head->next->next);
    
    //cout << deleteTopk(head, 2)->data << endl;
    
    //head = reverseList (head);
    
    //ListNode* merge = NULL;
    //merge = mergeList(head, head1);
    
    //ret = findTraNode2 (head, head1);
    
    ListNode list[6];
    
    list[0].data = 1;
    list[0].next = &list[1];
    list[1].data = 2;
    list[1].next = &list[2];
    list[2].data = 3;
    list[2].next = &list[3];
    list[3].data = 4;
    list[3].next = &list[4];
    list[4].data = 5;
    list[4].next = &list[5];
    list[5].data = 6;
    list[5].next = &list[2];
    //ret = findEntrance (list);
    //printList(ret);
    cout << ret->data << endl;
    cout << endl;
    return 0;
}
*//********** 主函数 **********/
#endif
