#!/bin/bash

# Verificar si el directorio actual existe
if [ -d "$(pwd)" ]; then
    # Enlistar todos los archivos en el directorio actual
    echo "Archivos en el directorio actual:"
    ls -l
else
    echo "El directorio actual no existe."
fi
