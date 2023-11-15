class Semaforo implements Runnable {
    private String nombre;
    private int tiempoEspera;

    public Semaforo(String nombre, int tiempoEspera) {
        this.nombre = nombre;
        this.tiempoEspera = tiempoEspera;
    }

    @Override
    public void run() {
        while (true) {
            switch (nombre) {
                case "Rojo":
                    imprimirEnColor("Semáforo " + nombre, ANSI_RED);
                    break;
                case "Amarillo":
                    imprimirEnColor("Semáforo " + nombre, ANSI_YELLOW);
                    break;
                case "Verde":
                    imprimirEnColor("Semáforo " + nombre, ANSI_GREEN);
                    break;
                default:
                    break;
            }

            try {
                Thread.sleep(tiempoEspera);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    // Función para imprimir en color en la consola
    private void imprimirEnColor(String mensaje, String color) {
        System.out.println(color + mensaje + ANSI_RESET);
    }

    // Códigos ANSI para colores
    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_YELLOW = "\u001B[33m";
    private static final String ANSI_GREEN = "\u001B[32m";
}

public class SemaforoPrograma {
    public static void main(String[] args) {
        // Crear dos semáforos con diferentes tiempos de espera
        Thread semaforoRojo = new Thread(new Semaforo("Rojo", 3000));
        Thread semaforoAmarillo = new Thread(new Semaforo("Amarillo", 1000));
        Thread semaforoVerde = new Thread(new Semaforo("Verde", 2000));

        // Iniciar los threads de los semáforos
        semaforoRojo.start();
        semaforoAmarillo.start();
        semaforoVerde.start();
    }
}
