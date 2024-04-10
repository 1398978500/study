#include <iostream>
#include <vector>

using namespace std;

// 类型T需要重载operator>和operator<
template <typename T>
void quickSort(vector<T>& vData, int l, int r) {
    if( l >= r) return;
    int mid = l + (r - l >> 1);
    T &num = vData[mid];

    int i = l - 1, j = r + 1;
    while(i < j) {
        while(vData[++i] < num) ;
        while(vData[--j] > num) ;
        if(i < j) {
            swap(vData[i], vData[j]);
        }
    }

    quickSort(vData, l, j);
    quickSort(vData, j + 1, r);
}

int main(int argc, char *argv[]) {
    int n = 0;
    cin >> n;
    vector<string> vData(n, "");

    for(int i = 0; i < n; i++) {
        cin >> vData[i];
    }

    quickSort(vData, 0, n - 1);

    for(auto &s : vData) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}

