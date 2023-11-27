#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
void worker_thread()
{
 // Espere hasta que main () envíe datos
 std::unique_lock lk(m);
 cv.wait(lk, []{return ready;});
 // después de la espera, somos dueños de la cerradura.
 std::cout << "El thread Worker esta procesando datos\n";
 data += " despues de procesar";
 // Enviar datos de vuelta a main ()
 processed = true;
 std::cout << "Las senales de datos del thread Worker son procesadas completamente\n";
 // El desbloqueo manual se realiza antes de notificar, para evitar despertar
 // el hilo en espera solo para volver a bloquearse (ver notificar_uno para más detalles)
 lk.unlock();
 cv.notify_one();
}
int main()
{
 std::thread worker(worker_thread);
 data = "Data de ejemplo";
// enviar datos al hilo de trabajo
 {
std::lock_guard lk(m);
 ready = true;
 std::cout << "main() los datos de las senales estan listos para ser procesados\n";
 }
 cv.notify_one();
 // espera al trabajador
 {
 std::unique_lock lk(m);
 cv.wait(lk, []{return processed;});
 }
 std::cout << "Volviendo al main(), datos = " << data << '\n';
 worker.join();
}
