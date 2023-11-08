#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;  // Mutex para proteger la variable

void thread_func(int& counter) {
    for (int i = 0; i < 10000; i++) {
        // Bloquea el mutex antes de modificar la variable
        mtx.lock();
        counter++;
        mtx.unlock();  // Desbloquea el mutex después de la modificación
    }
}

int main() {
    int counter = 0;

    thread t1(thread_func, std::ref(counter));
    thread t2(thread_func, std::ref(counter));

    t1.join();
    t2.join();

    cout << "Valor final de la variable: " << counter << endl;

    return 0;
}
