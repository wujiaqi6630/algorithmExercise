#if WDEBUG
/* 1. 设计一个LRU 146
 * 2. 设计一个set 380, 381
 */

//LRU leetcode 146
/* 设计一个LRU（最近最少使用）缓存机制
 * 要求：支持两个方法：
 * get(key): 输入key,返回value，如果不存在返回pair
 * put(key,value): if key 存在，更新；如果不存在，则插入： 如果插入的过程发现缓存已经满了，则替换掉最久没有使用的数据值
 * 分析 ： 因为需要频繁的移动内部节点，切需要频繁插入删除首尾节点，考虑使用双链表
 *      但是双链表无法实现内部节点的随机访问，因此考虑使用 hash_map 实现 key， ListNode 之间的映射
 */

 using T1 = int;
 using T2 = int;
 struct DoubleListNode {
     T1 k;
     T2 v;
     struct DoubleListNode* pre;
     struct DoubleListNode* next;
     DoubleListNode (): k(0), v(0), pre(nullptr), next(nullptr) {}
     DoubleListNode (T1 t1, T2 t2): k(t1), v(t2), pre(nullptr), next(nullptr) {}
 };
 
 class LRUCache {
 private:
     DoubleListNode* head, *tail;
     unordered_map<T1, DoubleListNode*> mmap_;
     int size_;
     int capcity_;
 public:
     LRUCache(int capcity) {
         capcity_ = capcity;
         size_ = (int)mmap_.size();
         
         head = new DoubleListNode();
         tail = new DoubleListNode();
         head->next = tail;
         tail->pre = head;
     }
 
     void moveToTail (DoubleListNode* node) {
         node->pre->next = node->next;
         node->next->pre = node->pre;
         
         node->pre = tail->pre;
         tail->pre->next = node;
         node->next = tail;
         tail->pre = node;
     }
 
     T2 get(T1 key) {
         if (mmap_.find(key) != mmap_.end()) {
         //被访问，应该挪到双链表的队尾
             if (size_ > 1) moveToTail(mmap_[key]);
             return mmap_[key]->v;
         }
         else return -1;
     }
 
     void put (T1 key, T2 value) {
         if (mmap_.find(key) != mmap_.end()) {
             mmap_[key]->v = value;
             //被访问，挪到链表尾部
             if (size_ > 1)  moveToTail(mmap_[key]);
         }
         //新插入的节点并不存在
         else {
            DoubleListNode* node = new DoubleListNode(key,value);
             //空间不够，先删除头部节点
             if (size_ > 0 && size_ >= capcity_) {
                 DoubleListNode* toBeDeleted = head->next;
                 head->next = toBeDeleted->next;
                 toBeDeleted->next->pre = head;
     
                 mmap_.erase(toBeDeleted->k);
                 --size_;
     
                 if (toBeDeleted != nullptr) {
                     delete toBeDeleted;
                     toBeDeleted = nullptr;
                 }
             }
             node->pre = tail->pre;
             tail->pre->next = node;
             node->next = tail;
             tail->pre = node;
     
             mmap_[key] = node;
             ++size_;
         }
     }
 };


/****************** 常数时间插入/删除/返回随机值的数据结构 ********************/
/* 题目：设计一个平均时间复杂度可在O(1)完成的插入删除返回随机值的操作，不允许重复元素
 * 分析 ： 删除可在O(1)时间复杂度完成的有两种方法：
 *      （1）链表
 *      （2）数组交换后，删除尾部元素
 * 返回随机值，则一般依靠索引操作，因此这道题目采用动态数组实现
 */
using ElemType = int;
class RandomizedSet {
private:
    vector<int> vec;
    unordered_map<ElemType, int> mmap;
    int size_;
    
public:
    RandomizedSet() {size_ = 0;}
    
    bool insert (ElemType val) {
        bool flag = false;
        //不存在才插入
        if (!mmap.count(val)) {
            vec.push_back(val);
            mmap[val] = size_;
            ++size_;
            flag = true;
        }
        return flag;
    }
    
    bool remove (int val) {
        bool flag = false;
        //不存在才删除
        if (mmap.count(val)) {
            int index = mmap[val];
            mmap[vec[size_-1]] = index;
            mmap.erase(val);
            --size_;
            
            if (index != size_-1) {
                vec[index] = vec[size_-1];
            }
            vec.pop_back();
            flag = true;
        }
        return flag;
    }
    
    int getRandom () {
        assert(size_ > 0);
        return vec[rand() % size_];
    }
};

//题目2 ： 允许重读元素
// 允许重复元素：unordered_map<int, unordered_set<int>>,其余一样
class RandomizedCollection {
private:
    vector<int> vec;
    unordered_map<int, unordered_set<int>> mmap;
    int size_;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        size_ = 0;
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool flag = false;
        if (mmap.count(val)) {
            flag = false;
        }
        else flag = true;
        
        mmap[val].insert(size_);
        ++size_;
        
        return flag;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (!mmap.count(val)) return false;
        if (vec.back() == val) {
            vec.pop_back();
            mmap[val].erase(size_-1);
            --size_;
        }
        else {
            int tail = vec.back();
            auto it = mmap[val].begin();
            vec[*it] = tail;
            mmap[val].erase(*it);
            mmap[tail].erase(size_-1);
            mmap[tail].insert(*it);
            vec.pop_back();
            --size_;
        }
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        assert (size_ > 0);
        return rand() % size_;
    }
};
/****************** 常数时间插入/删除/返回随机值的数据结构 ********************/


 int main () {
     LRUCache* cache = new LRUCache(2);
     cache->put(1, 1);
     cache->put(2, 2);
     cout << cache->get(1) << endl;
     cache->put(3, 3);
     cout << cache->get(2) << endl;
     cache->put(4, 4);
     cout << cache->get(1) << endl;
     cout << cache->get(3) << endl;
     cout << cache->get(4) << endl;
     //cout << num;
     return 0;
 }


#endif






