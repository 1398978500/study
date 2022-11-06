/*
维护一个字符串集合，支持两种操作：

I x 向集合中插入一个字符串 x；
Q x 询问一个字符串在集合中出现了多少次。
共有 N 个操作，输入的字符串总长度不超过 10^5，字符串仅包含小写英文字母。

输入格式
第一行包含整数 N，表示操作数。

接下来 N 行，每行包含一个操作指令，指令为 I x 或 Q x 中的一种。

输出格式
对于每个询问指令 Q x，都要输出一个整数作为结果，表示 x 在集合中出现的次数。

每个结果占一行。

数据范围
1≤N≤2∗10^4
输入样例：
5
I abc
Q abc
Q ab
I ab
Q ab
输出样例：
1
0
1
*/

#include <iostream>

using namespace std;

const int N = 100010;

int son[N][26];
int idx;      // 标记是哪个节点
int cnt[N];   // 计数
char str[N];  // 输入

void insert(char* s)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int u = str[i] - 'a';

        // 节点不存在
        if (son[p][u] <= 0) {
            son[p][u] = ++idx;
        }

        p = son[p][u];
    }

    cnt[p]++;  // 插入后对应节点计数增加
}

int query(char* s)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int u = str[i] - 'a';
        if (son[p][u] <= 0) {
            return 0;
        }

        p = son[p][u];
    }

    return cnt[p];
}

int main(int argc, char const* argv[])
{
    int n = 0;
    cin >> n;

    char op;
    while (n-- > 0) {
        cin >> op >> str;
        if (op == 'I') {
            insert(str);
        }
        else {
            cout << query(str) << endl;
        }
    }

    return 0;
}