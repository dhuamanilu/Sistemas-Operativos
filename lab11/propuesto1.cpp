#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    while (!ready) {
        cv.wait(lck);
    }
    std::cout << "thread " << id << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    const int num_threads = 50;
    std::thread threads[num_threads];

    // Crear 50 threads
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(print_id, i);
    }

    std::cout << num_threads << " threads listos para la carrera...\n";
    go(); // vamos

    for (auto &th : threads) {
        th.join();
    }

    return 0;
}
