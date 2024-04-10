#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void mergeSort(vector<T> &v, int l, int r) {
    if(l >= r) {
        return;
    }

    int mid = l + (r - l >> 1);
    mergeSort(v, l, mid);
    mergeSort(v, mid + 1, r);

    // 此时l-mid有序,mid+1-r有序
    // 合并一下
    vector<T> vTmp(r - l + 1, T());
    int i = l, j = mid + 1, index = 0;
    while(i <= mid && j <= r) {
        if(v[i] < v[j]) {
            vTmp[index++] = v[i++];
        } else {
            vTmp[index++] = v[j++];
        }
    }

    while(i <= mid) {
        vTmp[index++] = v[i++];
    }

    while(j <= r) {
        vTmp[index++] = v[j++];
    }

    // 写回原数组
    i = l;
    for(auto& item:vTmp) {
        v[i++] = move(item);
    }
}

int main(int argc, char* argv[]) {
    int n = 0;
    cin >> n;
    vector<string> vData(n, "");

    for(int i = 0; i < n; i++) {
        cin >> vData[i];
    }

    mergeSort(vData, 0, n - 1);

    for(auto &s : vData) {
        cout << s << " ";
    }
    cout << endl;
    

    return 0;
}

