#!/bin/bash
# Pruebas
VALOR1=23
VALOR2=45
# Para las operaciones puede usarse expr o []
RESULTADO=`expr ${VALOR1} + ${VALOR2}`
echo "Resultado: ${RESULTADO}"
