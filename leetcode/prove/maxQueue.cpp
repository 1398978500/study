/*
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1
*/

class MaxQueue {
public:
    queue<int> q;  // 队列
    deque<int> d;  // 队列最大值
    MaxQueue() {}

    int max_value()
    {
        if (d.empty()) {
            return -1;
        }

        return d.front();
    }

    void push_back(int value)
    {
        // 当前数插入 最大值队列时删除之前比当前数小的(当前数入队,则之前小的数永远不会是最大值)
        while (!d.empty() && d.back() < value) { d.pop_back(); }

        q.push(value);
        d.push_back(value);
    }

    int pop_front()
    {
        if (q.empty()) {
            return -1;
        }

        int res = q.front();
        if (d.front() == res) {
            d.pop_front();
        }

        q.pop();
        return res;
    }
};
