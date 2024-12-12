#<-------------------------------|VARIABLES|---------------------------------->#

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
READLINE_LIBS = -Lreadline -lreadline -lhistory -lncurses

#<---------------------------------|FILES|------------------------------------>#

LIBFT = ./Libft/libft.a

SRC_F = minishell.c token_utils.c token.c token_analize.c token_clean.c \
        token_clean_utils.c command_path.c \
        struct_delete.c command.c command_utils.c home.c \
		executor_utils.c executor_builts.c executor_files.c executor.c \
		expand_asterisk.c expand.c expand_env.c expand_next.c expand_slash.c expand_utils.c \
        cd.c echo.c env.c exit.c export.c export_append.c \
		export_utils.c print_export.c pwd.c unset.c utils.c \
        check.c main.c init.c cd_utils.c void_envp.c signals.c cd_env.c cd_type.c
SRC_D = ./sources/
BLT_D = ./built-ins/

OBJ_F = ${SRC_F:.c=.o}
OBJ_D = ./objects/
OBJ = ${addprefix ${OBJ_D}, ${OBJ_F}}

DEP_F = ${SRC_F:.c=.d}
DEP_D = ./dependencies/
DEP = ${addprefix ${DEP_D}, ${DEP_F}}

#<---------------------------------|COLORS|----------------------------------->#

DF = \033[0;39m#\t\tDefault
RED= \033[0;31m#\t\tRed
BRED= \033[1;31m#\t\tBold Red
BBLUE= \033[1;34m#\t\tBold Blue
BYELLOW= \033[1;33m#\tBold Yellow
BIPRPL = \033[1;95m#\tPurple
BCYAN= \033[1;36m#\t\tBold Cyan
BIRED= \033[1;91m#\t\tBold Intense Red
BIGREEN= \033[1;92m#\tBold Intense Green
BBLACK= \033[1;30m#\t\tBold Black

#<---------------------------------|RULES|------------------------------------>#

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	${CC} ${CFLAGS} ${OBJ} ${READLINE_LIBS} ${LIBFT} -o ${NAME}

${OBJ_D}%.o: ${SRC_D}%.c | ${OBJ_D} ${DEP_D}
	${CC} ${CFLAGS} -MMD -c $< -o $@

${OBJ_D}%.o: ${BLT_D}%.c | ${OBJ_D} ${DEP_D}
	${CC} ${CFLAGS} -MMD -c $< -o $@

${LIBFT}:
	make -C Libft --no-print-directory

${OBJ_D}:
	mkdir -p ${OBJ_D}

${DEP_D}:
	mkdir -p ${DEP_D}

readline:
	make -C readline

.rl_confi:
	echo "READLINE WILL BE CONFIGURED";
	cd readline && ./configure;
	touch .rl_confi

-include ${DEP}

clean:
	make clean -C Libft --no-print-directory
	rm -rf ${OBJ_D} ${DEP_D}

fclean: clean
	make fclean -C Libft --no-print-directory
	rm -rf ${NAME}
	rm -f .rl_confi

re: fclean all

.PHONY: all clean fclean re readline


