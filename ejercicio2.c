#include <stdio.h>

int main() {
    int num1, num2;

    // Solicitar al usuario los dos números enteros
    printf("Ingresa el primer número entero: ");
    scanf("%d", &num1);

    printf("Ingresa el segundo número entero: ");
    scanf("%d", &num2);

    // Realizar las operaciones y mostrar los resultados
    int suma = num1 + num2;
    int resta = num1 - num2;
    int multiplicacion = num1 * num2;

    // Verificar la división por cero
    if (num2 != 0) {
        double division = (double)num1 / num2;
        int resto = num1 % num2;
        
        printf("Suma: %d\n", suma);
        printf("Resta: %d\n", resta);
        printf("Multiplicación: %d\n", multiplicacion);
        printf("División: %.2lf\n", division);
        printf("Resto (Módulo de la división): %d\n", resto);
    } else {
        printf("No es posible dividir por cero.\n");
    }

    return 0;
}
