#include <stdio.h>

// Definir la constante PI
#define PI 3.14159265359

int main() {
	double radio, area;

	// Solicitar al usuario el valor del radio
	printf("Ingresa el valor del radio de la circunferencia: ");
	scanf("%lf", &radio);

        // Calcular el área de la circunferencia
        area = PI * radio * radio;

        // Mostrar el resultado
	printf("El área de la circunferencia con radio %.2lf es %.2lf\n", radio, area);

}
