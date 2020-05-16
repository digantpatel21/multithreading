#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void fun(int number) {
    for (int index = 0; index < number; index++)
    {
        cout<<"Index is "<<index<<endl;
        chrono::milliseconds(100);
    }
}

class threadClass {
    public:
    void operator()(int number) {
        for (int index = 0; index < number; index++)
        {
            cout<<"Index is "<<index<<endl;
            chrono::milliseconds(100);
        }

    }
};

int main() {

    // Thread creation by function calling
    thread th1(fun, 10);
    th1.join();
    //thread creation by lambda functions
    auto f = [](int x) {
        for (int index = 0; index < x ;index++)
        {
            cout<<"thread 2:Index is "<<index<<endl;
            chrono::milliseconds(100);
        }

    };

    thread th2(f,5);
    th2.join();
    // Thread creation by callable class object
    thread th3(threadClass(), 15);

    th3.join();
    return 0;
}