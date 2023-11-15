class Tarea implements Runnable {
    private String nombre;

    public Tarea(String nombre) {
        this.nombre = nombre;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(nombre + " - Iteración " + i);
            // Puedes agregar alguna lógica o tarea específica que realizará el hilo en cada iteración
            try {
                // Agregamos una pequeña pausa para simular un trabajo en el hilo
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class Principal {
    public static void main(String[] args) {
        Thread hilo1 = new Thread(new Tarea("hilo1"));
        Thread hilo2 = new Thread(new Tarea("hilo2"));

        hilo1.start();
        hilo2.start();
    }
}
