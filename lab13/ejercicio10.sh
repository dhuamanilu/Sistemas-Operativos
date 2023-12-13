#!/bin/bash
# Esto es igual pero el valor queda establecido
# ${variable:=valorpordefecto}
echo "Variable SINVALOR: ${SINVALOR:=31337} eta ${VACIO:='Miguel Indurain'}"
echo "La variable SINVALOR no tiene valor algun ${SINVALOR} "
