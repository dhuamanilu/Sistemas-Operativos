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
 // Aunque se llama al método de espera, la variable condicional espera
 // se omitirá si los datos ya están listos.
 cv.wait(lk, [] { return ready; });
 // Esto es equivalente a
 // while (!ready())
 // {
 // wait(lock);
 // }
 // Despues de wait, nosotros somos dueños de la cerradura.
 std::cout << "Worker thread esta procesando datos " << std::endl;
 data += " después de procesador ";
 // Envia datos de vuelta al master thread
 processed = true;
 std::cout << "Worker thread señala procesamiento de datos completado " << std::endl;
 // El desbloqueo manual se realiza antes de notificar, para evitar despertar
 // el thread en espera solo se bloquea nuevamente
 lk.unlock();
 cv.notify_one();
}
void master_thread()
{
 std::cout << "Master thread inicia" << std::endl;
 data = "Ejemplo de datos ";
 // Envia datos para el worker thread.
 {
 std::lock_guard lk(m);
 ready = true;
 std::cout << "Master thread señala procesamiento de datos listos "
 << std::endl;
 }
 // La variable de condición se notifica antes que la variable condicional de
 // el worker thread y el master thread comienzan a esperar.
cv.notify_one();
 // Esperando por el worker.
 {
 std::unique_lock lk(m);
 cv.wait(lk, [] { return processed; });
 }
 std::cout << "De vuelta al master thread, data = " << data << std::endl;
}
int main()
{
 std::thread worker(worker_thread), master(master_thread);
 worker.join();
 master.join();
}
