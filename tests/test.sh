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

        ##Multiple commands
        mkdir tnum/6 -p
        echo "ls | cat -e; pwd; echo pls; cd" | ./42sh > tnum/6/output
        echo "ls | cat -e; pwd; echo pls; cd" | tcsh  > tnum/6/desired
        if diff -q tnum/6/desired tnum/6/output; then
            echo -e "\e[32m[TEST 6] Multiple commands Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 6] Multiple commands Test NOT PASSED\e[0m"
        fi

        

        ##Simple backtick
        mkdir tnum/7 -p
        echo "\`ls -l\` | cat -e | grep test" | ./42sh &> tnum/7/output
        echo "\`ls -l\` | cat -e | grep test" | tcsh  &> tnum/7/desired
        if diff -q tnum/7/desired tnum/7/output; then
            echo -e "\e[32m[TEST 7] Simple backtick Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 7] Simple backtick Test NOT PASSED\e[0m"
        fi


        ##Simple backtick 2
        mkdir tnum/9 -p
        echo "`pwd` | cat -e" | ./42sh &> tnum/9/output
        echo "`pwd` | cat -e" | tcsh  &> tnum/9/desired
        if diff -q tnum/9/desired tnum/9/output; then
            echo -e "\e[32m[TEST 9] Simple backtick 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 9] Simple backtick 2 Test NOT PASSED\e[0m"
        fi

        ##Multiple commands with separator
        mkdir tnum/11 -p
        echo "echo toto | grep toto; ls; echo op || echo ops; ls" | ./42sh &> tnum/11/output
        echo "echo toto | grep toto; ls; echo op || echo ops; ls" | tcsh  &> tnum/11/desired
        if diff -q tnum/11/desired tnum/11/output; then
            echo -e "\e[32m[TEST 11] Multiple commands with separator || Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 11] Multiple commands with separator || Test NOT PASSED\e[0m"
        fi

        
        ##Multiple commands with separator &&
        mkdir tnum/13 -p
        echo "echo toto | grep toto; ls; echo op && echo ops; ls" | ./42sh &> tnum/13/output
        echo "echo toto | grep toto; ls; echo op && echo ops; ls" | tcsh  &> tnum/13/desired
        if diff -q tnum/13/desired tnum/13/output; then
            echo -e "\e[32m[TEST 13] Multiple commands with separator && Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 13] Multiple commands with separator && Test NOT PASSED\e[0m"
        fi

        
        ##Multiple commands with separator && and ||
        mkdir tnum/15 -p
        echo "echo \"echo toto | grep toto\" || echo yes && pwd; ls; echo op && echo ops; ls" | ./42sh &> tnum/15/output
        echo "echo \"echo toto | grep toto\" || echo yes && pwd; ls; echo op && echo ops; ls" | tcsh  &> tnum/15/desired
        if diff -q tnum/15/desired tnum/15/output; then
            echo -e "\e[32m[TEST 15] Multiple commands with separator && and || Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 15] Multiple commands with separator && and || Test NOT PASSED\e[0m"
        fi

        ##Multiple commands with separator && and || 2
        mkdir tnum/17 -p
        echo "fepf || echo yes && pwd; ls; echo op && echo ops || ferr; ls" | ./42sh &> tnum/17/output
        echo "fepf || echo yes && pwd; ls; echo op && echo ops || ferr; ls" | tcsh  &> tnum/17/desired
        if diff -q tnum/17/desired tnum/17/output; then
            echo -e "\e[32m[TEST 17] Multiple commands with separator && and || 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 17] Multiple commands with separator && and || 2 Test NOT PASSED\e[0m"
        fi

        ##Multiple commands with separator && and || 3
        mkdir tnum/19 -p
        echo "fepf || fihifh || hferofhi || jfei || jofjf || echo ok || diehd && echo and" | ./42sh &> tnum/19/output
        echo "fepf || fihifh || hferofhi || jfei || jofjf || echo ok || diehd && echo and" | tcsh  &> tnum/19/desired
        if diff -q tnum/19/desired tnum/19/output; then
            echo -e "\e[32m[TEST 19] Multiple commands with separator && and || 3 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 19] Multiple commands with separator && and || 3 Test NOT PASSED\e[0m"
        fi

        ##Multiple commands with separator && and || 4
        mkdir tnum/21 -p
        echo "fepf && fihifh && hferofhi && jfei && jofjf && echo ok && diehd && echo and" | ./42sh &> tnum/21/output
        echo "fepf && fihifh && hferofhi && jfei && jofjf && echo ok && diehd && echo and" | tcsh  &> tnum/21/desired
        if diff -q tnum/21/desired tnum/21/output; then
            echo -e "\e[32m[TEST 21] Multiple commands with separator && and || 4 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 21] Multiple commands with separator && and || 4 Test NOT PASSED\e[0m"
        fi

        ##Multiple commands with separator && and || 5
        mkdir tnum/23 -p
        echo "ls && pwd && date && cd && pwd && echo ok || diehd && echo and" | ./42sh &> tnum/23/output
        echo "ls && pwd && date && cd && pwd && echo ok || diehd && echo and" | tcsh  &> tnum/23/desired
        if diff -q tnum/23/desired tnum/23/output; then
            echo -e "\e[32m[TEST 23] Multiple commands with separator && and || 5 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 23] Multiple commands with separator && and || 5 Test NOT PASSED\e[0m"
        fi

        
        ##Simple globbing 1
        mkdir tnum/25 -p
        echo "echo *" | ./42sh &> tnum/25/output
        echo "echo *" | tcsh  &> tnum/25/desired
        if diff -q tnum/25/desired tnum/25/output; then
            echo -e "\e[32m[TEST 25] Simple globbing 1 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 25] Simple globbing 1 Test NOT PASSED\e[0m"
        fi

        
        ##Simple globbing 2
        mkdir tnum/27 -p
        echo "echo *.sh || ls" | ./42sh &> tnum/27/output
        echo "echo *.sh || ls" | tcsh  &> tnum/27/desired
        if diff -q tnum/27/desired tnum/27/output; then
            echo -e "\e[32m[TEST 27] Simple globbing 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 27] Simple globbing 2 Test NOT PASSED\e[0m"
        fi

        ##Simple globbing 3
        mkdir tnum/29 -p
        echo "echo ??.sh || ls" | ./42sh &> tnum/29/output
        echo "echo ??.sh || ls" | tcsh  &> tnum/29/desired
        if diff -q tnum/29/desired tnum/29/output; then
            echo -e "\e[32m[TEST 29] Simple globbing 3 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 29] Simple globbing 3 Test NOT PASSED\e[0m"
        fi

        ##Globbing OR and redirect
        mkdir tnum/31 -p
        echo "echo ??.sh || ls | cat -e" | ./42sh &> tnum/31/output
        echo "echo ??.sh || ls | cat -e" | tcsh  &> tnum/31/desired
        if diff -q tnum/31/desired tnum/31/output; then
            echo -e "\e[32m[TEST 31] Globbing OR and redirect Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 31] Globbing OR and redirect Test NOT PASSED\e[0m"
        fi

        ##Globbing OR and redirect 2
        mkdir tnum/33 -p
        echo "echo ??.sh || ls | cat -e | grep test || echo nothing" | ./42sh &> tnum/33/output
        echo "echo ??.sh || ls | cat -e | grep test || echo nothing" | tcsh  &> tnum/33/desired
        if diff -q tnum/33/desired tnum/33/output; then
            echo -e "\e[32m[TEST 33] Globbing OR and redirect 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 33] Globbing OR and redirect 2 Test NOT PASSED\e[0m"
        fi

        ##Globbing OR and redirect 3
        mkdir tnum/35 -p
        echo "echo 4*.sh || ls | cat -e | grep test" | ./42sh &> tnum/35/output
        echo "echo 4*.sh || ls | cat -e | grep test" | tcsh  &> tnum/35/desired
        if diff -q tnum/35/desired tnum/35/output; then
            echo -e "\e[32m[TEST 35] Globbing OR and redirect 3 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 35] Globbing OR and redirect 3 Test NOT PASSED\e[0m"
        fi

        ##Globbing [A-Z]*
        mkdir tnum/37 -p
        echo "echo [A-Z]*.sh" | ./42sh &> tnum/37/output
        echo "echo [A-Z]*.sh" | tcsh  &> tnum/37/desired
        if diff -q tnum/37/desired tnum/37/output; then
            echo -e "\e[32m[TEST 37] Globbing [A-Z]* Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 37] Globbing [A-Z]* Test NOT PASSED\e[0m"
        fi

        
        ##Globbing [b-a]*
        mkdir tnum/39 -p
        echo "echo [b-a]*.sh" | ./42sh &> tnum/39/output
        echo "echo [b-a]*.sh" | tcsh  &> tnum/39/desired
        if diff -q tnum/39/desired tnum/39/output; then
            echo -e "\e[32m[TEST 39] Globbing [b-a]* Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 39] Globbing [b-a]* Test NOT PASSED\e[0m"
        fi

        ##Globbing [a-b]*.sh
        mkdir tnum/41 -p
        echo "echo [a-b]*.sh" | ./42sh &> tnum/41/output
        echo "echo [a-b]*.sh" | tcsh  &> tnum/41/desired
        if diff -q tnum/41/desired tnum/41/output; then
            echo -e "\e[32m[TEST 41] Globbing [a-b]*.sh Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 41] Globbing [a-b]*.sh Test NOT PASSED\e[0m"
        fi

        ##Globbing [a-b]???.sh
        mkdir tnum/43 -p
        echo "echo [a-b]???.sh" | ./42sh &> tnum/43/output
        echo "echo [a-b]???.sh" | tcsh  &> tnum/43/desired
        if diff -q tnum/43/desired tnum/43/output; then
            echo -e "\e[32m[TEST 43] Globbing [a-b]???.sh Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 43] Globbing [a-b]???.sh Test NOT PASSED\e[0m"
        fi

        ##Globbing [a-z]???.sh
        mkdir tnum/45 -p
        echo "echo [a-z]???.sh" | ./42sh &> tnum/45/output
        echo "echo [a-z]???.sh" | tcsh  &> tnum/45/desired
        if diff -q tnum/45/desired tnum/45/output; then
            echo -e "\e[32m[TEST 45] Globbing [a-z]???.sh Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 45] Globbing [a-z]???.sh Test NOT PASSED\e[0m"
        fi
