#include <stdio.h>
int foo (unsigned int x){
	 if (x < 0)
		  return 0; /* no puede ocurrir */
	  else
		   return 1;
}
int main(void){
	printf("El valor de la funcion es %d",foo(0));
	return 0;
}

