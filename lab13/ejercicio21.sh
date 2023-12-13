#!/bin/bash
touch fichero_prueba # touch crea un fichero en blanco
if [ -f fichero_prueba ];
then
 echo "El fichero existe"
fi
