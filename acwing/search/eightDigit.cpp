/*
在一个 3×3 的网格中，1∼8 这 8 个数字和一个 x 恰好不重不漏地分布在这 3×3 的网格中。

例如：

1 2 3
x 4 6
7 5 8
在游戏过程中，可以把 x 与其上、下、左、右四个方向之一的数字交换（如果存在）。

我们的目的是通过交换，使得网格变为如下排列（称为正确排列）：

1 2 3
4 5 6
7 8 x
例如，示例中图形就可以通过让 x 先后与右、下、右三个方向的数字交换成功得到正确排列。

交换过程如下：

1 2 3   1 2 3   1 2 3   1 2 3
x 4 6   4 x 6   4 5 6   4 5 6
7 5 8   7 5 8   7 x 8   7 8 x
现在，给你一个初始网格，请你求出得到正确排列至少需要进行多少次交换。

输入格式
输入占一行，将 3×3 的初始网格描绘出来。

例如，如果初始网格如下所示：

1 2 3
x 4 6
7 5 8
则输入为：1 2 3 x 4 6 7 5 8

输出格式
输出占一行，包含一个整数，表示最少交换次数。

如果不存在解决方案，则输出 −1。

输入样例：
2 3 4 1 5 x 7 6 8
输出样例
19
*/

#if 0
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

int bfs(string start)
{
    string end = "12345678x";
    unordered_map<string, int> m;  // key为当前数组情况,val为变成当前形状需要的步数

    m[start] = 0;

    queue<string> q;
    q.emplace(start);

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    while (!q.empty()) {
        string t = q.front();
        q.pop();

        // 记录当前步骤
        int discount = m[t];

        // 若以结束 则返回结果
        if (t == end) {
            return discount;
        }

        int index = t.find('x');  // 找到当前x所在下标

        // 一维坐标转化为二维
        int x = index / 3;
        int y = index % 3;

        // 向四个方向尝试
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i], b = y + dy[i];

            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                swap(t[index], t[a * 3 + b]);

                // 没有走到过这一步
                if (m.count(t) <= 0) {
                    // 记录此步骤
                    m[t] = discount + 1;
                    q.emplace(t);  // 将此步加入到队列
                }

                // 遍历下个点前 先将字符串还原
                swap(t[index], t[a * 3 + b]);
            }
        }
    }

    return -1;
}

int main(int argc, char const* argv[])
{
    string start;

    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        start += c;
    }

    cout << bfs(start) << endl;

    return 0;
}
#else // chatgpt优化

#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 9; // 3x3网格的总格数
const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 上、右、下、左移动
const string target = "12345678x"; // 目标状态

// 预处理所有可能的状态转移
vector<string> getNextStates(const string& state) {
    vector<string> nextStates;
    int index = state.find('x');
    int x = index / 3, y = index % 3;
    for (auto& dir : dirs) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            string nextState = state;
            swap(nextState[index], nextState[nx * 3 + ny]);
            nextStates.push_back(nextState);
        }
    }
    return nextStates;
}

int bfs(const string& start) {
    if (start == target) return 0;
    queue<string> q;
    q.push(start);
    unordered_map<string, int> dist; // 记录到达每个状态的最小步数
    dist[start] = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        vector<string> nextStates = getNextStates(cur);
        for (const string& nextState : nextStates) {
            if (dist.count(nextState)) continue; // 已访问过
            dist[nextState] = dist[cur] + 1;
            if (nextState == target) return dist[nextState];
            q.push(nextState);
        }
    }
    return -1; // 无法到达目标状态
}

int main() {
    string start;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        start += c;
    }
    cout << bfs(start) << endl;
    return 0;
}


#endif
