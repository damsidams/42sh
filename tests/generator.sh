#bin/bash

function generate_test() {
    if [ $1 = "-h" ]; then
        echo "
        add a new test for your 42sh project:
        you will need 4 arguments:
            - 1: the number of your test (ex: 1, 2, 3, 4)
            - 2: the name of your test (ex: "simple ls command")
            - 3: the command you want to execute (ex: "ls")
            - 4: the file you want to write your test in
        "
    else
        echo "
        ##$2
        mkdir tnum/$1 -p
        echo \"$3\" | ./42sh &> tnum/$1/output
        echo \"$3\" | tcsh  &> tnum/$1/desired
        if diff -q tnum/$1/desired tnum/$1/output; then
            echo -e \"\e[32m[TEST $1] $2 Test PASSED\e[0m\"
        else
            echo -e \"\e[31m[TEST $1] $2 Test NOT PASSED\e[0m\"
        fi" >> $4
    fi
}