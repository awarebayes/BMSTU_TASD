#! /usr/bin/bash

cd $1 || exit 1
# gcc -std=c99 -Werror -Wall -lm ./main.c -o ./main
cd ./func_tests || exit 1
for TEST in $(ls | grep _in.txt | sed 's/_[^_]*//2g')
do
    if [ -s ${TEST}_in.txt ]
    then
        if ! diff ./${TEST}_out.txt <(../main < ./${TEST}_in.txt) > /dev/null
        then
            echo "_____________"
            echo "$TEST failed:"
            diff -y ./${TEST}_out.txt <(../main < ./${TEST}_in.txt)
            echo "_____________"
        fi
    fi
done