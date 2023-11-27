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
 // Dormir el worker thread por 1 segundo y que la variable de condición
 // es notificada en el master thread antes que la variable de condición inicie
 // esperar en el worker thread.
 std::this_thread::sleep_for(std::chrono::seconds(1));
 std::cout << "Worker thread inicia" << std::endl;
 std::unique_lock lk(m);
 // A menos que se produzca una reactivación espuria, el hilo será bloqueado
 // porque la variable de condición no recibe ninguna notificación.
 cv.wait(lk);
 // Después de esperar , nos apoderamos de la cerradura.
 std::cout << "Worker thread está procesando datos" << std::endl;
 data += " después de procesado ";
 // Envia datos de vuelta al master thread
 processed = true;
 std::cout << "Worker thread señala que los datos han sido procesados " << std::endl;
 // Desbloqueo Manual hecho antes de notificar, para evitar desperat
 // el hilo en espera solo para bloquearse nuevamente
 lk.unlock();
 cv.notify_one();
}
void master_thread()
{
std::cout << "Master thread inicia" << std::endl;
 data = "Ejemplo de datos";
 // Envia datos al worker thread.
 {
 std::lock_guard lk(m);
 ready = true;
 std::cout << "Master thread señala que los datos están listos para ser procesados "
 << std::endl;
 }
 // La variable de condición se notifica antes que la variable condicional de
 // worker thread y master thread comienzan a esperar.
 cv.notify_one();
 // Wait for the worker.
 {
 std::unique_lock lk(m);
 // El master thread es bloqueado la variable de condición no obtiene
 // notificacion.
 cv.wait(lk);
 }
 std::cout << "Devuelta en el master thread, datos = " << data << std::endl;
}
int main()
{
 std::thread worker(worker_thread), master(master_thread);
 worker.join();
 master.join();
}
