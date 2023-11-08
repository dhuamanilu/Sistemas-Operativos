// Programa C++ para implementar
// el alojamiento para thread_local
#include <iostream>
#include <thread>
using namespace std;
thread_local int counter = 0;
void increment_counter(){
	counter++;
	cout << "Thread " << this_thread::get_id()
	<< " counter = " << counter << endl;
}
int main(){
	// Crear el primer thread
	thread t1(increment_counter);
	// Crear el segundo thread
	thread t2(increment_counter);
	// Esperar por el primer thread para finalizar
	t1.join();
	// Esperar por el segundo thread para finalizar
	t2.join();
	return 0;
}
