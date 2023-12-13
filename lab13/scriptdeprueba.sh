#!/bin/bash
# Otras variables especiales
# $# : Número de argumentos
echo "Me has pasado $# argumentos"
# $@ : grupo de parámetros del script
echo IDa: $@
# Variables de entorno
echo "Mi directorio actual: ${PWD} y mi usuario ${UID}"
