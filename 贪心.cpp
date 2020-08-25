#if WDEBUG
//  贪心.cpp
//  jiaqi
//
//  Created by dragon on 2020/7/20.
//  Copyright © 2020 dragon. All rights reserved.
//

/******************************* **********************************/
//https://www.cnblogs.com/gropeliang/p/13417802.html
//关于区间调度问题，看这篇博客就够了！！
// 1. 最多无重叠区间数目
// 2. 最多重叠区间数目
// 3. 最大无重叠区间长度
/******************************* **********************************/

//问题原型
//有n个会议，开始结束时间分别是[s1,e1],[s2,e2],[s3,e3]...互相可能重叠
//问题1 ： 一个人最多参加几个会议？
//vec{{3,4},{2,5},{4,6},{5,6},{1,8},{7,9}}
int func1 () {
    int len = 0;
    cout << "输入元素个数 ： " << endl;
    cin >> len;
    vector<pair<int, int>> vec;
    int start, end;
    cout << "输入pair数据，以空格间隔 ：" << endl;
    for (int i = 0; i < len; ++i) {
        cin >> start >> end;
        vec.emplace_back (make_pair (start, end));
    }
    
    sort (vec.begin(), vec.end(), [](const pair<int,int>& a, const pair<int, int>& b) {return a.second < b.second;} );
    
    int count = 1;
    int endX = vec[0].second;
    for (int i = 1; i < len; ++i) {
        if (vec[i].first >= endX) {
            count++;
            endX = vec[i].second;
        }
    }
    cout << "一天最多参加"<<count << "个会议"<<endl;
    return count;
}

//问题2: 重叠区间的最多数目
// 分析 ： 将每个区间的开始和结束做标记后全部存储到数组中，对数组排序，相同的将标记为结束的排在前面
//然后遍历数组 ： 遇到是开始标记的数据+1，遇见结束标记的数据0；就可以得到任意区间的重叠数目，取最大值
//vec{{1,8},{2,5},{6,7},{4,9},{3,5}}
int func2 () {
    int num = 0;
    cout << "输入元素个数 ： " << endl;
    cin >> num;
    int start, end;
    vector<pair<int, int>> vec;
    cout << "输入pair数据，以空格间隔 ：" << endl;
    for (int i = 0; i < num; ++i) {
        cin >> start >> end;
        vec.emplace_back (make_pair (start, 0));
        vec.emplace_back (make_pair (end, 1));
    }
    
    sort (vec.begin(), vec.end(), [](const pair<int,int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return b.second < a.second;
        return a.first < b.first;
    });
    
    int count = 0, maxV = 1;
    for (int i = 0; i < 2*num; ++i) {
        if (vec[i].second == 0) count++;
        if (vec[i].second == 1) count--;
        maxV = max (maxV, count);
    }
    cout << "一天同时开的会议最多有"<<maxV << "个。"<<endl;
    return maxV;
}

//问题3: 最大不重叠区间长度：如果只有一间会议室，在所有不重叠的方案中，那个方案利用效率最高（使用时间最长）？
// 分析 ：按照会议结束时间排序。使用动态规划解决：dp[i]表示以第i个会议作为无重叠区间的最后一个会议，能得到的最长会议时间
//vec{{3,4},{2,5},{4,6},{5,6},{1,8},{7,9}}
int func3 () {
    int len = 0;
    cout << "输入元素个数 ： " << endl;
    cin >> len;
    int start, end;
    vector<pair<int, int>> vec;
    cout << "输入pair数据，以空格间隔 ：" << endl;
    for (int i = 0; i < len; ++i) {
        cin >> start >> end;
        vec.emplace_back (make_pair(start, end) );
    }
    
    sort (vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b){ return a.second < b.second;} );
    
    vector<int> dp(len);
    int ret = 0;
    for (int i = 0; i < len; ++i) {
        int maxV = 0;
        for (int j = 0; j < i; ++j) {
            if (vec[i].first >= vec[j].second) maxV = max (maxV, dp[j]);
        }
        dp[i] = maxV + (vec[i].second - vec[i].first);
        ret = max (ret, dp[i]);
    }
    cout << "一天会议室最长使用"<<ret << "个小时。"<<endl;
    return ret;
}


