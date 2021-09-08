#! /usr/bin/sh

for dir in $(ls | grep lab_)
do
    echo "DIR: $dir:"
    cd $dir/func_tests || continue
    for TEST in $(ls | grep _in.txt | sed 's/_[^_]*//2g')
    do
        if ! [ -s ${TEST}_in.txt ]
        then
            rm ${TEST}_in.txt
        fi
        if ! [ -s ${TEST}_out.txt ]
        then
            rm ${TEST}_out.txt
        fi
    done
    cd ../..
done