#!/bin/bash
VALOR1=5
VALOR2=4
echo "${VALOR1} y ${VALOR2}"
RESULTADO=$[${VALOR1} + $[${VALOR2} * 3]]
echo "Ahora: ${VALOR1} + ${VALOR2} * 3 = ${RESULTADO}"
