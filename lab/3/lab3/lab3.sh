#!/bin/bash	

read -p 'Username: ' uservar
read -sp 'Password: ' passvar

echo "Username: $uservar, Password: $passvar" > saveCredential.txt

