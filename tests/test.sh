(cd .. && make && cp 42sh tests/.)

echo " _____                 _   _                   _   _____         _            "
echo "|  ___|   _ _ __   ___| |_(_) ___  _ __   __ _| | |_   _|__  ___| |_ ___ _ __ "
echo "| |_ | | | | '_ \ / __| __| |/ _ \| '_ \ / _\` | |   | |/ _ \/ __| __/ _ \ '__|"
echo "|  _|| |_| | | | | (__| |_| | (_) | | | | (_| | |   | |  __/\__ \ ||  __/ |   "
echo "|_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|\__,_|_|   |_|\___||___/\__\___|_|   "
echo ""

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

        ##cd with args
        mkdir tnum/8 -p
        echo "cd ../; pwd" | ./42sh > tnum/8/output
        echo "cd ../; pwd" | tcsh  > tnum/8/desired
        if diff -q tnum/8/desired tnum/8/output; then
            echo -e "\e[32m[TEST 8] cd with args Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 8] cd with args Test NOT PASSED\e[0m"
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

        ##cd to root (no args)
        mkdir tnum/10 -p
        echo "cd; pwd" | ./42sh > tnum/10/output
        echo "cd; pwd" | tcsh  > tnum/10/desired
        if diff -q tnum/10/desired tnum/10/output; then
            echo -e "\e[32m[TEST 10] cd to root (no args) Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 10] cd to root (no args) Test NOT PASSED\e[0m"
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

        ##cd wrong path
        mkdir tnum/12 -p
        echo "cd toto" | ./42sh &> tnum/12/output
        echo "cd toto" | tcsh  &> tnum/12/desired
        if diff -q tnum/12/desired tnum/12/output; then
            echo -e "\e[32m[TEST 12] cd wrong path Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 12] cd wrong path Test NOT PASSED\e[0m"
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

        ##no command
        mkdir tnum/14 -p
        echo "" | ./42sh &> tnum/14/output
        echo "" | tcsh  &> tnum/14/desired
        if diff -q tnum/14/desired tnum/14/output; then
            echo -e "\e[32m[TEST 14] no command Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 14] no command Test NOT PASSED\e[0m"
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

        ##unknown command
        mkdir tnum/16 -p
        echo "toto" | ./42sh &> tnum/16/output
        echo "toto" | tcsh  &> tnum/16/desired
        if diff -q tnum/16/desired tnum/16/output; then
            echo -e "\e[32m[TEST 16] unknown command Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 16] unknown command Test NOT PASSED\e[0m"
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

        ##inhibitors ""
        mkdir tnum/18 -p
        echo "echo "this is a sentence between quotes"" | ./42sh > tnum/18/output
        echo "echo "this is a sentence between quotes"" | tcsh  > tnum/18/desired
        if diff -q tnum/18/desired tnum/18/output; then
            echo -e "\e[32m[TEST 18] inhibitors "" Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 18] inhibitors "" Test NOT PASSED\e[0m"
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

        ##set local variable
        mkdir tnum/20 -p
        echo "set test1=test2 && set test3 && set test1=test4 test3=test5" | ./42sh &> tnum/20/output
        echo "set test1=test2 && set test3 && set test1=test4 test3=test5" | tcsh  &> tnum/20/desired
        if diff -q tnum/20/desired tnum/20/output; then
            echo -e "\e[32m[TEST 20] set local variable Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 20] set local variable Test NOT PASSED\e[0m"
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

        ##unset local variables
        mkdir tnum/22 -p
        echo "set test1 test2 test3 test4=test5 test 6 && unset test1 test2 test3 test4 test5" | ./42sh &> tnum/22/output
        echo "set test1 test2 test3 test4=test5 test 6 && unset test1 test2 test3 test4 test5" | tcsh  &> tnum/22/desired
        if diff -q tnum/22/desired tnum/22/output; then
            echo -e "\e[32m[TEST 22] unset local variables Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 22] unset local variables Test NOT PASSED\e[0m"
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

        ##unset undefined local variable
        mkdir tnum/24 -p
        echo "unset toto" | ./42sh &> tnum/24/output
        echo "unset toto" | tcsh  &> tnum/24/desired
        if diff -q tnum/24/desired tnum/24/output; then
            echo -e "\e[32m[TEST 24] unset undefined local variable Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 24] unset undefined local variable Test NOT PASSED\e[0m"
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

        ##unset with not enough arguments
        mkdir tnum/26 -p
        echo "unset" | ./42sh &> tnum/26/output
        echo "unset" | tcsh  &> tnum/26/desired
        if diff -q tnum/26/desired tnum/26/output; then
            echo -e "\e[32m[TEST 26] unset with not enough arguments Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 26] unset with not enough arguments Test NOT PASSED\e[0m"
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

        ##set local variable with bad format
        mkdir tnum/28 -p
        echo "set 1toto" | ./42sh &> tnum/28/output
        echo "set 1toto" | tcsh  &> tnum/28/desired
        if diff -q tnum/28/desired tnum/28/output; then
            echo -e "\e[32m[TEST 28] set local variable with bad format Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 28] set local variable with bad format Test NOT PASSED\e[0m"
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

        ##set local variable with bad format 2
        mkdir tnum/30 -p
        echo "set to-to" | ./42sh &> tnum/30/output
        echo "set to-to" | tcsh  &> tnum/30/desired
        if diff -q tnum/30/desired tnum/30/output; then
            echo -e "\e[32m[TEST 30] set local variable with bad format 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 30] set local variable with bad format 2 Test NOT PASSED\e[0m"
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

        ##setenv variable
        mkdir tnum/32 -p
        echo "setenv test1 && setenv test2=test3 && setenv test4=test2 && setenv test1=test4" | ./42sh &> tnum/32/output
        echo "setenv test1 && setenv test2=test3 && setenv test4=test2 && setenv test1=test4" | tcsh  &> tnum/32/desired
        if diff -q tnum/32/desired tnum/32/output; then
            echo -e "\e[32m[TEST 32] setenv variable Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 32] setenv variable Test NOT PASSED\e[0m"
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

        ##setenv with too many arguments
        mkdir tnum/34 -p
        echo "setenv test1 test2 test3 test4" | ./42sh &> tnum/34/output
        echo "setenv test1 test2 test3 test4" | tcsh  &> tnum/34/desired
        if diff -q tnum/34/desired tnum/34/output; then
            echo -e "\e[32m[TEST 34] setenv with too many arguments Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 34] setenv with too many arguments Test NOT PASSED\e[0m"
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

        ##setenv variable with bad format
        mkdir tnum/36 -p
        echo "setenv 1test" | ./42sh &> tnum/36/output
        echo "setenv 1test" | tcsh  &> tnum/36/desired
        if diff -q tnum/36/desired tnum/36/output; then
            echo -e "\e[32m[TEST 36] setenv variable with bad format Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 36] setenv variable with bad format Test NOT PASSED\e[0m"
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

        ##setenv variable with bad format 2
        mkdir tnum/38 -p
        echo "setenv test-toto" | ./42sh &> tnum/38/output
        echo "setenv test-toto" | tcsh  &> tnum/38/desired
        if diff -q tnum/38/desired tnum/38/output; then
            echo -e "\e[32m[TEST 38] setenv variable with bad format 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 38] setenv variable with bad format 2 Test NOT PASSED\e[0m"
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

        ##unsetenv variable
        mkdir tnum/40 -p
        echo "setenv test1 && setenv test2=test3 && unsetenv test1 && unsetenv test2" | ./42sh &> tnum/40/output
        echo "setenv test1 && setenv test2=test3 && unsetenv test1 && unsetenv test2" | tcsh  &> tnum/40/desired
        if diff -q tnum/40/desired tnum/40/output; then
            echo -e "\e[32m[TEST 40] unsetenv variable Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 40] unsetenv variable Test NOT PASSED\e[0m"
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

        ##unsetenv unknown variable
        mkdir tnum/42 -p
        echo "unsetenv toto" | ./42sh &> tnum/42/output
        echo "unsetenv toto" | tcsh  &> tnum/42/desired
        if diff -q tnum/42/desired tnum/42/output; then
            echo -e "\e[32m[TEST 42] unsetenv unknown variable Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 42] unsetenv unknown variable Test NOT PASSED\e[0m"
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

        ##unsetenv with not enough arguments
        mkdir tnum/44 -p
        echo "unsetenv" | ./42sh &> tnum/44/output
        echo "unsetenv" | tcsh  &> tnum/44/desired
        if diff -q tnum/44/desired tnum/44/output; then
            echo -e "\e[32m[TEST 44] unsetenv with not enough arguments Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 44] unsetenv with not enough arguments Test NOT PASSED\e[0m"
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

        ##unsetenv multiple variables
        mkdir tnum/46 -p
        echo "setenv test1 && setenv test2 && unsetenv test1 test2" | ./42sh &> tnum/46/output
        echo "setenv test1 && setenv test2 && unsetenv test1 test2" | tcsh  &> tnum/46/desired
        if diff -q tnum/46/desired tnum/46/output; then
            echo -e "\e[32m[TEST 46] unsetenv multiple variables Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 46] unsetenv multiple variables Test NOT PASSED\e[0m"
        fi

        ##Simple parentheses
        mkdir tnum/47 -p
        echo "(ls)" | ./42sh &> tnum/47/output
        echo "(ls)" | tcsh  &> tnum/47/desired
        if diff -q tnum/47/desired tnum/47/output; then
            echo -e "\e[32m[TEST 47] Simple parentheses Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 47] Simple parentheses Test NOT PASSED\e[0m"
        fi

        ##Simple parentheses 2
        mkdir tnum/49 -p
        echo "(ls) && pwd" | ./42sh &> tnum/49/output
        echo "(ls) && pwd" | tcsh  &> tnum/49/desired
        if diff -q tnum/49/desired tnum/49/output; then
            echo -e "\e[32m[TEST 49] Simple parentheses 2 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 49] Simple parentheses 2 Test NOT PASSED\e[0m"
        fi

        ##Simple parentheses 3
        mkdir tnum/51 -p
        echo "(cd; pwd) && echo ok" | ./42sh &> tnum/51/output
        echo "(cd; pwd) && echo ok" | tcsh  &> tnum/51/desired
        if diff -q tnum/51/desired tnum/51/output; then
            echo -e "\e[32m[TEST 51] Simple parentheses 3 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 51] Simple parentheses 3 Test NOT PASSED\e[0m"
        fi

        ##Simple parentheses 4
        mkdir tnum/53 -p
        echo "(cd; pwd) || echo ok" | ./42sh &> tnum/53/output
        echo "(cd; pwd) || echo ok" | tcsh  &> tnum/53/desired
        if diff -q tnum/53/desired tnum/53/output; then
            echo -e "\e[32m[TEST 53] Simple parentheses 4 Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 53] Simple parentheses 4 Test NOT PASSED\e[0m"
        fi

        ##Alias infinite loop
        mkdir tnum/54 -p
        echo "alias p pwd || alias pwd p || pwd || p" | ./42sh > tnum/54/output
        echo "alias p pwd || alias pwd p || pwd || p" | tcsh  > tnum/54/desired
        if diff -q tnum/54/desired tnum/54/output; then
            echo -e "\e[32m[TEST 54] Alias infinite loop Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 54] Alias infinite loop Test NOT PASSED\e[0m"
        fi

        ##Change alias command
        mkdir tnum/55 -p
        echo "alias p pwd || alias p ls || p" | ./42sh > tnum/55/output
        echo "alias p pwd || alias p ls || p" | tcsh  > tnum/55/desired
        if diff -q tnum/55/desired tnum/55/output; then
            echo -e "\e[32m[TEST 55] Change alias command Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 55] Change alias command Test NOT PASSED\e[0m"
        fi

        ##Unalias
        mkdir tnum/56 -p
        echo "alias p pwd || unalias p || p" | ./42sh > tnum/56/output
        echo "alias p pwd || unalias p || p" | tcsh  > tnum/56/desired
        if diff -q tnum/56/desired tnum/56/output; then
            echo -e "\e[32m[TEST 56] Unalias Test PASSED\e[0m"
        else
            echo -e "\e[31m[TEST 56] Unalias Test NOT PASSED\e[0m"
        fi
