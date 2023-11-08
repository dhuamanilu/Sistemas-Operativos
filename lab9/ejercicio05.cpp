// Programa en C++ para demostrar el uso del thread-local
// alojada.
#include <iostream>
#include <thread>
using namespace std;
class Singleton {
public:
	static Singleton& getInstance(){
		// Cada thread tendria su propia instancia de
		// Singleton
		thread_local Singleton instance;
		return instance;
	}
	void printMessage(){
		cout << "Hola desde el thread "
		<< this_thread::get_id() << endl;
	}
private:
	Singleton() = default;
};
void workerThread(){
	Singleton::getInstance().printMessage();
}
int main(){
	// Crear el primer thread
	thread t1(workerThread);
	// Crear el segundo thread
	thread t2(workerThread);
	// Esperar por el primer thread para finalizar
	t1.join();
	// Esperar para el segundo thread para finalizar
	t2.join();
	return 0;
}
