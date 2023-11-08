#include <iostream>
#include <thread>

void func1() {
    for (int i = 0; i < 3; i++) {
        std::cout << "Función 1 - Iteración " << i << std::endl;
    }
}

void func2() {
    for (int i = 0; i < 3; i++) {
        std::cout << "Función 2 - Iteración " << i << std::endl;
    }
}

int main() {
    std::thread th1(func1);
    std::thread th2(func1);  // Segundo thread para func1
    std::thread th3(func2);
    std::thread th4(func2);  // Segundo thread para func2

    th1.join();
    th2.join();
    th3.join();
    th4.join();

    return 0;
}
