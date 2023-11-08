#include <iostream>
#include <thread>
void foo(){
	std::cout<<"estoy en foo";
}
void bar(){
	std::cout<<"estoy en bar";
}
int main(){
	std::thread th(foo);
	std::thread hr(bar);
	th.join();
	hr.join();
	return 0;
}
/* Crear una clase con funciones miembro, que sean llamadas por un thread */
