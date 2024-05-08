(cd .. && make && cp 42sh tests/.)

##simple command (not built-in)
mkdir tnum/1 -p
echo "ls" | ./42sh > tnum/1/output
ls > tnum/1/desired
if diff -q tnum/1/desired tnum/1/output; then
    echo -e "\e[32m[TEST 1] simple command Test PASSED\e[0m"
else
    echo -e "\e[31m[TEST 1] simple command Test NOT PASSED\e[0m"
fi

##simple pipe
mkdir tnum/2 -p
echo "ls | cat -e" | ./42sh > tnum/2/output
ls | cat -e > tnum/2/desired
if diff -q tnum/2/desired tnum/2/output; then
    echo -e "\e[32m[TEST 2] simple pipe Test PASSED\e[0m"
else
    echo -e "\e[31m[TEST 2] simple pipe Test NOT PASSED\e[0m"
fi


        ##Simple alias
        mkdir tnum/3 -p
        echo "alias ll \"ls -l\" && ll" | ./42sh > tnum/3/output
        echo "alias ll \"ls -l\" && ll" | tcsh  > tnum/3/desired
        if diff -q tnum/3/desired tnum/3/output; then
            echo -e "\e[32m[TEST 3] Simple alias Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 3] Simple alias Test NOT PASSED\e[0m"
        fi

        ##Multiple pipe 1
        mkdir tnum/4 -p
        echo "ls | grep Makefile | cat -e" | ./42sh > tnum/4/output
        echo "ls | grep Makefile | cat -e" | tcsh  > tnum/4/desired
        if diff -q tnum/4/desired tnum/4/output; then
            echo -e "\e[32m[TEST 4] Multiple pipe 1 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 4] Multiple pipe 1 Test NOT PASSED\e[0m"
        fi

        ##alias and Multiple pipe
        mkdir tnum/5 -p
        echo "alias ll \"ls -l \" && ll | grep Makefile | cat -e" | ./42sh > tnum/5/output
        echo "alias ll \"ls -l \" && ll | grep Makefile | cat -e" | tcsh  > tnum/5/desired
        if diff -q tnum/5/desired tnum/5/output; then
            echo -e "\e[32m[TEST 5] alias and Multiple pipe Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 5] alias and Multiple pipe Test NOT PASSED\e[0m"
        fi
