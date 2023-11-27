#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
int main()
{
 std::condition_variable cond;
 std::mutex mtx;
 std::queue<int> intq;
 bool stopped = false;
 std::thread producer{[&]()
 {
 // Preparar un generador de numeros aleatorios.
 // El productor ingresa numeros aleatorios a intq.
 //
 std::default_random_engine gen{};
 std::uniform_int_distribution<int> dist{};
 std::size_t count = 4006;
 while(count--)
 {
 // Siempre bloquea antes de cambiar
 // El estado es guardado por un mutex y
 // también afecta a la variable de condición (cond).
 std::lock_guard<std::mutex> L{mtx};
// Ingresa un entero aleatorio dentro de la cola
 intq.push(dist(gen));
 // Habla al consumidor que tiene un entero
 cond.notify_one();
 }
 // Todo hecho.
 // Adquiere la cerradura, establece la bandera detenida,
 // entonces informa al consumidor.
 std::lock_guard<std::mutex> L{mtx};
 std::cout << "Productor esta hecho!" << std::endl;
 stopped = true;
 cond.notify_one();
}};
 std::thread consumer{[&]()
 {
 do{
 std::unique_lock<std::mutex> L{mtx};
 cond.wait(L,[&]()
 {
 // Adquiere el candado solo si
 // nos hemos detenido o la cola
 // no esta vacia
 return stopped || ! intq.empty();
 });
 // Somos dueños del mutex aqui, salida de la cola
 // hasta vaciarla.
 while( ! intq.empty())
 {
 const auto val = intq.front();
 intq.pop();
 std::cout << "Consumidor saca: " << val << std::endl;
 }
 if(stopped){
 // productor ha señalado una parada
 std::cout << "Consumidor esta hecho!" << std::endl;
 break;
 }
 }while(true);
 }};
 consumer.join();
 producer.join();
std::cout << "¡Ejemplo completo!" << std::endl;
 return 0;
}
