#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
void worker_thread()
{
 std::cout << "Worker iniciar thread " << std::endl;
 std::unique_lock lk(m);
 cv.wait(lk, [] { return ready; });
 // Despues de wait, cerramos
 std::cout << "Worker thread esta procesando datos" << std::endl;
 data += " después de procesado ";
 // Envia datos devuelta al master thread
processed = true;
 std::cout << "Worker thread signals completa el procesamiento de datos " << std::endl;
 // Liberado manual hecho antes que se notifique previniendo el despertar
 // El thread despierta solamente para el bloque nuevamente
 lk.unlock();
 // El worker thread ha hecho su trabajo,
 // Se notifica a master thread para continuar el trabajo.
 cv.notify_one();
}
void master_thread()
{
 std::cout << "Master thread inicia" << std::endl;
data = "Ejemplo de dato";
 // Envia datos al worker thread.
 {
 std::lock_guard lk(m);
 ready = true;
 std::cout << "Los datos de Master thread signals listo para ser procesados"
 << std::endl;
 }
 // The mater thread ha hecho su trabajo preliminar,
 // Notifica a worker thread para continuar el trabajo.
 cv.notify_one();
 // Esperando para el worker.
 {
 std::unique_lock lk(m);
 cv.wait(lk, [] { return processed; });
 }
 std::cout << "Devuelta en master thread, datos = " << data << std::endl;
}
int main()
{
 std::thread worker(worker_thread), master(master_thread);
 // Workflow:
 // master thread -> worker thread -> master thread.
 worker.join();
 master.join();
}
