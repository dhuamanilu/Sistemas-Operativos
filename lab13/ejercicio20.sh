#!/bin/bash
user=root
if grep $user /etc/passwd; then
 echo "Solo existe esto del usuario $user"
fi
