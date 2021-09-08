#! /usr/bin/sh

for dir in lab_*
do
    cd $dir || exit 1
    echo "$dir:\n"
    for file in *.c
    do
        echo "$file:"
        code_checker $file
        echo "___"
    done
    for file in *.h
    do
        echo "$file:"
        code_checker $file
        echo "___"
    done
    cd ..
done