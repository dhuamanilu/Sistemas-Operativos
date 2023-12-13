#!/bin/bash
# Y lo contrario: si la variable SÍ tiene valor, se le pone otro
# ${variable:+valorpordefecto}
PROGRAMA='sniffit'
echo "valor de PROGRAMA: ${PROGRAMA:+'tcpdump'} y ahora ${PROGRAMA}"
