#include <iostream>
#include <vector>

using namespace std;

// 从小到大排序
// 大根堆
void down(vector<int> &vNums, int iCount, int i) {
    int l = i * 2 + 1;
    int r = l + 1;

    int t = i;
    if(l < iCount && vNums[l] > vNums[t]) {
        t = l;
    }

    if(r < iCount && vNums[r] > vNums[t]) {
        t = r;
    }

    // 将根与最大的节点交换
    if(t != i) {
        swap(vNums[t], vNums[i]);
        down(vNums, iCount, t);
    }
}

// 原地把堆排序
void heapSort(vector<int> &vNums) {
    for(int i = vNums.size() - 1; i >= 0; i--) {
        down(vNums, vNums.size(), i);
    }

    for(int i = vNums.size() - 1; i > 0; i--) {
        // 最大的数交换到堆尾
        swap(vNums[0], vNums[i]);

        // 堆顶元素down
        down(vNums, i, 0);
    }
}

int main(int argc, char* argv[]) {

    vector<int> vNums = {4,6,7,1,2,8,3};

    heapSort(vNums);

    for(int i : vNums) {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}

