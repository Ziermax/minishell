#<-------------------------------|VARIABLES|---------------------------------->#

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
READLINE_LIBS = -L./readline -lreadline -lhistory -lncurses

#<---------------------------------|FILES|------------------------------------>#

LIBFT = ./Libft/libft.a

SRC_F = minishell.c token_utils.c token.c analize_tokens.c clean_tokens.c \
        clean_tokens_utils.c arrange_tokens.c path.c print_struct.c \
        delete_struct.c command.c executor.c \
        cd.c echo.c env.c exit.c export.c export_append.c export_array.c \
		export_utils.c print_export.c pwd.c unset.c utils.c export_array_append.c \
        check.c main.c init.c
SRC_D = ./sources/
BLT_D = ./built-ins/

OBJ_F = ${SRC_F:.c=.o}
OBJ_D = ./objects/
OBJ = ${addprefix ${OBJ_D}, ${OBJ_F}}

DEP_F = ${SRC_F:.c=.d}
DEP_D = ./dependencies/
DEP = ${addprefix ${DEP_D}, ${DEP_F}}

#<---------------------------------|COLORS|----------------------------------->#

DF = \033[0;39m#		Default
RED= \033[0;31m#		Red
BRED= \033[1;31m#		Bold Red
BBLUE= \033[1;34m#		Bold Blue
BYELLOW= \033[1;33m#	Bold Yellow
BIPRPL = \033[1;95m#	Purple
BCYAN= \033[1;36m#		Bold Cyan
BIRED= \033[1;91m#		Bold Intense Red
BIGREEN= \033[1;92m#	Bold Intense Green
BBLACK=\033[1;30m#		Bold Black

#<---------------------------------|RULES|------------------------------------>#

all: .rl_confi libftmake readline ${NAME}

readline:
	@make -C readline

${NAME}: ${OBJ_D} ${DEP_D} ${OBJ} ${LIBFT} ${READLINE_LIBS}
	@${CC} ${CFLAGS} ${OBJ} ${READLINE_LIBS} ${LIBFT} -o ${NAME}
	@echo "\n${RED}Compiling program:${DF}"
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS}${DF} ${BIGREEN}${OBJ_F}${DF} \
	${BIPRPL}${LIBFT}${DF} ${BCYAN}${READLINE_LIBS}${DF} ${BCYAN}-o${DF} ${RED}${NAME}${DF}"

libftmake:
	@echo "${BCYAN}### LIBFT ###${DF}${BIGREEN}"
	@make -C Libft --no-print-directory
	@echo "${DF}${BCYAN}###${DF} ${BIPRPL}libft.a${DF} ${BCYAN}made ---${DF}\n"

${OBJ_D}%.o: ${SRC_D}%.c Makefile
	@${CC} ${CFLAGS} -MMD -c $< -o $@
	@mv ${@:.o=.d} ${DEP_D}
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS} -MMD${DF} ${BCYAN}-c${DF} \
	${BIRED}$<${DF} ${BCYAN}-o${DF} ${BIGREEN}$@${DF}"
	@echo "${BCYAN}mv${DF} ${BYELLOW}${@:.o=.d}${DF} ${BCYAN}${DEP_D}${DF}"

${OBJ_D}%.o: ${BLT_D}%.c Makefile
	@${CC} ${CFLAGS} -MMD -c $< -o $@
	@mv ${@:.o=.d} ${DEP_D}
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS} -MMD${DF} ${BCYAN}-c${DF} \
	${BIRED}$<${DF} ${BCYAN}-o${DF} ${BIGREEN}$@${DF}"
	@echo "${BCYAN}mv${DF} ${BYELLOW}${@:.o=.d}${DF} ${BCYAN}${DEP_D}${DF}"

${OBJ_D}:
	@mkdir ${OBJ_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${OBJ_D}${DF}"

${DEP_D}:
	@mkdir ${DEP_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${DEP_D}${DF}"

${READLINE_LIBS}: #readline/Makefile
	@echo "${BCYAN}### READLINE ###${DF}${BIRED}"
	@make -C readline static
	@echo "${DF}${BCYAN}###${DF} ${BIPRPL}READLINE${DF} ${BCYAN}made ---${DF}\n"

.rl_confi:
	echo "READLINE WILL BE CONFIGURED";
	cd readline && ./configure;
	@touch .rl_confi

#<---------------------------------|PHONY|------------------------------------>#

clean:
	@echo "${BCYAN}### LIBFT fclean ###${DF}"
	@make fclean -C Libft --no-print-directory
	@echo "${BCYAN}### LIBFT cleaned ---${DF}\n"
	@rm -rf ${OBJ_D} ${DEP_D}
	@echo "${RED}rm -rf${DF} ${BIGREEN}OBJECTS: ${OBJ_F}${DF}"
	@echo "${RED}rm -rf${DF} ${BYELLOW}DEPENDENCIES: ${DEP_F}${DF}"

fclean: clean
	@rm -rf ${NAME}
	@rm -rf .rl_confi
	@echo "${RED}rm -rf${DF} ${RED}PROGRAM: ${NAME}${DF}\n"

re: fclean all

-include ${DEP}

.PHONY: all clean fclean re
#<---------------------------------------------------------------------------->#

