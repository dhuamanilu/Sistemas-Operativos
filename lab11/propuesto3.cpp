#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mutex_;
std::condition_variable condVar;

void doTheWork() {
    std::cout << "Procesando datos compartidos." << std::endl;
}

void waitingForWork() {
    std::cout << "Worker: esperando por trabajo." << std::endl;
    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck);
    doTheWork();
    std::cout << "Trabajo hecho." << std::endl;
}

void setDataReady() {
    std::cout << "Enviador: Datos estan listos." << std::endl;
    condVar.notify_one();
}

int main() {
    std::cout << std::endl;

    // Crear 4 threads adicionales
    std::thread t3(waitingForWork);
    std::thread t4(waitingForWork);
    std::thread t5(waitingForWork);
    std::thread t6(waitingForWork);

    // Lanzar los threads existentes
    std::thread t1(waitingForWork);
    std::thread t2(setDataReady);

    // Unirse a todos los threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << std::endl;

    return 0;
}
