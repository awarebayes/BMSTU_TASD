#! /usr/bin/sh
cd "$1" || exit
echo "$1"
for file in *.c
do
    gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -c "$file"
done

if gcc -o main $(echo *.o | cut -f1 -d-)
then
    echo "🚀 Build succsessful!"
else 
    echo "🤔 Build failed!"
fi