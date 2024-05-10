##
## EPITECH PROJECT, 2023
## B-PSU-200-PAR-2-1-minishell1-nicolas.nunney
## File description:
## Makefile
##

SRC	=	src/main.c								\
		src/env/disp_env.c						\
		src/env/unsetenv.c						\
		src/env/setenv.c						\
		src/line_parsing/get_cmd.c				\
		src/line_parsing/get_input.c			\
		src/line_parsing/get_input_getline.c	\
		src/line_parsing/input_manip.c			\
		src/history/historic.c					\
		src/history/special_getnbr.c			\
		src/history/time.c						\
		src/history/display_hist.c				\
		src/history/find_cmd.c	\
		src/history/history_parser.c	\
		src/history/find_cmd_str.c	\
		src/history/get_historic.c	\
		src/command_handling/command_type.c		\
		src/command_handling/command_error.c	\
		src/command_handling/command_exec.c		\
		src/command_handling/built_in_command.c	\
		src/cd.c								\
		src/pipe.c								\
		src/redirect.c							\
		src/set_color.c							\
		src/my_sh.c								\
		src/auto_complete.c						\
		src/signal.c							\
		src/file.c								\
		src/backtick/backtick.c							\
		src/backtick/get_output.c							\
		src/check_and_or.c						\
		src/globbing.c							\
		src/linked_list.c	\
		src/shell_info.c	\
		src/parentheses.c	\
		src/aliases.c							\
		src/local/set.c			\
		src/local/unset.c		\
		src/local/insert_var.c		\
		src/test.c	\
		src/alias_loop.c	\
		src/job_control.c						\
		src/background.c 						\
		src/foreground.c 						\
		src/job_control_utils.c 				\
		src/auto_complete_cmd.c 				\
		src/auto_complete_paths.c				\

UT_SRC	=	tests/unit_tests.c						\
			src/test.c								\
			src/env/disp_env.c						\
			src/env/unsetenv.c						\
			src/env/setenv.c						\
			src/line_parsing/get_cmd.c				\
			src/line_parsing/get_input.c			\
			src/line_parsing/get_input_getline.c	\
			src/line_parsing/input_manip.c			\
			src/history/historic.c					\
			src/history/special_getnbr.c			\
			src/history/time.c							\
			src/history/display_hist.c				\
			src/history/find_cmd.c	\
			src/history/history_parser.c	\
			src/history/find_cmd_str.c	\
			src/history/get_historic.c	\
			src/command_handling/command_type.c		\
			src/command_handling/command_error.c	\
			src/command_handling/command_exec.c		\
			src/command_handling/built_in_command.c	\
			src/cd.c								\
			src/pipe.c								\
			src/redirect.c							\
			src/set_color.c							\
			src/my_sh.c					\
			src/auto_complete.c								\
			src/file.c								\
			src/backtick/backtick.c							\
			src/backtick/get_output.c							\
			src/check_and_or.c						\
			src/globbing.c							\
			src/linked_list.c	\
			src/shell_info.c	\
			src/parentheses.c	\
			src/aliases.c							\
			src/local/insert_var.c	\
			src/local/set.c			\
			src/local/unset.c		\
			src/alias_loop.c	\

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-I include/

LDFLAGS =	-L./lib/my/

LDLIBS	=	-lmy

LIBNAME	=	libmy.a

CS_CLEAN = *.log

UT_BIN	=	unit_test

UT_FLAGS	=	--coverage -lcriterion

UT_CLEAN	=	*.gc*

VAL_CLEAN	=	vgcore*

CS_REPORT	=	coding-style-reports.log

NAME	=	42sh

RM	=	rm -f

all:	libb $(NAME)

libb:
	$(MAKE) all -C lib/my

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(MAKE) clean -C lib/my
	$(RM) $(OBJ)

fclean:	clean
	$(MAKE) fclean -C lib/my/
	$(RM) $(NAME) $(TNAME)
	$(RM) $(NAME)
	$(RM) $(CS_CLEAN)
	$(RM) $(UT_CLEAN)
	$(RM) $(UT_BIN)
	$(RM) $(VAL_CLEAN)

re:	fclean all

valgrind: CFLAGS += -g3
valgrind: re

asan:	CC	=	clang -fsanitize=address
asan:	CFLAGS += -g3
asan:	re

gdb: valgrind
	gdb -ex "run" -ex "bt full" -ex "detach" -ex "quit" $(NAME)

coding_style:	fclean
	coding-style . . > /dev/null 2>&1
	cat $(CS_REPORT)
	make fclean  > /dev/null 2>&1

tests_run:
	$(MAKE) all -C lib/my
	$(CC) -I include/ -L lib/my -o $(UT_BIN) $(UT_SRC) $(UT_FLAGS) -lmy
	./$(UT_BIN)

coverage:
	gcovr --exclude tests/ --exclude src/useful_funcs

.PHONY:
	all libb clean fclean re debug coding_style tests_run coverage

.SILENT :
	coding_style
