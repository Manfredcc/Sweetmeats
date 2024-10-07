#include <iostream>
#include <thread>
#include "timeScoped.h"

using namespace std;

timeScoped<50> xxc("data.csv");

void hello()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

int main()
{
    cout << "call main" << endl;
    int i = 0;
    while (i++ < 51) {
        xxc.start();
        hello();
        xxc.end();
    }
}