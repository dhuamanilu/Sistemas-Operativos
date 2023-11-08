// Programa en C++ para demostrar el uso de
// std::thread::get_id
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
// funcion util function para la creacion de thread
void sleepThread(){
	this_thread::sleep_for(chrono::seconds(1));
}
int main(){
	// creando thread1 y thread2
	thread thread1(sleepThread);
	thread thread2(sleepThread);
	thread::id t1_id = thread1.get_id();
	thread::id t2_id = thread2.get_id();
	cout << "ID asociado con thread1= "
	<< t1_id << endl;
	cout << "ID asociado con thread2= "
	<< t2_id << endl;
	thread1.join();
	thread2.join();
	return 0;
}
