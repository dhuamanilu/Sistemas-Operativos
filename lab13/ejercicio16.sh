#!/bin/bash
booleano=true
$booleano && echo "OK" || echo "no es true"
otrobool=${!booleano}
test ${otrobool} || echo "Ahora es falso"
