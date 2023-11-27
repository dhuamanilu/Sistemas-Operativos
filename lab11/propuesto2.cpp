#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

std::condition_variable_any cv;
std::mutex cv_m;
int i;

void waits(int idx)
{
    std::unique_lock<std::mutex> lk(cv_m);
    auto deadline = std::chrono::steady_clock::now() + idx * 100ms;
    
    if (cv.wait_until(lk, deadline, [] { return i == 1; }))
        std::cerr << "Thread " << idx << " espera finalizada. i == " << i << '\n';
    else
        std::cerr << "Thread " << idx << " tiempo fuera. i == " << i << '\n';
}

void signals()
{
    std::this_thread::sleep_for(120ms);
    std::cerr << "Notificando...\n";
    cv.notify_all();
    std::this_thread::sleep_for(100ms);
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
    }
    std::cerr << "Notificando de nuevo...\n";
    cv.notify_all();
}

int main()
{
    std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