//下面是具体题目
/********************* 1. 贪心算法——区间调度问题（可选活动最多问题）****************/
// https://zhuanlan.zhihu.com/p/91254104
//多个活动有重叠，如何选择保证参加的活动最多？
//！！！！！！！！！在当前可选的时间内选择结束时间最早的！！！！！！
int compare (const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

int interverlSchedule (vector<pair<int, int>> nums) {
    int len = int (nums.size());
    if (len == 0) return 0;
    if (len == 1) return 1;
    
    sort(nums.begin(), nums.end(), compare);
    
    int count = 1;
    int end = nums[0].second;
    for (int i = 1; i < len; ++i) {
        int start = nums[i].first;
        if (start >= end) {
            count++;
            end = nums[i].second;
        }
    }
    return count;
}
/********************* 1. 贪心算法——区间调度问题****************/


/************************** 2. 去掉重复区间的最少次数（灵活使用） **************************/
int compare1 (const vector<int>& a, const vector<int>& b) {
    assert (a.size() == 2 && b.size() == 2);
    return a[1] < b[1];
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    int len = int (intervals.size());
    if (len < 2) return 1;
    sort (intervals.begin(), intervals.end(), compare1);
    int count = 1;
    int end = intervals[0][1];
    for (int i = 1; i < len; ++i) {
        if (intervals[i][0] >= end) {
            count++;
            end = intervals[i][1];
        }
    }
    return len-count;
}
/************************** 2. 去掉重复区间的最少次数 **************************/

/************************** 3. 射气球问题 **************************/
//题目：一支弓箭可以沿着x轴从不同点完全垂直地射出。在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。
int findMinArrowShots(vector<vector<int>>& points) {
    int len = int (points.size());
    if (len == 0) return 0;
    if (len == 1) return 1;
    
    sort (points.begin(), points.end(),
          [&](const vector<int>& a, const vector<int>& b){return a[1] < b[1];});
    
    int count = 1;
    int end = points[0][1];
    for (int i = 1; i < len; ++i) {
        if (points[i][0] > end) {
            count++;
            end = points[i][1];
        }
    }
    return count;
}
/************************** 3. 射气球问题 **************************/

/********************* 2. 剪绳子****************/
//问题 ： 长度为n 剪成m 段，乘积最大 （m,n>1,都是整数）
//分析 ： dp[i]表示绳子长度为i时，剪绳子方法的乘积能得到最大值
/* dp[2] = 1;
 * dp[3] = 2;
 * dp[3] = 4
 */
int cutSolution (int n) {
    assert (n > 1);
    if (n == 2) return 1;
    if (n == 3) return 2;
    vector<int> dp(n+1);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    
    for (int i = 4; i <= n; ++i) {
        for (int j = 1; j <= n/2; ++j) {
            dp[i] = max (dp[i], dp[j]*dp[i-j]);
        }
    }
    return dp[n];
}
/********************* 2. 剪绳子****************/

/********************* 3. 小明上课（最多重叠区间问题，最少使用会议室问题）****************/
//小明看节目，节目一起始时间是s1,e1  节目二s2,e2,   节目三s3,e3。。。各个节目时间可能会出现重叠，一共有n个节目，小明有一心多用的能力（同一时刻可同时看多个节目），问，要看完所有节目，小明至少要一心几用能力？（s和e自己输入）
int maxLessons (vector<pair<int, int>> vec) {
    int len = int (vec.size());
    if (len == 0) return 0;
    if (len == 1) return 1;
    
    sort (vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.fisrt == b.fisrt) return b.second < a.second;
        return a.fisrt < b.first;
    });
    
    int count = 0, maxV = 1;
    for (int i = 0; i < len*2; ++i) {
        if (vec[i].second == 0) count++;
        if (vec[i].second == 1) count--;
        maxV = max (maxV, count);
    }
    
    return maxV;
}
/********************* 3. 小明上课****************/

#endif
