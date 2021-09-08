#! /usr/bin/sh

for dir in $(ls | grep lab_06)
do
    echo "DIR: $dir:\n"
    # bash ./scripts/run_test.sh $dir
    cd ./$dir/func_tests || exit 1
    bash run.sh
    cd ../../
done