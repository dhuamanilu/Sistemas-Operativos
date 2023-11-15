class TestTh extends Thread {
 private String nombre;
 private int retardo;
 // Constructor para almacenar nuestro nombre
 // y el retardo
 public TestTh( String s,int d ) {
 nombre = s;
 retardo = d;
 }
 // El metodo run() es similar al main(), pero para
 // threads. Cuando run() termina el thread muere
 public void run() {
 // Retasamos la ejecución el tiempo especificado
 try {
 sleep( retardo );
 } catch( InterruptedException e ) {
 ;
 }
 // Ahora imprimimos el nombre
 System.out.println( "Hola Mundo! "+nombre+" "+retardo );
 }
 }
public class MultiHola2 {
 public static void main( String args[] ) {
 TestTh t1,t2,t3,t4,t5,t6,t7;
 // Creamos los threads
 t1 = new TestTh( "Thread 1",(int)(Math.random()*2000) );
 t2 = new TestTh( "Thread 2",(int)(Math.random()*2000) );
 t3 = new TestTh( "Thread 3",(int)(Math.random()*2000) );
 t4 = new TestTh( "Thread 4",(int)(Math.random()*2000) );
 t5 = new TestTh( "Thread 5",(int)(Math.random()*2000) );
t6 = new TestTh( "Thread 6",(int)(Math.random()*2000) );
 t7 = new TestTh( "Thread 7",(int)(Math.random()*2000) );

 // Arrancamos los threads
 t1.start();
 t2.start();
 t3.start();
 t4.start();
 t5.start();
 t6.start();
t7.start();
 }
 }
