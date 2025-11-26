#include "ThreadPool.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ThreadSafeQueue<Task> q;

    q.push([]() { cout << "hello" << endl; });

    Task t;
    if (q.pop(t)) {
        t();
    }

    return 0;
}