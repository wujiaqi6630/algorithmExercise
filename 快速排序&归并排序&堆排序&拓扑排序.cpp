#if WDEBUG
/*
 * 归并排序
 * 快速排序
 * 堆排序
 * 冒泡
 * 插入
 * 选择
 * 逆序数对
 * 数学成绩和语文成绩排序
 */

//  快速排序&归并排序&堆排序&拓扑排序.cpp
//  testing
//
//  Created by dragon on 2020/7/18.
//  Copyright © 2020 dragon. All rights reserved.
//

#include <iostream>
#include <stdexcept>

using namespace std;
/*********************归并排序*****************************/
/* 归并排序算法：先划分，再组合
 *      if(left < right) 不能相等
 *      注意使用一个临时数组
 *      tmp要记得释放，输出给arr时候注意下标，arr[]本身就是一个指针，可以改变值
 */
void merge (int arr[], int left, int mid, int right) {
    int* tmp = new int[right-left+1];
    int l = left, r = mid+1, k = 0;
    while (l <= mid && r <= right) {
        if (arr[l] < arr[r]) tmp[k++] = arr[l++];
        else tmp[k++] = arr[r++];
    }
    while (l <= mid) tmp[k++] = arr[l++];
    while (r <= right) tmp[k++] = arr[r++];
    
    for (int i = left,k=0; i <= right; ++i,++k)   //最重要！！！！
        arr[i] = tmp[k];
    delete[] tmp;
}

void mergeSort (int arr[], int left, int right) {
    if (left < right){   //left 不能和 right 相等，一个元素没有划分的意义
        int mid = left + (right - left)/2;
        mergeSort (arr, left, mid);
        mergeSort (arr, mid+1,right);
        merge (arr, left, mid, right);
    }
}

/*********************快速排序*****************************/
/* 快速排序：找一个基准元素，一趟排序结果：比pivot大的在右面，比pivot小的在左面。
 *      注意最后递归 quickSort(arr, left, l-1);
 */
void quickSort (int arr[], int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int pivot = arr[l];
        while (l < r) {
            while (l < r && arr[r] > pivot) r--;
            if (l < r) arr[l++] = arr[r];
            while (l < r && arr[l] < pivot) l++;
            if (l < r) arr[r--] = arr[l];
        }
        arr[l] = pivot;
        quickSort(arr, left, l-1);
        quickSort(arr, l+1,right);
    }
}

// 快速排序变形 形式，非常有用！！！
int randomInRange (int left, int right) {
    return (rand() % (right-left+1) + left);
}
int partition (vector<int>& nums, int left, int right) {
    int axis = -1;
    if (left < right) {
        //int index = randomInRange (left, right);
        //swap(nums[index], nums[left]);
        int l = left, r = right;
        int pivot = nums[left];
        while (l < r) {
            while (l < r && pivot < nums[r]) r--;
            if (l < r) nums[l++] = nums[r];
            while (l < r && pivot > nums[l]) l++;
            if (l < r) nums[r--] = nums[l];
        }
        nums[l] = pivot;
        axis = l;
        //partition(nums, left, l-1);
        //partition(nums, l+1, right);
    }
    return axis;
}

/*********************堆排序*****************************/
/* 堆排序：堆是一个完全二叉树，每个父节点都大于其子节点；父子节点关系可以使用下标表示。如当前节点i，则其父节点是（i-1）/2,
 *          子节点分别是 2*i+1 和 2*i+2
 * 1）构建一个大顶堆：从第一个非叶节点开始调整.假设完全二叉树一共有n个节点，则第一个非叶节点是n/2-1
 * 2）每次把大顶堆的跟节点取出来与最后一个节点进行交换 swap
 * 对于任意一个的调整算法：
 *  首先保存当前节点；
 *  将左右孩子最大的那个赋值给父节点
 *  并且以孩子节点作为父节点去调整子树
 */
// 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
void heapAdjust (int arr[], int len, int par) {
    int lc = 2 * par + 1;
    int rc = 2 * par + 2;
    
    int cur = par;
    if (lc < len && arr[lc] > arr[cur]) cur = lc;
    if (rc < len && arr[rc] > arr[cur]) cur = rc;
    
    if (cur != par) {
        swap (arr[cur],arr[par]);
        heapAdjust (arr, len, cur);
    }
}

void heapSort (int arr[], int len) {
    //从第一个非叶节点开始，每次都能得到当前堆中最大值,
    for (int i = len/2 - 1; i >= 0; i--)
        heapAdjust (arr, len, i);
    
    //每次调整的arr[0]的位置，将最大值放在arr[i--]中
    for (int i = len-1; i >= 1; i--) {
        swap(arr[0],arr[i]);
        heapAdjust (arr, i, 0);
    }
}
/*********************堆排序*****************************/

/*
int main()
{
    int array[] = { 49,38,65,97,76,13,27,49,10  };
    int size = sizeof(array) / sizeof(int);
    //mergeSort(array, 0, size-1);
    //quickSort (array, 0, size-1);
    heapSort(arr, size);
    for (auto i : array)
        cout << i << " ";
    cout<<endl;
    return 0;
}
*/

/* 冒泡排序：按照两两交换的方式，每一趟把最大值放在最后
 * 插入排序：假设前n个元素已经是有序的状态，通过遍历比较 将第n个元素插入进去
 * 选择排序：每一趟遍历都选择最小的数据，通过交换 放在起始位置
 */
void bubbleSort (int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 1; j < len-i; ++j) {
            if (arr[j] < arr[j-1])
                swap(arr[j],arr[j-1]);
        }
    }
}

