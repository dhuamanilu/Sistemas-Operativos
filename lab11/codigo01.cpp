// ejemplo de variable de condición
#include <iostream> // std::cout
#include <thread> // std::thread
#include <mutex> // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
void print_id (int id) {
 std::unique_lock<std::mutex> lck(mtx);
 while (!ready) cv.wait(lck);
 // ...
 std::cout << "thread " << id << '\n';
}
void go() {
 std::unique_lock<std::mutex> lck(mtx);
 ready = true;
 cv.notify_all();
}
int main ()
{
 std::thread threads[10];
 // aparecen 10 threads:
 for (int i=0; i<10; ++i)
 threads[i] = std::thread(print_id,i);
 std::cout << "10 threads listos para la carrera...\n";
 go(); // vamos
 for (auto& th : threads) th.join();
 return 0;
}
