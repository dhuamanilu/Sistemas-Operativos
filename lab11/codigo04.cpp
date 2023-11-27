// conditionVariable.cpp
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
std::mutex mutex_;
std::condition_variable condVar;
void doTheWork(){
std::cout << "Procesando datos compartidos." << std::endl;
}
void waitingForWork(){
 std::cout << "Worker: esperando por trabajo." << std::endl;
 std::unique_lock<std::mutex> lck(mutex_);
 condVar.wait(lck);
 doTheWork();
std::cout << "Trabajo hecho." << std::endl;
}
void setDataReady(){
 std::cout << "Enviador: Datos estan listos." << std::endl;
 condVar.notify_one();
}
int main(){
 std::cout << std::endl;
 std::thread t1(waitingForWork);
 std::thread t2(setDataReady);
 t1.join();
 t2.join();
 std::cout << std::endl;

}