void insertSort (int arr[], int len) {
    for (int i = 1; i < len; ++i) {
        //for (int j = 0; j < i; ++j) {
        int j = i-1, tmp = arr[i];
        if (arr[i] >= arr[j]) continue;
        else {
            while (j >=0 && tmp < arr[j]) {   //!!!!  arr[i] < arr[j]  !!!error!!!!
                arr[j+1] = arr[j];
                j--;
            }
            if (j != i-1) arr[j+1] = tmp;
        }
    }
}

void selectSort (int arr[], int len ) {
    for (int i = 0; i < len; ++i) {
        int min = arr[i];
        for (int j = i + 1; j < len; ++j) {
            if (arr[j] < min)
                swap(arr[i],arr[j]);
        }
    }
}

/*********************逆序对数目统计***************************/
//思路：在归并排序中，在合并左右两个数组的过程中:选择右边元素时候，如果左边元素有几个，就有几个逆序对，则可以累加
void count1 (int arr[], int left, int mid, int right, int& count) {
    int* tmp = new int[right-left+1];
    int i = left, j = mid+1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) tmp[k++] = arr[i++];
        else {
            //count++;
            count += mid-i+1;
            tmp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];
    
    for (int i = left, k = 0; i <= right; i++,k++)
        arr[i] = tmp[k];
    
    delete[] tmp;
}

void countReversePairs (int arr[], int left, int right, int& count) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        countReversePairs (arr, left, mid, count);
        countReversePairs (arr, mid+1, right, count);
        count1 (arr, left, mid, right, count);
    }
}
/*********************逆序对数目统计***************************/

/*********************链表排序***************************/
ListNode* mergeList (ListNode* p, ListNode* q) {
    if (p == nullptr) return q;
    if (q == nullptr) return p;
    
    if (p->val < q->val) {
        p->next = mergeList(p->next,q);
        return p;
    }
    else {
        q->next = mergeList(p,q->next);
        return q;
    }
}
/*********************链表排序***************************/


//采用归并排序实现
ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;
    //快慢指针实现链表分段
    ListNode* p = head, *q = head, *pre = head;
    while (q != nullptr && q->next != nullptr) {
        pre = p;
        p = p->next;
        q = q->next->next;
    }
    pre->next = nullptr;
    
    return mergeList (sortList(head), sortList(p));
}


/*********************语文数学成绩排序***************************/
//根据语文成绩排序，如果语文成绩一样，则按照数学成绩排序
//思考使用pair<>
void sort1 (vector<pair<int, int> >& vec, int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int pivot = vec[l].first;
        while (l < r) {
            while (l < r && pivot < vec[r].first) r--;
            if (l < r) vec[l++].first = vec[r].first;
            while (l < r && pivot > vec[l].first) l++;
            if (l < r) vec[r--].first = vec[l].first;
        }
        vec[l].first = pivot;
        sort1 (vec, left, l-1);
        sort1 (vec, l+1, right);
    }
}

void sort2 (vector<pair<int, int> >& vec, int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int pivot = vec[l].second;
        while (l < r) {
            while (l < r && pivot < vec[r].second) r--;
            if (l < r) vec[l++].second = vec[r].second;
            while (l < r && pivot > vec[l].second) l++;
            if (l < r) vec[r--].second = vec[l].second;
        }
        vec[l].second = pivot;
        sort2 (vec, left, l-1);
        sort2 (vec, l+1, right);
    }
}

//语文数学成绩排序
int comp1 (const pair<int,int>& a, const pair<int,int>& b) {
    return a.first < b.first;
}
int comp2 (const pair<int,int>& a, const pair<int,int>& b) {
    return a.second < b.second;
}
void sort1 (vector<pair<int,int>>& vec) {
    sort (vec.begin(),vec.end(),comp1);
    int start = 0, end = 1;
    while (start < vec.size()-1) {
        end = start+1;
        if (vec[start].first == vec[end].first) {
            while (vec[start].first == vec[end].first) end++;
            sort (vec.begin()+start,vec.begin()+end,comp2);
        }
        start = end;
    }
}
    /*
     int left = 0, right = vec.size()-1;
     //调用sort，怎么使用？
     sort1 (vec, left, right);
     //sort (vec.begin(),vec.end(),cmp1);
     int i = 0;
     while  (i < right+1) {
     if (vec[i].first == vec[i-1].first) {
     int start = i-1;
     while (vec[i].first == vec[i-1].first)
     i++;
     int end = i-1;
     sort2 (vec, start, end);
     //sort (vec.begin(),vec.end(),cmp2);
     }
     else i++;
     }
     */
}
/*********************语文数学成绩排序***************************/

int main(int argc, const char * argv[]) {
    int arr[] = {5,10,2,3,4,9,-1};
    int c = 0;
    countReversePairs (arr, 0, 6, c);
    cout << "c is : " << c << endl;
    vector<int> a1{3,4,5,4,1,3,3};
    vector<int> a2{4,6,0,7,6,8,5};
    vector<pair<int,int>> vec;
    //注意赋值过程！！！！
    for (int i = 0; i < a1.size(); ++i) {
        //vec[i] = make_pair(a1[i], a2[i]); // 下标只能用于获取已存在的元素
        //vec.push_back(make_pair(a1[i], a2[i]));
        vec.emplace_back (make_pair (a1[i], a2[i]));//效率!!!
    }
    mySort(vec);
    for (auto i : vec)
        cout << i.first << " , " << i.second << endl;
    cout << endl;
    return 0;
}

#endif
