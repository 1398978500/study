#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void down(vector<T>& v, int i) {
    int l = i * 2;
    int r = l + 1;

    int t = i;
    if(l < v.size() && v[l] < v[t]) {
        t = l;
    }

    if(r < v.size() && v[r] < v[t]) {
        t = r;
    }

    if(t != i) {
        swap(v[t], v[i]);
        down(v, t);
    }
}

int main(int argc, char* argv[]) {
    int n = 0;
    cin >> n;
    vector<string> vData(n + 1, "");

    for(int i = 1; i <= n; i++) {
        cin >> vData[i];
    }

    for(int i = n / 2; i > 0; i--) {
        down(vData, i);
    }

    while(n--) {
        cout << vData[1] << endl;

        vData[1] = vData.back();
        vData.pop_back();
        down(vData, 1);
    }

    return 0;
}

