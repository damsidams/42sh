##
## EPITECH PROJECT, 2023
## B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
## File description:
## Makefile
##

SRC	=	src/main.c					\
		src/disp_env.c				\
		src/unsetenv.c				\
		src/cd.c					\
		src/pipe.c					\
		src/user_input.c			\
		src/command_handling.c		\
		src/redirect.c				\
		src/setenv.c				\
		src/set_color.c				\
		src/my_sh.c					\
		src/auto_complete.c

UT_SRC	=	tests/unit_tests.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I include/

LDFLAGS =	-L./lib/my

LDLIBS	=	-lmy

LIBNAME	=	libmy.a

CS_CLEAN = *.log

UT_BIN	=	ut

UT_FLAGS	=	--coverage -lcriterion

UT_CLEAN	=	*.gc*

VAL_CLEAN	=	vgcore*

CS_REPORT	=	coding-style-reports.log

NAME	=	42sh

RM	=	rm -f


all:	lib	$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C lib/my
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

clean	:
	$(MAKE) clean -C lib/my
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME) $(TNAME) lib/my/$(LIBNAME)
	$(RM) $(NAME)
	$(RM) $(CS_CLEAN)
	$(RM) $(UT_CLEAN)
	$(RM) $(UT_BIN)
	$(RM) $(VAL_CLEAN)

re	:	fclean all

valgrind : CFLAGS += -g3
valgrind : re

asan:	CC	=	clang -fsanitize=address
asan:	CFLAGS += -g3
asan:	re

gdb: valgrind
	gdb -ex "run" -ex "bt full" -ex "detach" -ex "quit" $(NAME)

coding_style:	fclean
	coding-style . . > /dev/null 2>&1
	cat $(CS_REPORT)
	make fclean  > /dev/null 2>&1

tests_run:	fclean re
	gcc -o $(UT_BIN) $(UT_SRC) -I include/ -L . -lhashtable $(UT_FLAGS)
	./$(UT_BIN)

coverage:
	gcovr --exclude tests/ --exclude src/useful_funcs

.PHONY	:
	all	clean fclean re debug $(NAME) coding_style tests_run coverage

.SILENT :
	all	clean fclean re debug $(NAME) coding_style tests_run coverage
