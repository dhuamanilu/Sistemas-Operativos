#include <thread>
#include <mutex>
#include <condition_variable>
#include <syncstream>
#include <iostream>
using namespace std::chrono_literals;
struct Resource {
 bool full = false;
 std::mutex mux;
 // Nota, el std::condition_variable solamente trabaja con c++20
 // std::unique_lock<std::mutex>, para otras combinaciones
 // usar std::condition_variable_any la cual puede ser menos eficiente.
 std::condition_variable cond;
 void produce() {
 {
 std::unique_lock lock(mux);
 // espera hasta que la codicion es verdadera
 // 1. el bloqueo se libera
 // 2. cuando el thread es despertado, la cerradura es adquirida
 // y la condición es verificada
 // 3. si la condición es aun no verdadera, la cerradura
 // es reliberdada, y vamos al paso 2.
 // 4. si la condición es verdadera, el wait() llama para finalizar
 cond.wait(lock, [this]{ return !full; });
 std::osyncstream(std::cout) <<
 "LLenando el recurso y notificando al consumidor.\n";
 full = true;
 std::this_thread::sleep_for(200ms);
}
// despierta un hilo esperando en esta variable de condición
 // tenga en cuenta que ya liberamos nuestro bloqueo, de lo contrario
 // el subproceso notificado se despertaría y no podría adquirir
 // la cerradura y se suspende de nuevo
 cond.notify_one();
 }
 void consume() {
 {
 std::unique_lock lock(mux);
// igual que arriba, pero con semántica opuesta
 cond.wait(lock, [this]{ return full; });
 std::osyncstream(std::cout) <<
 "Consumiendo el recurso y notificando al productor.\n";
 full = false;
 std::this_thread::sleep_for(200ms);
}
 cond.notify_one();
 }
};
int main() {
 Resource resource;
 auto t1 = std::jthread([&resource](std::stop_token token){
 while (!token.stop_requested())
 resource.produce();
 });
 auto t2 = std::jthread([&resource](std::stop_token token){
 while (!token.stop_requested())
 resource.consume();
 });
 std::this_thread::sleep_for(2s);
 t1.request_stop();
 t2.request_stop();
// Nota: usar request_stop aquí no es seguro.
 // Si eliminamos sleep_for, el subproceso t2 podría
 // ejecuta un bucle completo antes de que se dé cuenta de la solicitud de parada
 // y considerando que t1 ya no corre, el bloqueo
 // la condición nunca se cumpliría.
 // Esto se puede evitar usando condition_variable_any,
 // que admite un token de parada o un tiempo de espera.
}
