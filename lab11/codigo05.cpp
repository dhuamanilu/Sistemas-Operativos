#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std::placeholders;
class Application
{
std::mutex m_mutex;
 std::condition_variable m_condVar;
 bool m_bDataLoaded;
public:
 Application()
 {
 m_bDataLoaded = false;
 }
 void loadData()
 {
 // haciendo que el thread duerma por 1 segundo
 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 std::cout<<"Cargando datos desde el XML"<<std::endl;
 // Cerrando la estructura de datos
 std::lock_guard<std::mutex> guard(m_mutex);
 // Ingresando la bandera como verdadera, significa que laos datos estan cargados
 m_bDataLoaded = true;
 // Notifica a la variable de condición
 m_condVar.notify_one();
 }
 bool isDataLoaded()
 {
 return m_bDataLoaded;
 }
 void mainTask()
 {
 std::cout<<"Haciendo algo con las manos"<<std::endl;
 // Adquiere la cerradura
 std::unique_lock<std::mutex> mlock(m_mutex);
// Empezar a esperar a que se señale la variable de condición
 // Wait() liberará internamente el bloqueo y hará que el hilo se bloquee
 // Tan pronto como se señale la variable de condición, reanude el hilo y
 // adquirir de nuevo el candado. Luego verifique si la condición se cumple o no
 // Si se cumple la condición, continúe, de lo contrario, vuelva a esperar.
m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
 std::cout<<"Hacer procesamiento sobre los datos cargados"<<std::endl;
 }
};
int main()
{
 Application app;
 std::thread thread_1(&Application::mainTask, &app);
 std::thread thread_2(&Application::loadData, &app);
 thread_2.join();
 thread_1.join();
 return 0;
}
