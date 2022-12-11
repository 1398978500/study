/*定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。



示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.


提示：

各函数的调用总次数不超过 20000 次
*/

class MinStack {
public:
    stack<int> st;     // 存储原数的栈
    stack<int> stMin;  // 存储最小值的栈

    /** initialize your data structure here. */
    MinStack() {}

    void push(int x)
    {
        st.push(x);

        if (stMin.empty()) {
            stMin.push(x);
        }
        else {
            // 将较小值存入最小值栈
            stMin.push(x < stMin.top() ? x : stMin.top());
        }
    }

    void pop()
    {
        st.pop();
        stMin.pop();
    }

    int top()
    {
        return st.top();
    }

    int min()
    {
        return stMin.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
