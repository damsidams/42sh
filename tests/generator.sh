#bin/bash

function generate_test() {
    if [ "$1" = "-h" ]; then
        echo "generate_test n t_name cmd"
        echo "n         test num"
        echo "t_nname   test name"
        echo "cmd       test cmd"
    else
        echo "
        ##$2
        mkdir tnum/$1 -p
        echo \"$3\" | ./42sh > tnum/$1/output
        echo \"$3\" | tcsh  > tnum/$1/desired
        if diff -q tnum/$1/desired tnum/$1/output; then
            echo -e \"\e[32m[TEST $1] $2 Test PASSED\e[0m\"
        else
            echo -e \"\e[31m[TEST $1] $2 Test NOT PASSED\e[0m\"
        fi" >> $4
    fi
}