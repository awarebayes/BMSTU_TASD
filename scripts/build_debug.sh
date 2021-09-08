#! /usr/bin/sh
cd "$1" || exit
echo "$1"
for file in *.c
do
    gcc -std=c99 -Og -g "$file"
done

if gcc -o main $(echo *.o | cut -f1 -d-)
then
    echo "🚀 Debug build succsessful!"
else 
    echo "🤔 Debug build failed!"
fi