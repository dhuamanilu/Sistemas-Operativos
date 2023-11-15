class TestTh2 extends Thread {
    private String nombre;
    private int retardo;

    // Constructor para almacenar nuestro nombre y el retardo
    public TestTh2(String s, int d) {
        nombre = s;
        retardo = d;
    }

    // El método run() es similar al main(), pero para threads.
    // Cuando run() termina, el thread muere.
    public void run() {
        // Retrasamos la ejecución el tiempo especificado
        try {
            sleep(retardo);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        // Ahora imprimimos el nombre
        System.out.println("Hola Mundo! " + nombre + " " + retardo);
    }
}

public class Propuesto2 {
    public static void main(String args[]) {
        // Creamos un arreglo de TestTh
        TestTh2[] threads = new TestTh2[7];

        // Inicializamos los threads con nombres y retardos aleatorios
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new TestTh2("Thread " + (i + 1), (int) (Math.random() * 2000));
        }

        // Arrancamos los threads usando un bucle
        for (TestTh2 thread : threads) {
            thread.start();
        }
    }
}
