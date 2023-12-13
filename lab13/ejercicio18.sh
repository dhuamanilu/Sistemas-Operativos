#!/bin/bash
# Asignaciones
nuevo=${valor}
test ${nuevo} eq ${valor} && echo "Son los mismo"
echo "Ahora ${nuevo} es lo mismo que ${valor}"
